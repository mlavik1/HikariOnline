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

	Hikari::LightComponent* lightComp = actor->AddComponent<Hikari::LightComponent>();
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

	while (1)
	{
		float terrainHeight = gameInstance->GetWorld()->GetTerrainHeight(actor->GetPositionAbsolute().x, actor->GetPositionAbsolute().z);
		//std::cout << terrainHeight << std::endl;
		actor->SetPosition(Ogre::Vector3(actor->GetPosition().x, terrainHeight, actor->GetPosition().z));
		if(gameInstance->GetInputManager()->GetKeyDown("1"))
		{
			meshComp->SetActiveAnimation("idle");
		}
		else if (gameInstance->GetInputManager()->GetKeyDown("2"))
		{
			meshComp->SetActiveAnimation("walk");
		}


		if (gameInstance->GetInputManager()->GetKey("d"))
		{
			actor->Rotate(Ogre::Vector3::UNIT_Y, 1.8f);
		}
		if (gameInstance->GetInputManager()->GetKey("a"))
		{
			actor->Rotate(Ogre::Vector3::UNIT_Y, -1.8f);
		}

		if (gameInstance->GetInputManager()->GetKey("up"))
		{
			//Ogre::Vector3 vec = actor->GetForwardVector() * 0.06f;
			//actor->SetPosition(actor->GetPosition() + vec);
			actor->GetMovementComponent()->AddInput(actor->GetForwardVector());
		}
		else if (gameInstance->GetInputManager()->GetKey("down"))
		{
			//Ogre::Vector3 vec = actor->GetUpVector() * 0.06f;
			//actor->SetPosition(actor->GetPosition() + vec);
			actor->GetMovementComponent()->AddInput(actor->GetUpVector());
		}
		else
		{
			actor->GetMovementComponent()->SetVelocity(Ogre::Vector3::ZERO);
		}

		gameEngine->TickGameInstance(gameInstance);
	}

	return 0;
}