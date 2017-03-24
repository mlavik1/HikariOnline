#ifndef HIKARI_GAMESERVERNETWORKCONTROLLER_H
#define HIKARI_GAMESERVERNETWORKCONTROLLER_H

#include "network_controller.h"

namespace Hikari
{
	class GameServerNetworkController : public Hikari::NetworkController
	{
		DEFINE_CLASS(Hikari::GameServerNetworkController, Hikari::NetworkController)

	public:
		GameServerNetworkController(GameInstance* arg_gameinstance);

		void TestFunction(int a, float b);


		DEFINE_FUNCTION(TestFunction, int, float)

		BEGIN_REGISTER_CLASSPROPERTIES(Hikari::GameServerNetworkController)
		REGISTER_CLASS_FUNCTION(Hikari::GameServerNetworkController, TestFunction)
		END_REGISTER_CLASSPROPERTIES(Hikari::GameServerNetworkController)
	};
}

#endif
