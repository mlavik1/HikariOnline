#include "world_server.h"
#include "Core/Debug/debug.h"
#include "Core/World/world_factory.h"
#include "Core/Engine/game_instance.h"
#include "Core/World/world.h"

namespace Hikari
{
	WorldServer::WorldServer()
	{
		mGameServerConnection = new Hikari::ServerConnection();
		mClientConnection = new Hikari::ClientConnection(1000);
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
		if (mGameServerConnection != nullptr && mGameServerConnection->IsConnected())
		{
			mGameServerConnection->FetchNewMessages();
		}
		if (mClientConnection != nullptr && mClientConnection->IsConnected())
		{
			mClientConnection->FetchNewMessages();
		}

		for (NetMessage* outMessage : mOutgoingGameServerMessages)
		{
			mGameServerConnection->SendNetworkMessage(outMessage);
		}
		for (ClientNetMessage& outMessage : mOutgoingClientMessages)
		{
			mClientConnection->SendNetworkMessage(std::get<0>(outMessage), std::get<1>(outMessage));
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
					std::string clientAccountName = netMessage->GetMessageData();
					ClientConnectionData clientConnData;
					clientConnData.mAccountName = clientAccountName;
					clientConnData.mClientID = clientID;
					clientConnData.mIPAddress = mClientConnection->GetSocketIPAddress(clientID);
					handleIncomingClientConnectionRequest(clientConnData);
				break;
			}
		}

		// Delete all received/sent NetMessage instances. Multiple client messages may reference the same NetMessage.
		for (NetMessage* msg : mPendingDeleteNetMessages)
		{
			delete(msg);
		}

		mOutgoingGameServerMessages.clear();
		mOutgoingClientMessages.clear();
		mPendingDeleteNetMessages.clear();
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
			mOutgoingClientMessages.push_back(ClientNetMessage(client.mClientID, arg_message));
		}
		mPendingDeleteNetMessages.insert(arg_message);
	}

	void WorldServer::SendMessageToGameServer(int arg_serverid, NetMessage* arg_message)
	{
		mOutgoingGameServerMessages.push_back(arg_message);
		mPendingDeleteNetMessages.insert(arg_message);
	}




	void WorldServer::handleIncomingClientConnectionRequest(const ClientConnectionData& arg_conndata)
	{
		mConnectedClients.push_back(arg_conndata);
		NetMessage* msgAck = new NetMessage(NetMessageType::ConnectionEstablishedAck, "");
		mOutgoingClientMessages.push_back(ClientNetMessage(arg_conndata.mClientID, msgAck));
	}

}
