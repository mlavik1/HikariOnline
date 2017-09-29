#ifndef HIKARI_WORLDSERVER_H
#define HIKARI_WORLDSERVER_H

#include "Core/Networking/server_connection.h"
#include "Core/Networking/client_connection.h"
#include "Core/Networking/net_message.h"
#include <vector>
#include "Core/Engine/game_engine.h"
#include <tuple>
#include "Core/Networking/player.h"
#include "Core/Controller/world_server_network_controller.h"

namespace Hikari
{
	typedef std::tuple<int, NetMessage*> ClientNetMessage;

	class ClientNetworkController;

	class WorldServer
	{
	private:
		WorldServerNetworkController* mWorldServerNetworkController;
		Hikari::ServerConnection* mGameServerConnection;
		Hikari::ClientConnection* mClientConnection;

		std::unordered_map<int, ClientConnectionData> mConnectedClients;
		std::unordered_map<int, ClientNetworkController*> mClientNetworkControllers;

		std::vector<NetMessage*> mIncomingGameServerMessages;
		std::vector<ClientNetMessage> mIncomingClientMessages;

		std::vector<NetMessage*> mOutgoingGameServerMessages;
		std::vector<ClientNetMessage> mOutgoingClientMessages;

		std::unordered_set<NetMessage*> mPendingDeleteNetMessages;

		void handleIncomingClientConnectionRequest(const ClientConnectionData& arg_conndata);

	public:
		WorldServer();
		~WorldServer();

		void Initialise();
		bool ConnectToGameServer();
		void Update();

		void SendMessageToClient(int arg_clientid, NetMessage* arg_message);
		void SendMessageToAllClients(NetMessage* arg_message);

		void SendMessageToGameServer(int arg_serverid, NetMessage* arg_message);

		std::unordered_map<int, ClientConnectionData> GetConnectedClients() { return mConnectedClients; }

		ClientNetworkController* GetClientNetworkController(int arg_clientid);

	};
}

#endif
