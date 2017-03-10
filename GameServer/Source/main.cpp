#include "Core/Debug/debug.h"
#include "game_server.h"

#undef main

int main(int args, char* argv)
{
	LOG_INFO() << "Starting Game Server";

	SDL_Init(SDL_INIT_EVERYTHING);

	Hikari::GameServer* gameServer = new Hikari::GameServer();

	gameServer->Initialise();

	while (true)
	{
		gameServer->Update();
	}

	return 0;
}
