#include "game_engine.h"
#include "Core/Engine/game_instance.h"

#include "Core/Debug/debug.h"
#include "Core/Debug/st_assert.h"
#include "Core/Window/game_window.h"

namespace Hikari
{
	__ImplementSingleton(GameEngine)

	GameEngine::GameEngine()
	{
		__ConstructSingleton(GameEngine)

		mOgreRoot = nullptr;
		mGameWindow = nullptr;
	}

	void GameEngine::Initialise()
	{
		LOG_INFO() << "Initialising game engine";
		mOgreRoot = new Ogre::Root("plugins_d.cfg");
		__Assert(mOgreRoot->showConfigDialog());

		mGameWindow = new GameWindow(this);
	}

	void GameEngine::TickGameInstance(GameInstance* arg_instance)
	{
		__Assert(arg_instance != nullptr);

		arg_instance->Tick();

#ifdef HIKARI_CLIENT
		mOgreRoot->renderOneFrame();
#endif
	}

	GameInstance* GameEngine::CreateGameInstance()
	{
		GameInstance* instance = new GameInstance(this);
		return instance;
	}
}
