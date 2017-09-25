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
#include "Core/Controller/world_server_network_controller.h"
#include "Core/Controller/client_network_controller.h"
#include <unordered_map>
#include <unordered_set>

namespace Hikari
{
	typedef std::tuple<int, NetMessage*> ClientNetMessage;

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
		Hikari::ClientConnection* mWorldServerConnection;
		Hikari::ClientConnection* mClientConnection;
		std::vector<WorldServerConnectionData> mConnectedWorldServers;
		std::unordered_map<int, ClientConnectionData> mConnectedClients;

		std::vector<ClientNetMessage> mIncomingWorldServerMessages;
		std::vector<ClientNetMessage> mIncomingClientMessages;

		std::vector<ClientNetMessage> mOutgoingWorldServerMessages;
		std::vector<ClientNetMessage> mOutgoingClientMessages;

		GameServerNetworkController* mGameServerNetworkController;

		std::unordered_map<int, WorldServerNetworkController*> mWorldServerNetworkControllers;
		std::unordered_map<int, ClientNetworkController*> mClientNetworkControllers;

		std::unordered_set<NetMessage*> mPendingDeleteNetMessages;

		void establishConnectionWithWorldServer(const WorldServerConnectionData& arg_conndata);
		void establishConnectionWithClient(const ClientConnectionData& arg_clientconndata);

	public:
		GameServer();
		~GameServer();

		void Initialise();
		void Update();

		const std::unordered_map<int, ClientConnectionData>& GetConnectedClients();
		const ClientConnectionData* GetClientConnectionData(int arg_clientid);

		ClientNetworkController* GetClientNetworkController(int arg_clientid);

		void SendMessageToClient(int arg_clientid, NetMessage* arg_message);
		void SendMessageToAllClients(NetMessage* arg_message);

		void SendMessageToWorldServer(int arg_serverid, NetMessage* arg_message);

	};
}

#endif
