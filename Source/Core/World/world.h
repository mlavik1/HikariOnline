#ifndef HIKARI_WORLD_H
#define HIKARI_WORLD_H

#include "OGRE/Ogre.h"
#include "terrain.h"
#include "Core/Actor/actor.h"
#include <vector>

namespace Hikari
{
	class GameInstance;

	class World
	{
	private:
		Ogre::SceneManager* mSceneManager;
		GameInstance* mGameInstance;
		std::vector<Actor*> mActors;
		Terrain* mTerrain;
		int mWorldSizeX = 1000;
		int mWorldSizeZ = 1000;
		float mGridUnitSize = 1.0f;

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

		void AddActor(Actor* arg_actor);

		float GetTerrainHeight(float arg_x, float arg_z);

		void LoadTerrain();
	};
}

#endif
