#include "Core/Debug/debug.h"
#include "OGRE/Ogre.h"

#include "Core/Engine/game_engine.h"
#include "Core/Engine/game_instance.h"
#include "Core/Actor/actor.h"
#include "Core/World/world.h"
#include "Core/Component/mesh_component.h"
#include "Core/Component/camera_component.h"
#include "Core/Component/light_component.h"
#include "Core/Window/game_window.h"
#include "Core/Managers/input_manager.h"
#include "Core/Actor/player_character.h"
#include "Core/Component/movement_component.h"
#include "Core/Component/terrain_component.h"
#include "Core/Debug/debug_graphics.h"
#include "Core/Engine/client.h"
#include "Core/Controller/ingame_controller.h"
#include "Core/Object/function.h"
#include "MyGUI/MyGUI.h"
#include "MyGUI/MyGUI_OgrePlatform.h"
#include "GUI/game_hud.h"
#include "Core/Managers/window_manager.h"
#include "Core/World/world_factory.h"

#undef main

int main(int args, char** argv)
{
	LOG_INFO() << "starting client";

	SDL_Init(SDL_INIT_EVERYTHING);

	Hikari::GameEngine* gameEngine = Hikari::GameEngine::Create();
	gameEngine->Initialise();

	// TEMP - todo :  NOTE: must come before MyGUI::OGrePlatform is initialised...
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/OgreExport.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/TerrainTest.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/MyGUIMedia.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/Skybox2.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Data/Terrain1.zip", "Zip");
	//Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Layouts.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Resources/GUI/Layouts", "FileSystem", "GUILayouts");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Hikari::GameInstance* gameInstance = gameEngine->CreateGameInstance();

	gameInstance->GetGameWindow()->SetTitle("Hikari Client");

	
	Hikari::PlayerCharacter* actor = new Hikari::PlayerCharacter(gameInstance->GetWorld());
	actor->Initialise();
	actor->SetScale(Ogre::Vector3(1, 1, 1));
	actor->SetPosition(Ogre::Vector3(130.0f, 2.0f, 130.0f));

	Hikari::MeshComponent* meshComp = actor->AddComponent<Hikari::MeshComponent>();
	meshComp->SetMesh("GMObject0.mesh");
	meshComp->Initialise();

	Hikari::WorldFactory::SetupGameWorld(gameInstance->GetWorld());
	// TODO: initialise components and actors from game engine!

	gameInstance->GetClient()->GetInGameController()->SetControlledCharacter(actor);

	Hikari::GameHUD* gameHUD = (Hikari::GameHUD*)gameInstance->GetWindowManager()->ShowWindow(Hikari::GameHUD::GetStaticClass());

	gameInstance->GetClient()->ConnectToGameServer("127.0.0.1");

	while (1)
	{

		gameEngine->TickGameInstance(gameInstance);
	}

	return 0;
}