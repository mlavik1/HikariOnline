#include "game_instance.h"

#include "Core/Engine/game_engine.h"
#include "Core/Debug/st_assert.h"
#include "Core/World/world.h"

namespace Hikari
{
	GameInstance::GameInstance(GameEngine* arg_engine)
	{
		__Assert(arg_engine != nullptr);
		__Assert(arg_engine->GetOgreRoot() != nullptr);

		mGameEngine = arg_engine;
		Ogre::SceneManager* sceneManager = mGameEngine->GetOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
		mWorld = new World(this, sceneManager);
	}
}
