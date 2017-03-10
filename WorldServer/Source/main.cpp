#include "Core/Debug/debug.h"
#include "world_server.h"

#undef main

int main(int args, char* argv)
{
	LOG_INFO() << "Starting World Server";


	SDL_Init(SDL_INIT_EVERYTHING);

	Hikari::WorldServer* worldServer = new Hikari::WorldServer();

	worldServer->Initialise();

	while (!worldServer->ConnectToGameServer())
	{
		LOG_ERROR() << "Connection to GameServer failed! Trying again...";
		_sleep(3000);
	}

	worldServer->SetReady();

	while (true)
	{
		worldServer->Update();
	}

	return 0;
}
