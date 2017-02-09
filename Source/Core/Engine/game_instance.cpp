#include "game_instance.h"

#include "Core/Engine/game_engine.h"
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
		mTickManager = new TickManager();
		mInputManager = new InputManager(this);
		
		Ogre::SceneManager* sceneManager = mGameEngine->GetOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
		mWorld = new World(this, sceneManager);
	}

	void GameInstance::Tick()
	{

	}
}
