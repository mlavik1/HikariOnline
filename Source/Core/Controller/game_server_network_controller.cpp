#include "game_server_network_controller.h"
#include "Core/Debug/debug.h"

namespace Hikari
{
	IMPLEMENT_CLASS(Hikari::GameServerNetworkController)

	REGISTER_CLASSPROPERTIES(Hikari::GameServerNetworkController)

	GameServerNetworkController::GameServerNetworkController(GameInstance* arg_gameinstance)
		:NetworkController(arg_gameinstance)
	{
		//CALL_FUNCTION(this, TestFunction, 2, 3.0f);
	}

	void GameServerNetworkController::TestFunction(int a, float b)
	{
		LOG_INFO() << "Called TestFunction";
		LOG_INFO() << a;
		LOG_INFO() << b;
	}
}
