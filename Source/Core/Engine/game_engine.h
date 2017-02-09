#ifndef HIKARI_GAMEENGINE_H
#define HIKARI_GAMEENGINE_H

#include "OGRE/Ogre.h"
#include "Core/Common/singleton.h"

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
		void Initialise();

		void TickGameInstance(GameInstance* arg_instance);

		GameInstance* CreateGameInstance();

		inline Ogre::Root* GetOgreRoot()
		{
			return mOgreRoot;
		}

		// TODO: move to GameInstance
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
