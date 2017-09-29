#ifndef HIKARI_CLIENT_H
#define HIKARI_CLIENT_H

#include "Core/Networking/server_connection.h"
#include "Core/Networking/net_message.h"
#include <vector>
#include <string>
#include "Core/Controller/game_server_network_controller.h"
#include "Core/Controller/client_network_controller.h"
#include "Core/Controller/world_server_network_controller.h"

namespace Hikari
{
	class ClientController;
	class InGameController;

	class Client
	{
	protected:
		ClientController* mClientController;
		InGameController* mInGameController; // null, if not in-game
		ServerConnection* mGameServerConnection;
		ServerConnection* mWorldServerConnection;
		std::vector<NetMessage*> mOutgoingGameServerMessages;
		std::vector<NetMessage*> mOutgoingWorldServerMessages;
		std::vector<NetMessage*> mIncomingGameServerMessages;
		std::vector<NetMessage*> mIncomingWorldServerMessages;
		std::string mAccountName;
		GameServerNetworkController* mGameServerNetworkController;
		WorldServerNetworkController* mWorldServerNetworkController;
		ClientNetworkController* mClientNetworkController;

	public:
		Client();
		~Client();

		void TickClient(float arg_deltatime);
		void ConnectToGameServer(const char* arg_ip);
		void ConnectToWorldServer(const char* arg_ip);
		void SendOutgoingNetworkMessages();
		void FetchIncomingNetworkMessages();
		void HandleIncomingNetworkMessages();

		void SendMessageToGameServer(NetMessage* arg_message);
		void SendMessageToWorldServer(NetMessage* arg_message);

		InGameController* GetInGameController();

		GameServerNetworkController* GetGameServerNetworkController();
		ClientNetworkController* GetClientNetworkController();
	};
}

#endif
