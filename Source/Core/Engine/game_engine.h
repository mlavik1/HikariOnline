#ifndef HIKARI_GAMEENGINE_H
#define HIKARI_GAMEENGINE_H

#include "OGRE/Ogre.h"

namespace Hikari
{
	class GameInstance;

	class GameEngine
	{
	public:
		GameEngine();

		GameInstance* CreateGameInstance();

		inline Ogre::Root* GetOgreRoot()
		{
			return mOgreRoot;
		}

	private:
		Ogre::Root* mOgreRoot;
		
	};
}

#endif
