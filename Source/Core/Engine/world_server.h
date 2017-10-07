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
#include "Core/Task/ws_establish_client_connection_task.h"

namespace Hikari
{
	typedef std::tuple<int, NetMessage*> ClientNetMessage;

	class ClientNetworkController;

	class WorldServer
	{
	private:
		WorldServerNetworkController* mWorldServerNetworkController;
		Hikari::ServerConnection* mGameServerConnection;

		/*** Client ***/

		Hikari::ClientConnection* mClientConnection;
		std::unordered_map<int, ClientConnectionData> mConnectedClients;
		std::unordered_map<int, ClientNetworkController*> mClientNetworkControllers;


		/*** Messages ***/

		std::vector<NetMessage*> mIncomingGameServerMessages;
		std::vector<ClientNetMessage> mIncomingClientMessages;

		std::vector<NetMessage*> mOutgoingGameServerMessages;
		std::vector<ClientNetMessage> mOutgoingClientMessages;

		std::unordered_set<NetMessage*> mPendingDeleteNetMessages;

		/** Task responsible for setting up a connection to the client. */
		std::unordered_map<std::string, WSEstablishClientConnectionTask*> mEstablishClientConnectionTasks;

	public:
		WorldServer();
		~WorldServer();

		void Initialise();
		bool ConnectToGameServer();
		void Update();

		/** Sends a message to client, with the given client ID. */
		void SendMessageToClient(int arg_clientid, NetMessage* arg_message);

		/** Sends a message to all connected clients. */
		void SendMessageToAllClients(NetMessage* arg_message);

		/**
		* Registers a client. Will create a ClientNetworkController and add client to list of connected clients.
		* @param arg_conndata Connection Data for the client.
		* @param arg_netguid  NetGUID for the client.
		*/
		void RegisterClient(const ClientConnectionData& arg_conndata, NetGUID arg_netguid);

		/** Sends a message to the GameServer */
		void SendMessageToGameServer(NetMessage* arg_message);

		std::unordered_map<int, ClientConnectionData> GetConnectedClients() { return mConnectedClients; }

		ClientNetworkController* GetClientNetworkController(int arg_clientid);
		WorldServerNetworkController* GetWorldServerNetworkController() { return mWorldServerNetworkController; }

	};
}

#endif
