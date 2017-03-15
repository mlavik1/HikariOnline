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
#include "Core/Managers/network_manager.h"
#include "Core/Engine/world_server.h"

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

		mTickManager = new TickManager();
		
		mNetworkManager = new NetworkManager();

#ifdef HIKARI_CLIENT
		mGameWindow = new GameWindow(this);
#else
		GameEngine::Instance()->GetOgreRoot()->initialise(true, "Hikari")->setHidden(true); // because some things fail if we don't have a window
#endif

#ifdef HIKARI_CLIENT
		mInputManager = new InputManager(this);
		mWindowManager = new WindowManager(this);
		mClient = new Client(this);
#endif
#ifdef HIKARI_WORLDSERVER
		mWorldServer = new WorldServer();
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
#ifdef HIKARI_CLIENT
		Ogre::WindowEventUtilities::messagePump();
		mInputManager->CaptureInput();
#endif
		float currentTime = TimeManager::Instance()->GetTimeSeconds();
		float deltaTime = currentTime - mLastTime;
		
#ifdef HIKARI_CLIENT
		mClient->TickClient(deltaTime);
#endif
#ifdef HIKARI_WORLDSERVER
		mWorldServer->Update();
#endif
		
		mTickManager->Tick(deltaTime);

		mLastTime = currentTime;
	}
}
