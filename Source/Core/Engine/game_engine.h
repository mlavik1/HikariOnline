#ifndef HIKARI_GAMEENGINE_H
#define HIKARI_GAMEENGINE_H

#include "OGRE/Ogre.h"
#include "Core/Common/singleton.h"
#include <vector>

namespace Hikari
{
	class GameEngine;
	class World;
	class TaskManager;
	class InputManager;
	class TickManager;
	class WindowManager;
	class NetworkManager;
	class PlayerManager;
	class GameWindow;
	class Client;
#ifdef HIKARI_WORLDSERVER
	class WorldServer;
#endif
#ifdef HIKARI_GAMESERVER
	class GameServer;
#endif


	class GameEngine
	{
		__DeclareSingleton(Hikari::GameEngine);


	private:
		Ogre::Root* mOgreRoot;

		GameWindow* mGameWindow;
		World* mWorld;
		TickManager* mTickManager;
		InputManager* mInputManager;
		WindowManager* mWindowManager;
		NetworkManager* mNetworkManager;
		PlayerManager* mPlayerManager;
		TaskManager* mTaskManager;
		float mLastTime = 0.0f;
#ifdef HIKARI_CLIENT
		Client* mClient;
#endif
#ifdef HIKARI_WORLDSERVER
		WorldServer* mWorldServer;
#endif
#ifdef HIKARI_GAMESERVER
		GameServer* mGameServer;
#endif

	protected:
		GameEngine();

	public:
		~GameEngine();

	public:
		void Initialise();

		void TickEngine();

		inline Ogre::Root* GetOgreRoot()
		{
			return mOgreRoot;
		}

		inline World* GetWorld()
		{
			return mWorld;
		}

		inline GameWindow* GetGameWindow()
		{
			return mGameWindow;
		}

		inline TickManager* GetTickManager()
		{
			return mTickManager;
		}

		inline InputManager* GetInputManager()
		{
			return mInputManager;
		}

		inline WindowManager* GetWindowManager()
		{
			return mWindowManager;
		}

		inline NetworkManager* GetNetworkManager()
		{
			return mNetworkManager;
		}

		inline PlayerManager* GetPlayerManager()
		{
			return mPlayerManager;
		}

		inline TaskManager* GetTaskManager()
		{
			return mTaskManager;
		}

#ifdef HIKARI_CLIENT
		inline Client* GetClient()
		{
			return mClient;
		}
#endif
#ifdef HIKARI_WORLDSERVER
		inline WorldServer* GetWorldServer()
		{
			return mWorldServer;
		}
#endif
#ifdef HIKARI_GAMESERVER
		inline GameServer* GetGameServer()
		{
			return mGameServer;
		}
#endif
		
	};

	extern GameEngine* GGameEngine;

}

#endif
