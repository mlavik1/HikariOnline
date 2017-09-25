#ifndef HIKARI_GAMESERVERNETWORKCONTROLLER_H
#define HIKARI_GAMESERVERNETWORKCONTROLLER_H

#include "network_controller.h"
#include "Core/Networking/net_message_data.h"

namespace Hikari
{
	class GameServerNetworkController : public Hikari::NetworkController
	{
		DEFINE_CLASS(Hikari::GameServerNetworkController, Hikari::NetworkController)

	public:
		GameServerNetworkController();

		void ServerSendMessage(NetMessageData::ChatMessage arg_message);
		void ClientSendMessage(NetMessageData::ChatMessage arg_message); // MOVE TO CLIENT NETWORK CONTROLLER !!!

		DEFINE_FUNCTION(ServerSendMessage, NetMessageData::ChatMessage)
		DEFINE_FUNCTION(ClientSendMessage, NetMessageData::ChatMessage)

		BEGIN_REGISTER_CLASSPROPERTIES(Hikari::GameServerNetworkController)
			REGISTER_CLASS_FUNCTION(Hikari::GameServerNetworkController, ServerSendMessage)
			REGISTER_CLASS_FUNCTION(Hikari::GameServerNetworkController, ClientSendMessage)
		END_REGISTER_CLASSPROPERTIES(Hikari::GameServerNetworkController)
	};
}

#endif
