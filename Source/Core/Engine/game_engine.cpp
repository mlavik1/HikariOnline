#include "game_engine.h"
#include "Core/Engine/game_instance.h"

namespace Hikari
{
	GameEngine::GameEngine()
	{
		mOgreRoot = new Ogre::Root("plugins_d.cfg");
	}

	GameInstance* GameEngine::CreateGameInstance()
	{
		GameInstance* instance = new GameInstance(this);
		return instance;
	}
}
