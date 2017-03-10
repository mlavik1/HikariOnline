#ifndef HIKARI_WORLDSERVER_H
#define HIKARI_WORLDSERVER_H

#include "Core/Networking/server_connection.h"
#include "Core/Networking/client_connection.h"
#include "Core/Networking/net_message.h"
#include <vector>
#include "Core/Engine/game_engine.h"

namespace Hikari
{
	class WorldServer
	{
	private:
		Hikari::ServerConnection* mGameServerConnection;
		Hikari::ClientConnection* mClientConnection;

		std::vector<NetMessage> mOutgoingGameServerMessages;
		GameEngine* mGameEngine;
		GameInstance* mGameInstance;

	public:
		WorldServer();
		~WorldServer();

		void Initialise();
		bool ConnectToGameServer();
		void SetReady();
		void Update();
	};
}

#endif
