#ifndef HIKARI_CLIENTNETWORKCONTROLLER_H
#define HIKARI_CLIENTNETWORKCONTROLLER_H

/*=============================================================================================
Controller for communication between a server (GameServer or WorldServer) and a client.

==============================================================================================*/

#include "network_controller.h"

namespace Hikari
{
	class PlayerCharacter;

	class ClientNetworkController : public Hikari::NetworkController
	{
		DEFINE_CLASS(Hikari::ClientNetworkController, Hikari::NetworkController)

	public:
		ClientNetworkController();
		/*
		void WorldServerCreatePlayer();
		void ClientCreatePlayer(NetGUID arg_netguid, bool arg_owner);
		PlayerCharacter* CreatePlayerInternal();

		BEGIN_REGISTER_CLASSPROPERTIES(Hikari::ClientNetworkController)
			REGISTER_CLASS_FUNCTION(Hikari::ClientNetworkController, ClientCreatePlayer)
		END_REGISTER_CLASSPROPERTIES(Hikari::ClientNetworkController)
		*/
	};
}

#endif
