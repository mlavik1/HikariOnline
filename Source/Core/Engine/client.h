#ifndef HIKARI_CLIENT_H
#define HIKARI_CLIENT_H

namespace Hikari
{
	class GameInstance;
	class ClientController;
	class InGameController;

	class Client
	{
	protected:
		GameInstance* mGameInstance;
		ClientController* mClientController;
		InGameController* mInGameController; // null, if not in-game

	public:
		Client(GameInstance* arg_gameinstance);
		void TickClient(float arg_deltatime);

		InGameController* GetInGameController();
		GameInstance* GetGameInstance();
	};
}

#endif
