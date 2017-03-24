#ifndef HIKARI_GAMESERVER_H
#define HIKARI_GAMESERVER_H

#include "Core/Debug/debug.h"
#include "Core/Networking/client_connection.h"
#include "Core/Networking/net_message.h"
#include <vector>
#include <tuple>
#include <string>
#include "Core/Managers/network_manager.h"
#include "Core/Controller/game_server_network_controller.h"
#include "Core/Controller/client_network_controller.h"
#include <unordered_map>

namespace Hikari
{
	typedef std::tuple<int, NetMessage> ClientNetMessage;

	class GameInstance;

	class WorldServerConnectionData
	{
	public:
		std::string mIPAddress;
		int mClientID;
	};

	class GameServer
	{
		class ClientConnectionData
		{
		public:
			std::string mIPAddress;
			int mClientID;
			std::string mAccountName;
		};

	private:
		GameInstance* mGameInstance;
		Hikari::ClientConnection* mWorldServerConnection;
		Hikari::ClientConnection* mClientConnection;
		std::vector<WorldServerConnectionData> mConnectedWorldServers;
		std::vector<ClientConnectionData> mConnectedClients;

		std::vector<ClientNetMessage> mIncomingWorldServerMessages;
		std::vector<ClientNetMessage> mIncomingClientMessages;

		std::vector<ClientNetMessage> mOutgoingWorldServerMessages;
		std::vector<ClientNetMessage> mOutgoingClientMessages;

		GameServerNetworkController* mGameServerNetworkController;

		std::unordered_map<int, ClientNetworkController*> mClientNetworkControllers;

	public:
		GameServer(GameInstance* arg_gameinstance);
		~GameServer();

		void Initialise();
		void Update();

		void EstablishConnectionWithClient(const ClientConnectionData& arg_clientconndata);

		ClientNetworkController* GetClientNetworkController(int arg_clientid);
	};
}

#endif
