#ifndef HIKARI_WORLDSERVER_H
#define HIKARI_WORLDSERVER_H

#include "Core/Networking/server_connection.h"
#include "Core/Networking/client_connection.h"
#include "Core/Networking/net_message.h"
#include <vector>
#include "Core/Engine/game_engine.h"
#include <tuple>

namespace Hikari
{
	typedef std::tuple<int, NetMessage> ClientNetMessage;

	class ClientConnectionData
	{
	public:
		std::string mIPAddress;
		int mClientID;
		std::string mAccountName;
	};

	class WorldServer
	{
	private:
		Hikari::ServerConnection* mGameServerConnection;
		Hikari::ClientConnection* mClientConnection;

		std::vector<NetMessage> mIncomingGameServerMessages;
		std::vector<ClientNetMessage> mIncomingClientMessages;

		std::vector<NetMessage> mOutgoingGameServerMessages;
		std::vector<ClientNetMessage> mOutgoingClientMessages;

		std::vector<ClientConnectionData> mConnectedClients;

	public:
		WorldServer();
		~WorldServer();

		void Initialise();
		bool ConnectToGameServer();
		void Update();
	};
}

#endif
