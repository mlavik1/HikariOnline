#include "game_instance.h"

#include "Core/Engine/game_engine.h"
#include "Core/Window/game_window.h"
#include "Core/Debug/st_assert.h"
#include "Core/World/world.h"
#include "Core/Managers/input_manager.h"
#include "Core/Managers/tick_manager.h"

namespace Hikari
{
	GameInstance::GameInstance(GameEngine* arg_engine)
	{
		__Assert(arg_engine != nullptr);
		__Assert(arg_engine->GetOgreRoot() != nullptr);

		LOG_INFO() << "Creating game instance";

		mGameEngine = arg_engine;
		mGameWindow = new GameWindow();
		mTickManager = new TickManager();
		mInputManager = new InputManager(this);
		
		Ogre::SceneManager* sceneManager = mGameEngine->GetOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
		mWorld = new World(this, sceneManager);
	}

	GameInstance::~GameInstance()
	{
		delete mInputManager;
		delete mTickManager;
		delete mWorld;
	}

	void GameInstance::Tick()
	{
		Ogre::WindowEventUtilities::messagePump();
		mInputManager->CaptureInput();
		mTickManager->Tick(0.01f); // TEMP- TODO: get delta time
	}
}
