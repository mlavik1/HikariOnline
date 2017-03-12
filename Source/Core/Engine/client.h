#ifndef HIKARI_CLIENT_H
#define HIKARI_CLIENT_H

#include "Core/Networking/server_connection.h"
#include "Core/Networking/net_message.h"
#include <vector>
#include <string>

namespace Hikari
{
	class GameInstance;
	class ClientController;
	class InGameController;

	class Client
	{
	protected:
		GameInstance* mGameInstance;
		ClientController* mClientController;
		InGameController* mInGameController; // null, if not in-game
		ServerConnection* mGameServerConnection;
		ServerConnection* mWorldServerConnection;
		std::vector<NetMessage*> mOutgoingGameServerMessages;
		std::vector<NetMessage*> mOutgoingWorldServerMessages;
		std::vector<NetMessage*> mIncomingGameServerMessages;
		std::vector<NetMessage*> mIncomingWorldServerMessages;
		std::string mAccountName;

	public:
		Client(GameInstance* arg_gameinstance);
		~Client();

		void TickClient(float arg_deltatime);
		void ConnectToGameServer(const char* arg_ip);
		void ConnectToWorldServer(const char* arg_ip);
		void SendOutgoingNetworkMessages();
		void FetchIncomingNetworkMessages();
		void HandleIncomingNetworkMessages();

		InGameController* GetInGameController();
		GameInstance* GetGameInstance();
	};
}

#endif
