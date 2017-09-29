#ifdef HIKARI_WORLDSERVER
#include "world_server.h"
#include "Core/Debug/debug.h"
#include "Core/World/world_factory.h"
#include "Core/World/world.h"
#include "Core/Controller/client_network_controller.h"
#include "Core/Engine/game_engine.h"
#include "Core/Managers/network_manager.h"
#include "Core/Networking/player_manager.h"
#include "Core/Actor/player_character.h"
#include "Core/Networking/rpc.h"
#include "Core/Networking/net_message_data.h"

namespace Hikari
{
	WorldServer::WorldServer()
	{
		mGameServerConnection = new Hikari::ServerConnection();
		mClientConnection = new Hikari::ClientConnection(1000);
		mWorldServerNetworkController = new WorldServerNetworkController();
	}

	WorldServer::~WorldServer()
	{
		mGameServerConnection->Close();
		mClientConnection->Close();
		delete(mGameServerConnection);
		delete(mClientConnection);
	}

	void WorldServer::Initialise()
	{
		std::string myIP = GetLocalhostIP();
		LOG_INFO() << "My IP: " << myIP;

		GameEngine::Instance()->GetNetworkManager()->GenerateNetGUID(mWorldServerNetworkController);
		GameEngine::Instance()->GetNetworkManager()->RegisterObject(mWorldServerNetworkController);

		mClientConnection->Connect(PORT_WORLDSERVER_CLIENT);

		mClientConnection->SetMessageCallback([&](int arg_clientid, const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from client";

			NetMessage* incomingMessage = new NetMessage(arg_message);
			mIncomingClientMessages.push_back(ClientNetMessage(arg_clientid, incomingMessage));
		});

		mGameServerConnection->SetMessageCallback([&](const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from game server";

			NetMessage* incomingMessage = new NetMessage(arg_message);
			mIncomingGameServerMessages.push_back(incomingMessage);
		});
	}

	bool WorldServer::ConnectToGameServer()
	{
		bool bConnected = mGameServerConnection->Connect("127.0.0.1", PORT_GAMESERVER_WORLDSERVER);

		if (bConnected)
		{
			NetMessage* connMessage = new NetMessage(NetMessageType::EstablishConnection, "");
			mOutgoingGameServerMessages.push_back(connMessage);
		}
		return bConnected;
	}

	void WorldServer::Update()
	{
		// Fetch new messages
		if (mGameServerConnection != nullptr && mGameServerConnection->IsConnected())
		{
			mGameServerConnection->FetchNewMessages();
		}
		if (mClientConnection != nullptr && mClientConnection->IsConnected())
		{
			mClientConnection->FetchNewMessages();
		}


		for (NetMessage* netMessage: mIncomingGameServerMessages)
		{
			const NetMessageType& messageType = netMessage->GetMessageType();
			switch (messageType)
			{

			}
		}

		for (ClientNetMessage& message : mIncomingClientMessages)
		{
			const NetMessage* netMessage = std::get<1>(message);
			int clientID = std::get<0>(message);
			const NetMessageType& messageType = netMessage->GetMessageType();
			switch (messageType)
			{
				case NetMessageType::EstablishConnection:
				{
					std::string clientAccountName = netMessage->GetMessageData();
					ClientConnectionData clientConnData;
					clientConnData.mAccountName = clientAccountName;
					clientConnData.mClientID = clientID;
					clientConnData.mIPAddress = mClientConnection->GetSocketIPAddress(clientID);
					handleIncomingClientConnectionRequest(clientConnData);
					break;
				}
				case NetMessageType::RPC:
				{
					RPCCaller::HandleIncomingRPC(netMessage);
					break;
				}
			}
		}

		// Send outgoing messages
		for (NetMessage* outMessage : mOutgoingGameServerMessages)
		{
			mGameServerConnection->SendNetworkMessage(outMessage);
		}
		for (ClientNetMessage& outMessage : mOutgoingClientMessages)
		{
			if(std::get<0>(outMessage) == -1)
				mClientConnection->SendNetworkMessageToAll(std::get<1>(outMessage));
			else
				mClientConnection->SendNetworkMessage(std::get<0>(outMessage), std::get<1>(outMessage));
		}


		// Delete all received/sent NetMessage instances. Multiple client messages may reference the same NetMessage.
		for (NetMessage* msg : mPendingDeleteNetMessages)
		{
			delete(msg);
		}

		// Clear list of outgoing messages
		mOutgoingGameServerMessages.clear();
		mOutgoingClientMessages.clear();

		mPendingDeleteNetMessages.clear();
		mIncomingClientMessages.clear();
		mIncomingGameServerMessages.clear();
	}

	void WorldServer::SendMessageToClient(int arg_clientid, NetMessage* arg_message)
	{
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_clientid, arg_message));
		mPendingDeleteNetMessages.insert(arg_message);
	}

	void WorldServer::SendMessageToAllClients(NetMessage* arg_message)
	{
		for (auto client : mConnectedClients)
		{
			mOutgoingClientMessages.push_back(ClientNetMessage(client.second.mClientID, arg_message));
		}
		mPendingDeleteNetMessages.insert(arg_message);
	}

	void WorldServer::SendMessageToGameServer(int arg_serverid, NetMessage* arg_message)
	{
		mOutgoingGameServerMessages.push_back(arg_message);
		mPendingDeleteNetMessages.insert(arg_message);
	}


	ClientNetworkController* WorldServer::GetClientNetworkController(int arg_clientid)
	{
		return mClientNetworkControllers[arg_clientid];
	}




	void WorldServer::handleIncomingClientConnectionRequest(const ClientConnectionData& arg_conndata)
	{
		// Add client to map of connected clients
		mConnectedClients[arg_conndata.mClientID] = arg_conndata;

		// Create ClientNetworkController, for communication with client
		ClientNetworkController* clientNetworkController = new ClientNetworkController();
		GameEngine::Instance()->GetNetworkManager()->GenerateNetGUID(clientNetworkController);
		GameEngine::Instance()->GetNetworkManager()->RegisterObject(clientNetworkController);
		mClientNetworkControllers[arg_conndata.mClientID] = clientNetworkController;

		// Register Player in PlayerManager
		GameEngine::Instance()->GetPlayerManager()->AddPlayer(clientNetworkController->GetNetGUID(), arg_conndata);

		// Send ack
		NetMessage* msgAck = new NetMessage(NetMessageType::ConnectionEstablishedAck, "");
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_conndata.mClientID, msgAck));

		// Tell client to initialise WorldServerNetworkController, and set its GUID
		NetMessageData::ClientGameServerConnectionData initGSNetController;
		initGSNetController.GameServerNetworkControllerNetGUID = mWorldServerNetworkController->GetNetGUID();
		initGSNetController.ClientNetworkControllerNetGUID = clientNetworkController->GetNetGUID();
		NetMessage *initGSNetControllerMsg = new NetMessage(NetMessageType::ClientInitWorldServerConnection, sizeof(NetMessageData::ClientGameServerConnectionData), reinterpret_cast<char*>(&initGSNetController));
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_conndata.mClientID, initGSNetControllerMsg));

		// Create PlayerCharacter on server and clients
		PlayerCharacter* playerChar = (PlayerCharacter*)mWorldServerNetworkController->ServerCreateNetworkedObjectByClass(PlayerCharacter::GetStaticClass());
		if (playerChar != nullptr)
		{
			playerChar->SetPosition(Ogre::Vector3(130.0f, 2.0f, 130.0f));
			playerChar->ReplicateInitialData();
		}
	}

}

#endif
