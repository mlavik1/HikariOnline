#ifndef HIKARI_GAMEINSTANCE_H
#define HIKARI_GAMEINSTANCE_H

namespace Hikari
{
	class GameEngine;
	class World;
	class InputManager;
	class TickManager;

	class GameInstance
	{
	public:
		GameInstance(GameEngine* arg_engine);

		inline World* GetWorld()
		{
			return mWorld;
		}

		void Tick();

	private:
		GameEngine* mGameEngine;
		World* mWorld;
		TickManager* mTickManager;
		InputManager* mInputManager;
	};
}

#endif
