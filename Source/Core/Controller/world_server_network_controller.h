#ifndef HIKARI_WORLDSERVERNETWORKCONTROLLER_H
#define HIKARI_WORLDSERVERNETWORKCONTROLLER_H

#include "network_controller.h"

namespace Hikari
{
	class WorldServerNetworkController : public Hikari::NetworkController
	{
		DEFINE_CLASS(Hikari::WorldServerNetworkController, Hikari::NetworkController)

	public:
		WorldServerNetworkController(GameInstance* arg_gameinstance);
	};
}

#endif
