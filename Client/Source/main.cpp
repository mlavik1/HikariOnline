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

int main(int args, char** argv)
{
	LOG_INFO() << "starting client";

	Hikari::GameEngine* gameEngine = Hikari::GameEngine::Create();
	gameEngine->Initialise();

	// TEMP - todo :  NOTE: must come before MyGUI::OGrePlatform is initialised...
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("OgreExport.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("TerrainTest.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("MyGUIMedia.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Skybox2.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Layouts.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Hikari::GameInstance* gameInstance = gameEngine->CreateGameInstance();

	gameInstance->GetGameWindow()->SetTitle("Hikari Client");

	// TODO: make scene settings
	gameInstance->GetWorld()->GetSceneManager()->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));

	
	Hikari::PlayerCharacter* actor = new Hikari::PlayerCharacter(gameInstance->GetWorld());
	actor->Initialise();
	actor->SetScale(Ogre::Vector3(10, 10, 10));
	actor->SetPosition(Ogre::Vector3(130.0f, 2.0f, 130.0f));

	Hikari::MeshComponent* meshComp = actor->AddComponent<Hikari::MeshComponent>();
	meshComp->SetMesh("GMObject0.mesh");
	meshComp->Initialise();

	Hikari::Actor* lightActor = new Hikari::Actor(gameInstance->GetWorld());
	Hikari::LightComponent* lightComp = lightActor->AddComponent<Hikari::LightComponent>();
	lightComp->Initialise();

	Hikari::PlayerCharacter* landscapeTest = new Hikari::PlayerCharacter(gameInstance->GetWorld());
	landscapeTest->SetScale(Ogre::Vector3(0.6f, 0.3f, 0.6f));
	landscapeTest->Rotate(Ogre::Vector3(1.0f, 0.0f, 0.0f), 270.0f);
	landscapeTest->SetPosition(Ogre::Vector3(130.0f, 0.0f, 130.0f));
	landscapeTest->Initialise();
	Hikari::MeshComponent* landscapeComp = landscapeTest->AddComponent<Hikari::MeshComponent>();
	landscapeComp->SetMesh("ID3.mesh");
	landscapeComp->Initialise();
	Hikari::TerrainComponent* terrainComp = landscapeTest->AddComponent<Hikari::TerrainComponent>();
	terrainComp->Initialise();

	gameInstance->GetWorld()->GetSceneManager()->setSkyBox(true, "Skybox2", 15000.0f);

	gameInstance->GetWorld()->LoadTerrain();
	// TODO: initialise components and actors from game engine!


	gameInstance->GetClient()->GetInGameController()->SetControlledCharacter(actor);

	Hikari::GameHUD* gameHUD = (Hikari::GameHUD*)gameInstance->GetWindowManager()->ShowWindow(Hikari::GameHUD::GetStaticClass());
	//gameHUD->ShowWindow();
	/*
	MyGUI::Gui* mGUI = gameInstance->GetGameWindow()->GetMyGUI();
	
	MyGUI::ButtonPtr button = mGUI->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
	button->setCaption("exit");

	MyGUI::WindowPtr guiWIndow = mGUI->createWidget<MyGUI::Window>("Button", 100, 100, 300, 300, MyGUI::Align::Default, "Main");
	guiWIndow->setAlign(MyGUI::Align::Bottom);
	guiWIndow->setProperty("Movable", "true");
	*/
	

	while (1)
	{

		gameEngine->TickGameInstance(gameInstance);
	}

	return 0;
}