#include "game_engine.h"
#include "Core/Engine/game_instance.h"

#include "Core/Debug/debug.h"
#include "Core/Debug/st_assert.h"

namespace Hikari
{
	GameEngine::GameEngine()
	{
		LOG_INFO() << "Creating game engine";
		mOgreRoot = new Ogre::Root("plugins_d.cfg");
		__Assert(mOgreRoot->showConfigDialog());
	}

	GameInstance* GameEngine::CreateGameInstance()
	{
		GameInstance* instance = new GameInstance(this);
		return instance;
	}
}
