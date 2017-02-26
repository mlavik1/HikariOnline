#include "client_controller.h"
#include "Core/Debug/st_assert.h"

namespace Hikari
{
	ClientController::ClientController(Client* arg_client)
	{
		__Assert(arg_client != nullptr);
		mClient = arg_client;
	}

	void ClientController::Tick(float arg_deltatime)
	{
	}
}
