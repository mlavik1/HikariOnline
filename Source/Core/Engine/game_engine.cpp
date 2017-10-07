#include "game_engine.h"

#include <sdl2/SDL.h>
#include <sdl2/SDL_net.h>

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
#include "Core/Networking/player_manager.h"
#include "Core/Task/task_manager.h"
#ifdef HIKARI_WORLDSERVER
#include "Core/Engine/world_server.h"
#endif
#ifdef HIKARI_GAMESERVER
#include "Core/Engine/game_server.h"
#endif

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
		delete mInputManager;
		delete mTickManager;
		delete mWorld;

		SDLNet_Quit();
	}

	void GameEngine::Initialise()
	{
		LOG_INFO() << "Initialising game engine";

		SDL_Init(SDL_INIT_EVERYTHING);
		SDLNet_Init();

#if defined(HIKARI_CLIENT) || defined(HIKARI_WORLDSERVER)
		mOgreRoot = new Ogre::Root("plugins_d.cfg");
		__Assert(mOgreRoot->showConfigDialog());
#endif

#if defined(HIKARI_CLIENT) || defined(HIKARI_WORLDSERVER)
		Ogre::SceneManager* sceneManager = GetOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
		mWorld = new World(sceneManager);
#endif

		mTickManager = new TickManager();

		mNetworkManager = new NetworkManager();

		mPlayerManager = new PlayerManager();

		mTaskManager = new TaskManager();

#ifdef HIKARI_CLIENT

		// TEMP - todo :  NOTE: must come before MyGUI::OGrePlatform is initialised...
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/OgreExport.zip", "Zip");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/TerrainTest.zip", "Zip");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/MyGUIMedia.zip", "Zip");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/Skybox2.zip", "Zip");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/Terrain1.zip", "Zip");
		//Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Layouts.zip", "Zip");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Resources/GUI/Layouts", "FileSystem", "GUILayouts");
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		mGameWindow = new GameWindow();
#elif defined(HIKARI_WORLDSERVER)
		GameEngine::Instance()->GetOgreRoot()->initialise(true, "Hikari")->setHidden(true); // because some things fail if we don't have a window
#endif

#ifdef HIKARI_CLIENT
		mInputManager = new InputManager();
		mWindowManager = new WindowManager();
		mClient = new Client();
#endif
#ifdef HIKARI_WORLDSERVER
		mWorldServer = new WorldServer();
#endif
#ifdef HIKARI_GAMESERVER
		mGameServer = new GameServer();
#endif

		TimeManager::Create();
	}

	void GameEngine::TickEngine()
	{
#ifdef HIKARI_CLIENT
		mOgreRoot->renderOneFrame();
#endif

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
#ifdef HIKARI_GAMESERVER
		mGameServer->Update();
#endif

		mTickManager->Tick(deltaTime);

		mTaskManager->ProcessTasks();

		mLastTime = currentTime;
	}

}
