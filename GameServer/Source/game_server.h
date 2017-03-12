#ifndef HIKARI_GAMESERVER_H
#define HIKARI_GAMESERVER_H

#include "Core/Debug/debug.h"
#include "Core/Networking/client_connection.h"
#include "Core/Networking/net_message.h"
#include <vector>
#include <tuple>
#include <string>

namespace Hikari
{
	typedef std::tuple<int, NetMessage> ClientNetMessage;

	class WorldServerConnectionData
	{
	public:
		std::string mIPAddress;
		int mClientID;
	};

	class ClientConnectionData
	{
	public:
		std::string mIPAddress;
		int mClientID;
		std::string mAccountName;
	};

	class GameServer
	{
	private:
		Hikari::ClientConnection* mWorldServerConnection;
		Hikari::ClientConnection* mClientConnection;
		std::vector<WorldServerConnectionData> mConnectedWorldServers;
		std::vector<ClientConnectionData> mConnectedClients;

		std::vector<ClientNetMessage> mIncomingWorldServerMessages;
		std::vector<ClientNetMessage> mIncomingClientMessages;

		std::vector<ClientNetMessage> mOutgoingWorldServerMessages;
		std::vector<ClientNetMessage> mOutgoingClientMessages;

	public:
		GameServer();
		~GameServer();

		void Initialise();
		void Update();
	};
}

#endif
