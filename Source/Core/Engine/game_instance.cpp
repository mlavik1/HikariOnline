#include "game_instance.h"

#include "Core/Engine/game_engine.h"
#include "Core/Window/game_window.h"
#include "Core/Debug/st_assert.h"
#include "Core/World/world.h"
#include "Core/Managers/input_manager.h"
#include "Core/Managers/tick_manager.h"
#include "Core/Managers/time_manager.h"
#include "Core/Engine/client.h"
#include "Core/Managers/window_manager.h"

namespace Hikari
{
	GameInstance::GameInstance(GameEngine* arg_engine)
	{
		__Assert(arg_engine != nullptr);
		__Assert(arg_engine->GetOgreRoot() != nullptr);

		LOG_INFO() << "Creating game instance";

		mGameEngine = arg_engine;
		Ogre::SceneManager* sceneManager = mGameEngine->GetOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
		mWorld = new World(this, sceneManager);

		mGameWindow = new GameWindow(this);
		mTickManager = new TickManager();
		mInputManager = new InputManager(this);
	

#ifdef HIKARI_CLIENT
		mWindowManager = new WindowManager(this);
		mClient = new Client(this);
#endif
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
		float currentTime = TimeManager::Instance()->GetTimeSeconds();
		float deltaTime = currentTime - mLastTime;
		
#ifdef HIKARI_CLIENT
		mClient->TickClient(deltaTime);
#endif
		mTickManager->Tick(deltaTime);

		mLastTime = currentTime;
	}
}
