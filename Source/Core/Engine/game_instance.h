#ifndef HIKARI_GAMEINSTANCE_H
#define HIKARI_GAMEINSTANCE_H

namespace Hikari
{
	class GameEngine;
	class World;
	class InputManager;
	class TickManager;
	class WindowManager;
	class NetworkManager;
	class GameWindow;
	class Client;
#ifdef HIKARI_WORLDSERVER
	class WorldServer;
#endif
#ifdef HIKARI_GAMESERVER
	class GameServer;
#endif

	class GameInstance
	{
	private:
		GameEngine* mGameEngine;
		GameWindow* mGameWindow;
		World* mWorld;
		TickManager* mTickManager;
		InputManager* mInputManager;
		WindowManager* mWindowManager;
		NetworkManager* mNetworkManager;
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

	public:
		GameInstance(GameEngine* arg_engine);
		~GameInstance();

		void Tick();

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
}

#endif // #ifndef HIKARI_GAMEINSTANCE_H
