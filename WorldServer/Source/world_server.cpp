#include "world_server.h"
#include "Core/Debug/debug.h"
#include "Core/World/world_factory.h"
#include "Core/Engine/game_instance.h"
#include "Core/World/world.h"

namespace Hikari
{
	WorldServer::WorldServer()
	{
		SDLNet_Init();

		mGameServerConnection = new Hikari::ServerConnection();
		mClientConnection = new Hikari::ClientConnection(1000);
	}

	WorldServer::~WorldServer()
	{
		mGameServerConnection->Close();
		mClientConnection->Close();
		delete(mGameServerConnection);
		delete(mClientConnection);

		SDLNet_Quit();
	}

	void WorldServer::Initialise()
	{
		std::string myIP = GetLocalhostIP();
		LOG_INFO() << "My IP: " << myIP;

		mClientConnection->Connect(PORT_WORLDSERVER_CLIENT);

		mGameEngine = GameEngine::Create();
		mGameEngine->Initialise();
		mGameInstance = mGameEngine->CreateGameInstance();

		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/TerrainTest.zip", "Zip");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/Terrain1.zip", "Zip");

		WorldFactory::SetupGameWorld(mGameInstance->GetWorld());
	}

	bool WorldServer::ConnectToGameServer()
	{
		bool bConnected = mGameServerConnection->Connect("127.0.0.1", PORT_GAMESERVER_WORLDSERVER);

		if (bConnected)
		{
			NetMessage connMessage(NetMessageType::EstablishConnection, "");
			mOutgoingGameServerMessages.push_back(connMessage);
		}
		return bConnected;
	}

	void WorldServer::SetReady()
	{
		// TODO: tell GameServer that we are ready
	}

	void WorldServer::Update()
	{
		for (NetMessage& outMessage : mOutgoingGameServerMessages)
		{
			std::string msgStr = outMessage.GetStringRepresentation();
			mGameServerConnection->SendNetworkMessage(msgStr.c_str(), msgStr.length());
		}

		mOutgoingGameServerMessages.clear();

		// Tick game engine
		mGameEngine->TickGameInstance(mGameInstance);
	}
}
