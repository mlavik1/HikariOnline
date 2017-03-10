#include "game_server.h"
#include <sdl2/SDL_net.h>

namespace Hikari
{
	GameServer::GameServer()
	{
		SDLNet_Init();

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

		for (ClientNetMessage& clientNetMessage : mIncomingWorldServerMessages)
		{
			const int& clientID = std::get<0>(clientNetMessage);
			const NetMessage& netMessage = std::get<1>(clientNetMessage);

			LOG_INFO() << "message: " << netMessage.GetMessage();

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

			LOG_INFO() << "message: " << netMessage.GetMessage();

			switch (netMessage.GetMessageType())
			{
			case NetMessageType::EstablishConnection:
				ClientConnectionData clientConn;
				clientConn.mClientID = clientID;
				clientConn.mIPAddress = mWorldServerConnection->GetSocketIPAddress(clientID);
				mConnectedClients.push_back(clientConn);
				LOG_INFO() << "Established connection with client: " << clientConn.mIPAddress;
				NetMessage msgAck(NetMessageType::ConnectionEstablishedAck, "");
				mOutgoingClientMessages.push_back(ClientNetMessage(clientID, msgAck));
				break;
			}
		}

		for (ClientNetMessage& outMessage : mOutgoingWorldServerMessages)
		{
			const int& clientID = std::get<0>(outMessage);
			const NetMessage& netMessage = std::get<1>(outMessage);
			std::string msgStr = netMessage.GetStringRepresentation();
			mWorldServerConnection->SendNetworkMessage(clientID, msgStr.c_str(), msgStr.length());
		}

		for (ClientNetMessage& outMessage : mOutgoingClientMessages)
		{
			const int& clientID = std::get<0>(outMessage);
			const NetMessage& netMessage = std::get<1>(outMessage);
			std::string msgStr = netMessage.GetStringRepresentation();
			if (clientID == -1)
			{
				mClientConnection->SendNetworkMessageToAll(msgStr.c_str(), msgStr.length());
			}
			else
			{
				mClientConnection->SendNetworkMessage(clientID, msgStr.c_str(), msgStr.length());
			}
		}

		mIncomingWorldServerMessages.clear();
		mIncomingClientMessages.clear();
		mOutgoingWorldServerMessages.clear();
		mOutgoingClientMessages.clear();
	}
}
