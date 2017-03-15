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

			NetMessage incomingMessage(arg_message);
			mIncomingClientMessages.push_back(ClientNetMessage(arg_clientid, incomingMessage));
		});

		mGameServerConnection->SetMessageCallback([&](const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from game server";

			NetMessage incomingMessage(arg_message);
			mIncomingGameServerMessages.push_back(incomingMessage);
		});
	}

	bool WorldServer::ConnectToGameServer()
	{
		bool bConnected = mGameServerConnection->Connect("127.0.0.1", PORT_GAMESERVER_WORLDSERVER);

		if (bConnected)
		{
			NetMessage connMessage(NetMessageType::EstablishConnection, "");
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

		for (NetMessage& outMessage : mOutgoingGameServerMessages)
		{
			mGameServerConnection->SendNetworkMessage(&outMessage);
		}
		for (ClientNetMessage& outMessage : mOutgoingClientMessages)
		{
			mClientConnection->SendNetworkMessage(std::get<0>(outMessage), &std::get<1>(outMessage));
		}


		for (NetMessage& netMessage: mIncomingGameServerMessages)
		{
			const NetMessageType& messageType = netMessage.GetMessageType();
			switch (messageType)
			{

			}
		}

		for (ClientNetMessage& message : mIncomingClientMessages)
		{
			const NetMessage& netMessage = std::get<1>(message);
			int clientID = std::get<0>(message);
			const NetMessageType& messageType = netMessage.GetMessageType();
			switch (messageType)
			{
				case NetMessageType::EstablishConnection:
					std::string clientAccountName = netMessage.GetMessageData();
					ClientConnectionData clientConnData;
					clientConnData.mAccountName = clientAccountName;
					clientConnData.mClientID = clientID;
					clientConnData.mIPAddress = mClientConnection->GetSocketIPAddress(clientID);
					mConnectedClients.push_back(clientConnData);
					NetMessage msgAck(NetMessageType::ConnectionEstablishedAck, "");
					mOutgoingClientMessages.push_back(ClientNetMessage(clientID, msgAck));
				break;
			}
		}

		mOutgoingGameServerMessages.clear();
	}
}
