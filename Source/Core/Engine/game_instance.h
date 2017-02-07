#ifndef HIKARI_GAMEINSTANCE_H
#define HIKARI_GAMEINSTANCE_H

namespace Hikari
{
	class GameEngine;
	class World;

	class GameInstance
	{
	public:
		GameInstance(GameEngine* arg_engine);

	private:
		GameEngine* mGameEngine;
		World* mWorld;
	};
}

#endif
