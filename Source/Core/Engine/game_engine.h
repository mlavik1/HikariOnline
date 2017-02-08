#ifndef HIKARI_GAMEENGINE_H
#define HIKARI_GAMEENGINE_H

#include "OGRE/Ogre.h"

namespace Hikari
{
	class GameInstance;
	class GameWindow;

	class GameEngine
	{
	public:
		GameEngine();

		void Initialise();
		GameInstance* CreateGameInstance();

		inline Ogre::Root* GetOgreRoot()
		{
			return mOgreRoot;
		}

		inline GameWindow* GetGameWindow()
		{
			return mGameWindow;
		}

	private:
		Ogre::Root* mOgreRoot;
		GameWindow* mGameWindow;
		
	};
}

#endif
