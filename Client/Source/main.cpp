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
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Hikari::PlayerCharacter* actor = new Hikari::PlayerCharacter(gameInstance->GetWorld());
	actor->Initialise();
	actor->SetScale(Ogre::Vector3(10, 10, 10));

	Hikari::MeshComponent* meshComp = actor->AddComponent<Hikari::MeshComponent>();
	meshComp->Initialise();

	Hikari::LightComponent* lightComp = actor->AddComponent<Hikari::LightComponent>();
	lightComp->Initialise();

	Hikari::Actor* cameraActor = new Hikari::Actor(gameInstance->GetWorld());
	cameraActor->SetPosition(Ogre::Vector3(0.0f, 10.0f, -50.0f));
	cameraActor->Rotate(Ogre::Vector3::UNIT_X, 20.0f);
	Hikari::CameraComponent* camComp = cameraActor->AddComponent<Hikari::CameraComponent>();
	camComp->Initialise();

	// TODO: initialise components and actors from game engine!

	while (1)
	{
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
			actor->Rotate(Ogre::Vector3::UNIT_Y, 0.8f);
		}
		if (gameInstance->GetInputManager()->GetKey("a"))
		{
			actor->Rotate(Ogre::Vector3::UNIT_Y, -0.8f);
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