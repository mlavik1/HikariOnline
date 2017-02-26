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

int main(int args, char** argv)
{
	LOG_INFO() << "starting client";

	Hikari::GameEngine* gameEngine = Hikari::GameEngine::Create();
	gameEngine->Initialise();
	Hikari::GameInstance* gameInstance = gameEngine->CreateGameInstance();

	gameInstance->GetGameWindow()->SetTitle("Hikari Client");

	// TODO: make scene settings
	gameInstance->GetWorld()->GetSceneManager()->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));

	// TEMP - todo
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("OgreExport.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("TerrainTest.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

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

	Hikari::Actor* cameraActor = new Hikari::Actor(gameInstance->GetWorld());
	cameraActor->SetPosition(Ogre::Vector3(130.0f, 45.0f, 80.0f));
	cameraActor->Rotate(Ogre::Vector3::UNIT_X, 40.0f);
	Hikari::CameraComponent* camComp = cameraActor->AddComponent<Hikari::CameraComponent>();
	camComp->Initialise();

	Hikari::PlayerCharacter* landscapeTest = new Hikari::PlayerCharacter(gameInstance->GetWorld());
	landscapeTest->SetScale(Ogre::Vector3(0.6f, 0.3f, 0.6f));
	landscapeTest->Rotate(Ogre::Vector3(1.0f, 0.0f, 0.0f), 90.0f);
	landscapeTest->SetPosition(Ogre::Vector3(130.0f, 0.0f, 130.0f));
	//landscapeTest->SetPosition(Ogre::Vector3(0.0f, 0.0f, 100.0f));
	landscapeTest->Initialise();
	Hikari::MeshComponent* landscapeComp = landscapeTest->AddComponent<Hikari::MeshComponent>();
	landscapeComp->SetMesh("ID3.mesh");
	landscapeComp->Initialise();
	Hikari::TerrainComponent* terrainComp = landscapeTest->AddComponent<Hikari::TerrainComponent>();
	terrainComp->Initialise();

	gameInstance->GetWorld()->LoadTerrain();
	// TODO: initialise components and actors from game engine!

	//std::vector<Ogre::Vector3> points;
	//points.push_back(actor->GetPositionAbsolute());
	//points.push_back(actor->GetPositionAbsolute() + Ogre::Vector3::UNIT_Y * 2.0f);
	//Hikari::DebugGraphics::DrawDebugPoints(gameInstance->GetWorld(), points, 20.0f, Ogre::ColourValue::Red, 10.0f);

	gameInstance->GetClient()->GetInGameController()->SetControlledCharacter(actor);

	while (1)
	{
		

		gameEngine->TickGameInstance(gameInstance);
	}

	return 0;
}