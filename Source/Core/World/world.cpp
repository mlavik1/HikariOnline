#include "world.h"

#include "Core/Debug/st_assert.h"
#include "Core/Engine/game_instance.h"

namespace Hikari
{
	World::World(GameInstance* arg_gameinstance, Ogre::SceneManager* arg_scenemanager)
	{
		__Assert(arg_gameinstance != nullptr);
		__Assert(arg_scenemanager != nullptr);
		mGameInstance = arg_gameinstance;
		mSceneManager = arg_scenemanager;
	}
}
