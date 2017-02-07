#ifndef HIKARI_WORLD_H
#define HIKARI_WORLD_H

#include "OGRE/Ogre.h"

namespace Hikari
{
	class GameInstance;

	class World
	{
	private:
		Ogre::SceneManager* mSceneManager;
		GameInstance* mGameInstance;

	public:
		World(GameInstance* arg_gameinstance, Ogre::SceneManager* arg_scenemanager);

		inline GameInstance* GetGameInstance()
		{
			return mGameInstance;
		}

		inline Ogre::SceneManager* GetSceneManager()
		{
			return mSceneManager;
		}
	};
}

#endif
