#include "Core/Debug/debug.h"
#include "Core/Engine/world_server.h"
#include "Core/Engine/game_engine.h"
#include "Core/Engine/game_instance.h"
#include "Core/World/world_factory.h"

#undef main

int main(int args, char* argv)
{
	using namespace Hikari;
	LOG_INFO() << "Starting World Server";
	GameEngine* mGameEngine;
	GameInstance* mGameInstance;

	mGameEngine = GameEngine::Create();
	mGameEngine->Initialise();
	mGameInstance = mGameEngine->CreateGameInstance();

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/TerrainTest.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/Terrain1.zip", "Zip");

	WorldFactory::SetupGameWorld(mGameInstance->GetWorld());

	WorldServer* worldServer = mGameInstance->GetWorldServer();

	//SDL_Init(SDL_INIT_EVERYTHING);
	worldServer->Initialise();

	while (!worldServer->ConnectToGameServer())
	{
		LOG_ERROR() << "Connection to GameServer failed! Trying again...";
		_sleep(3000);
	}

	while (true)
	{
		mGameEngine->TickGameInstance(mGameInstance);
	}

	return 0;
}
