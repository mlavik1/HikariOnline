#include "client.h"
#include "Core/Debug/st_assert.h"
#include "Core/Controller/client_controller.h"
#include "Core/Controller/ingame_controller.h"

namespace Hikari
{
	Client::Client(GameInstance* arg_gameinstance)
	{
		__Assert(arg_gameinstance != nullptr);
		mGameInstance = arg_gameinstance;

		// TEMP!  this should happen hafter joining game
		mInGameController = new InGameController(this);
		mClientController = mInGameController;
	}

	void Client::TickClient(float arg_deltatime)
	{
#ifdef HIKARI_CLIENT
		if (mClientController != nullptr)
		{
			mClientController->Tick(arg_deltatime);
		}
#endif
	}

	InGameController* Client::GetInGameController()
	{
		return mInGameController;
	}

	GameInstance* Client::GetGameInstance()
	{
		return mGameInstance;
	}
}
