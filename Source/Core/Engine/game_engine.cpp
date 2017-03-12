#include "game_engine.h"
#include "Core/Engine/game_instance.h"
#include "Core/Managers/time_manager.h"

#include "Core/Debug/debug.h"
#include "Core/Debug/st_assert.h"
#include "Core/Window/game_window.h"
#include <sdl2/SDL.h>
#include <sdl2/SDL_net.h>

namespace Hikari
{
	__ImplementSingleton(GameEngine)

	GameEngine::GameEngine()
	{
		__ConstructSingleton(GameEngine)

		mOgreRoot = nullptr;
	}

	GameEngine::~GameEngine()
	{
		for (GameInstance* gameInstance : mGameInstances)
		{
			delete gameInstance;
		}
		SDLNet_Quit();
	}

	void GameEngine::Initialise()
	{
		LOG_INFO() << "Initialising game engine";

		SDL_Init(SDL_INIT_EVERYTHING);
		SDLNet_Init();

		mOgreRoot = new Ogre::Root("plugins_d.cfg");
		__Assert(mOgreRoot->showConfigDialog());

		TimeManager::Create();
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
