#include "Core/Debug/debug.h"
#include "Core/Engine/game_engine.h"
#include "Core/Engine/game_instance.h"
#include "Core/Engine/game_server.h"
#include <sdl2/SDL.h>

#undef main

int main(int args, char* argv)
{
	using namespace Hikari;
	LOG_INFO() << "Starting Game Server";

	SDL_Init(SDL_INIT_EVERYTHING);

	GameEngine* mGameEngine;
	GameInstance* mGameInstance;

	mGameEngine = GameEngine::Create();
	mGameEngine->Initialise();
	mGameInstance = mGameEngine->CreateGameInstance();


	Hikari::GameServer* gameServer = mGameInstance->GetGameServer();

	gameServer->Initialise();

	while (true)
	{
		gameServer->Update();
	}

	return 0;
}
