#ifndef HIKARI_GAMEENGINE_H
#define HIKARI_GAMEENGINE_H

#include "OGRE/Ogre.h"
#include "Core/Common/singleton.h"
#include <vector>

namespace Hikari
{
	class GameInstance;
	class GameWindow;

	class GameEngine
	{
		__DeclareSingleton(Hikari::GameEngine);

	protected:
		GameEngine();

	public:
		~GameEngine();

	public:
		void Initialise();

		void TickGameInstance(GameInstance* arg_instance);

		GameInstance* CreateGameInstance();

		inline Ogre::Root* GetOgreRoot()
		{
			return mOgreRoot;
		}

	private:
		Ogre::Root* mOgreRoot;
		std::vector<GameInstance*> mGameInstances;
		
	};
}

#endif
