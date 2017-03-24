#ifndef HIKARI_CLIENTNETWORKCONTROLLER_H
#define HIKARI_CLIENTNETWORKCONTROLLER_H

#include "network_controller.h"

namespace Hikari
{
	class ClientNetworkController : public Hikari::NetworkController
	{
		DEFINE_CLASS(Hikari::ClientNetworkController, Hikari::NetworkController)

			ClientNetworkController(GameInstance* arg_gameinstance);
	};
}

#endif
