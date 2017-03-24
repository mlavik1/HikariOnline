#ifdef HIKARI_GAMESERVER
#include "game_server.h"
#include <sdl2/SDL_net.h>
#include "Core/Networking/net_message_data.h"
#include <algorithm>
#include "game_instance.h"
#include "Core/Networking/rpc.h"

namespace Hikari
{
	GameServer::GameServer(GameInstance* arg_gameinstance)
	{
		mGameInstance = arg_gameinstance;
		SDLNet_Init();
		
		mGameServerNetworkController = new GameServerNetworkController(mGameInstance);

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
		mGameInstance->GetNetworkManager()->GenerateNetGUID(mGameServerNetworkController);
		mGameInstance->GetNetworkManager()->RegisterObject(mGameServerNetworkController);
		
		std::string myIP = GetLocalhostIP();
		LOG_INFO() << "My IP: " << myIP;

		mWorldServerConnection->SetClientConnectedCallback([&](int arg_clientid) -> void
		{
			LOG_INFO() << "World Server connected!";
		});

		mWorldServerConnection->SetMessageCallback([&](int arg_clientid, const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from world server";

			NetMessage incomingMessage(arg_message);
			mIncomingWorldServerMessages.push_back(ClientNetMessage(arg_clientid, incomingMessage));
		});


		mClientConnection->SetClientConnectedCallback([&](int arg_clientid) -> void
		{
			LOG_INFO() << "Client connected!";
		});

		mClientConnection->SetMessageCallback([&](int arg_clientid, const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from client";

			NetMessage incomingMessage(arg_message);
			mIncomingClientMessages.push_back(ClientNetMessage(arg_clientid, incomingMessage));
		});

	}

	void GameServer::Update()
	{
		mWorldServerConnection->FetchNewMessages();
		mClientConnection->FetchNewMessages();

		for (ClientNetMessage& clientNetMessage : mIncomingWorldServerMessages)
		{
			const int& clientID = std::get<0>(clientNetMessage);
			const NetMessage& netMessage = std::get<1>(clientNetMessage);

			const char* messageData = netMessage.GetMessageData();
			if(messageData != nullptr)
				LOG_INFO() << "message: " << netMessage.GetMessageData();

			switch (netMessage.GetMessageType())
			{
			case NetMessageType::EstablishConnection:
				WorldServerConnectionData worldServer;
				worldServer.mClientID = clientID;
				worldServer.mIPAddress = mWorldServerConnection->GetSocketIPAddress(clientID);
				mConnectedWorldServers.push_back(worldServer);
				LOG_INFO() << "Established connection with World Server: " << worldServer.mIPAddress;
				NetMessage msgAck(NetMessageType::ConnectionEstablishedAck, "");
				mOutgoingWorldServerMessages.push_back(ClientNetMessage(clientID, msgAck));
				break;
			}
		}

		for (ClientNetMessage& clientNetMessage : mIncomingClientMessages)
		{
			const int& clientID = std::get<0>(clientNetMessage);
			const NetMessage& netMessage = std::get<1>(clientNetMessage);

			LOG_INFO() << "message: " << netMessage.GetMessageData();

			switch (netMessage.GetMessageType())
			{
			case NetMessageType::EstablishConnection:
			{
				ClientConnectionData clientConn;
				clientConn.mClientID = clientID;
				clientConn.mIPAddress = mClientConnection->GetSocketIPAddress(clientID);
				clientConn.mAccountName = netMessage.GetMessageData();
				EstablishConnectionWithClient(clientConn);
				break;
			}
			case NetMessageType::RPC:
				RPCCaller::HandleIncomingRPC(&netMessage, mGameInstance);
				break;
			}
		}

		for (ClientNetMessage& outMessage : mOutgoingWorldServerMessages)
		{
			const int& clientID = std::get<0>(outMessage);
			const NetMessage& netMessage = std::get<1>(outMessage);
			mWorldServerConnection->SendNetworkMessage(clientID, &netMessage);
		}

		for (ClientNetMessage& outMessage : mOutgoingClientMessages)
		{
			const int& clientID = std::get<0>(outMessage);
			const NetMessage& netMessage = std::get<1>(outMessage);
			if (clientID == -1)
			{
				mClientConnection->SendNetworkMessageToAll(&netMessage);
			}
			else
			{
				mClientConnection->SendNetworkMessage(clientID, &netMessage);
			}
		}

		mIncomingWorldServerMessages.clear();
		mIncomingClientMessages.clear();
		mOutgoingWorldServerMessages.clear();
		mOutgoingClientMessages.clear();
	}

	void GameServer::EstablishConnectionWithClient(const ClientConnectionData& arg_clientconndata)
	{
		mConnectedClients.push_back(arg_clientconndata);
		ClientNetworkController* clientNetworkController = new ClientNetworkController(mGameInstance);
		mGameInstance->GetNetworkManager()->GenerateNetGUID(clientNetworkController);
		mGameInstance->GetNetworkManager()->RegisterObject(clientNetworkController);
		mClientNetworkControllers[arg_clientconndata.mClientID] = clientNetworkController;

		LOG_INFO() << "Established connection with client: " << arg_clientconndata.mAccountName << " " << arg_clientconndata.mIPAddress;
		NetMessage msgAck(NetMessageType::ConnectionEstablishedAck, "");
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
		NetMessage serverListMsg(NetMessageType::WorldServerListUpdate, sizeof(NetMessageData::WorldServerList), reinterpret_cast<char*>(&serverListData));
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_clientconndata.mClientID, serverListMsg));

		// Tell client to initialise GameServerNetworkController, and set its GUID
		NetMessageData::ClientGameServerConnectionData initGSNetController;
		initGSNetController.GameServerNetworkControllerNetGUID = mGameServerNetworkController->GetNetGUID();
		initGSNetController.ClientNetworkControllerNetGUID = clientNetworkController->GetNetGUID();
		NetMessage initGSNetControllerMsg(NetMessageType::ClientInitGameServerConnection, sizeof(NetMessageData::ClientGameServerConnectionData), reinterpret_cast<char*>(&initGSNetController));
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_clientconndata.mClientID, initGSNetControllerMsg));
	}


	ClientNetworkController* GameServer::GetClientNetworkController(int arg_clientid)
	{
		return mClientNetworkControllers[arg_clientid];
	}

}

#endif
