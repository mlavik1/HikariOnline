#ifndef HIKARI_GAMEINSTANCE_H
#define HIKARI_GAMEINSTANCE_H

namespace Hikari
{
	class GameEngine;
	class World;
	class InputManager;
	class TickManager;
	class GameWindow;

	class GameInstance
	{
	public:
		GameInstance(GameEngine* arg_engine);
		~GameInstance();

		inline World* GetWorld()
		{
			return mWorld;
		}

		inline GameWindow* GetGameWindow()
		{
			return mGameWindow;
		}

		void Tick();

		inline TickManager* GetTickManager()
		{
			return mTickManager;
		}

		inline InputManager* GetInputManager()
		{
			return mInputManager;
		}

	private:
		GameEngine* mGameEngine;
		GameWindow* mGameWindow;
		World* mWorld;
		TickManager* mTickManager;
		InputManager* mInputManager;
		float mLastTime = 0.0f;
	};
}

#endif
