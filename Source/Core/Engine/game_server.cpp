#ifdef HIKARI_GAMESERVER
#include "game_server.h"
#include <sdl2/SDL_net.h>
#include "Core/Networking/net_message_data.h"
#include <algorithm>
#include "game_engine.h"
#include "Core/Networking/rpc.h"

namespace Hikari
{
	GameServer::GameServer()
	{
		SDLNet_Init();
		
		mGameServerNetworkController = new GameServerNetworkController();

		mWorldServerConnection = new Hikari::ClientConnection(50);
		mClientConnection = new Hikari::ClientConnection(8000);

		mWorldServerConnection->Connect(PORT_GAMESERVER_WORLDSERVER);
		mClientConnection->Connect(PORT_GAMESERVER_CLIENT);
	}

	GameServer::~GameServer()
	{
		mWorldServerConnection->Close();
		mClientConnection->Close();
		delete(mWorldServerConnection);
		delete(mClientConnection);

		SDLNet_Quit();
	}

	void GameServer::Initialise()
	{
		GameEngine::Instance()->GetNetworkManager()->GenerateNetGUID(mGameServerNetworkController);
		GameEngine::Instance()->GetNetworkManager()->RegisterObject(mGameServerNetworkController);
		
		std::string myIP = GetLocalhostIP();
		LOG_INFO() << "My IP: " << myIP;

		mWorldServerConnection->SetClientConnectedCallback([&](int arg_clientid) -> void
		{
			LOG_INFO() << "World Server connected!";
		});

		mWorldServerConnection->SetMessageCallback([&](int arg_clientid, const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from world server";

			NetMessage* incomingMessage = new NetMessage(arg_message);
			mIncomingWorldServerMessages.push_back(ClientNetMessage(arg_clientid, incomingMessage));
		});


		mClientConnection->SetClientConnectedCallback([&](int arg_clientid) -> void
		{
			LOG_INFO() << "Client connected!";
		});

		mClientConnection->SetMessageCallback([&](int arg_clientid, const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from client";

			NetMessage* incomingMessage = new NetMessage(arg_message);
			mIncomingClientMessages.push_back(ClientNetMessage(arg_clientid, incomingMessage));
		});

	}

	void GameServer::Update()
	{
		mWorldServerConnection->FetchNewMessages();
		mClientConnection->FetchNewMessages();

		for (ClientNetMessage& worldServerNetMessage : mIncomingWorldServerMessages)
		{
			const int& worldServerID = std::get<0>(worldServerNetMessage);
			const NetMessage* netMessage = std::get<1>(worldServerNetMessage);

			const char* messageData = netMessage->GetMessageData();
			if(messageData != nullptr)
				LOG_INFO() << "message: " << netMessage->GetMessageData();

			switch (netMessage->GetMessageType())
			{
			case NetMessageType::EstablishConnection:
				WorldServerConnectionData worldServer;
				worldServer.mClientID = worldServerID;
				worldServer.mIPAddress = mWorldServerConnection->GetSocketIPAddress(worldServerID);
				establishConnectionWithWorldServer(worldServer);

				break;
			}
			delete(netMessage);
		}

		for (ClientNetMessage& clientNetMessage : mIncomingClientMessages)
		{
			const int& clientID = std::get<0>(clientNetMessage);
			const NetMessage* netMessage = std::get<1>(clientNetMessage);

			LOG_INFO() << "message: " << netMessage->GetMessageData();

			switch (netMessage->GetMessageType())
			{
			case NetMessageType::EstablishConnection:
			{
				ClientConnectionData clientConn;
				clientConn.mClientID = clientID;
				clientConn.mIPAddress = mClientConnection->GetSocketIPAddress(clientID);
				clientConn.mAccountName = netMessage->GetMessageData();
				establishConnectionWithClient(clientConn);
				break;
			}
			case NetMessageType::RPC:
				RPCCaller::HandleIncomingRPC(netMessage);
				break;
			}
			delete(netMessage);
		}

		for (ClientNetMessage& outMessage : mOutgoingWorldServerMessages)
		{
			const int& clientID = std::get<0>(outMessage);
			const NetMessage* netMessage = std::get<1>(outMessage);
			mWorldServerConnection->SendNetworkMessage(clientID, netMessage);
		}

		for (ClientNetMessage& outMessage : mOutgoingClientMessages)
		{
			const int& clientID = std::get<0>(outMessage);
			const NetMessage* netMessage = std::get<1>(outMessage);
			if (clientID == -1)
			{
				mClientConnection->SendNetworkMessageToAll(netMessage);
			}
			else
			{
				mClientConnection->SendNetworkMessage(clientID, netMessage);
			}
		}

		// Delete all NetMessage instances. Multiple client messages may reference the same NetMessage.
		for (NetMessage* msg : mPendingDeleteNetMessages)
		{
			delete(msg);
		}

		mIncomingWorldServerMessages.clear();
		mIncomingClientMessages.clear();
		mOutgoingWorldServerMessages.clear();
		mOutgoingClientMessages.clear();
		mPendingDeleteNetMessages.clear();
	}

	void GameServer::establishConnectionWithWorldServer(const WorldServerConnectionData& arg_conndata)
	{
		mConnectedWorldServers.push_back(arg_conndata);
		LOG_INFO() << "Established connection with World Server: " << arg_conndata.mIPAddress;
		NetMessage* msgAck = new NetMessage(NetMessageType::ConnectionEstablishedAck, "");
		SendMessageToWorldServer(arg_conndata.mClientID, msgAck);

		// Create WorldServerNetworkController, used for communicating between game server and world server
		WorldServerNetworkController* worldServerNetworkController = new WorldServerNetworkController();
		GameEngine::Instance()->GetNetworkManager()->GenerateNetGUID(worldServerNetworkController);
		GameEngine::Instance()->GetNetworkManager()->RegisterObject(worldServerNetworkController);
		mWorldServerNetworkControllers[arg_conndata.mClientID] = worldServerNetworkController;

		// Tell world server to initialise GameServerNetworkController, and set its GUID
		NetMessageData::ClientGameServerConnectionData initGSNetController;
		initGSNetController.GameServerNetworkControllerNetGUID = mGameServerNetworkController->GetNetGUID();
		initGSNetController.ClientNetworkControllerNetGUID = worldServerNetworkController->GetNetGUID();
		NetMessage *initGSNetControllerMsg = new NetMessage(NetMessageType::WorldServerInitGameServerConnection, sizeof(NetMessageData::ClientGameServerConnectionData), reinterpret_cast<char*>(&initGSNetController));
		mOutgoingWorldServerMessages.push_back(ClientNetMessage(arg_conndata.mClientID, initGSNetControllerMsg));
	}
	
	void GameServer::establishConnectionWithClient(const ClientConnectionData& arg_clientconndata)
	{
		mConnectedClients[arg_clientconndata.mClientID] = arg_clientconndata;
		ClientNetworkController* clientNetworkController = new ClientNetworkController();
		GameEngine::Instance()->GetNetworkManager()->GenerateNetGUID(clientNetworkController);
		GameEngine::Instance()->GetNetworkManager()->RegisterObject(clientNetworkController);
		mClientNetworkControllers[arg_clientconndata.mClientID] = clientNetworkController;

		LOG_INFO() << "Established connection with client: " << arg_clientconndata.mAccountName << " " << arg_clientconndata.mIPAddress;
		NetMessage* msgAck = new NetMessage(NetMessageType::ConnectionEstablishedAck, "");
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_clientconndata.mClientID, msgAck));

		// Send WorldServer-list to client
		NetMessageData::WorldServerList serverListData;
		serverListData.NumServers = mConnectedWorldServers.size();
		for (int i = 0; i < mConnectedWorldServers.size(); i++)
		{
			NetMessageData::WorldServerInfo serverInfo;
			std::string currServerName = "ServerNameTest"; // TODO
			std::memcpy(serverInfo.ServerName, currServerName.c_str(), std::min((size_t)32, currServerName.size() + 1));
			std::memcpy(serverInfo.IPAddress, mConnectedWorldServers[i].mIPAddress.c_str(), std::min((size_t)16, mConnectedWorldServers[i].mIPAddress.size() + 1));
			serverListData.ServerInfos[i] = serverInfo;
		}
		NetMessage* serverListMsg = new NetMessage(NetMessageType::WorldServerListUpdate, sizeof(NetMessageData::WorldServerList), reinterpret_cast<char*>(&serverListData));
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_clientconndata.mClientID, serverListMsg));

		// Tell client to initialise GameServerNetworkController, and set its GUID
		NetMessageData::ClientGameServerConnectionData initGSNetController;
		initGSNetController.GameServerNetworkControllerNetGUID = mGameServerNetworkController->GetNetGUID();
		initGSNetController.ClientNetworkControllerNetGUID = clientNetworkController->GetNetGUID();
		NetMessage *initGSNetControllerMsg = new NetMessage(NetMessageType::ClientInitGameServerConnection, sizeof(NetMessageData::ClientGameServerConnectionData), reinterpret_cast<char*>(&initGSNetController));
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_clientconndata.mClientID, initGSNetControllerMsg));
	}
	
	const std::unordered_map<int, Hikari::GameServer::ClientConnectionData>& GameServer::GetConnectedClients()
	{
		return mConnectedClients;
	}
	
	const Hikari::GameServer::ClientConnectionData* GameServer::GetClientConnectionData(int arg_clientid)
	{
		auto connData = mConnectedClients.find(arg_clientid);
		if (connData != mConnectedClients.end())
			return &connData->second;
		else
			return nullptr;
	}

	ClientNetworkController* GameServer::GetClientNetworkController(int arg_clientid)
	{
		return mClientNetworkControllers[arg_clientid];
	}

	void GameServer::SendMessageToClient(int arg_clientid, NetMessage* arg_message)
	{
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_clientid, arg_message));
		mPendingDeleteNetMessages.insert(arg_message);
	}

	void GameServer::SendMessageToAllClients(NetMessage* arg_message)
	{
		for (auto client : mConnectedClients)
		{
			mOutgoingClientMessages.push_back(ClientNetMessage(client.second.mClientID, arg_message));
		}
		mPendingDeleteNetMessages.insert(arg_message);
	}

	void GameServer::SendMessageToWorldServer(int arg_serverid, NetMessage* arg_message)
	{
		mOutgoingWorldServerMessages.push_back(ClientNetMessage(arg_serverid, arg_message));
		mPendingDeleteNetMessages.insert(arg_message);
	}

}

#endif
