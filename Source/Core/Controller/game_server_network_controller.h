#ifndef HIKARI_GAMESERVERNETWORKCONTROLLER_H
#define HIKARI_GAMESERVERNETWORKCONTROLLER_H

/*=============================================================================================
Class used for communication between game server and clients.
==============================================================================================*/

#include "network_controller.h"
#include "Core/Networking/net_message_data.h"
#include <string>

namespace Hikari
{
	class GameServerNetworkController : public Hikari::NetworkController
	{
		DEFINE_CLASS(Hikari::GameServerNetworkController, Hikari::NetworkController)

	public:
		GameServerNetworkController();

		void ServerSendMessage(std::string arg_message);
		void ClientSendMessage(std::string arg_message); // MOVE TO CLIENT NETWORK CONTROLLER !!!

		DEFINE_FUNCTION(ServerSendMessage, std::string)
		DEFINE_FUNCTION(ClientSendMessage, std::string)

		BEGIN_REGISTER_CLASSPROPERTIES(Hikari::GameServerNetworkController)
			REGISTER_CLASS_FUNCTION(Hikari::GameServerNetworkController, ServerSendMessage)
			REGISTER_CLASS_FUNCTION(Hikari::GameServerNetworkController, ClientSendMessage)
		END_REGISTER_CLASSPROPERTIES(Hikari::GameServerNetworkController)
	};
}

#endif
