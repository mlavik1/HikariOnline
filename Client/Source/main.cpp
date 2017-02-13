#include "Core/Debug/debug.h"
#include "OGRE/Ogre.h"

#include "Core/Engine/game_engine.h"
#include "Core/Engine/game_instance.h"
#include "Core/Actor/actor.h"
#include "Core/Component/mesh_component.h"
#include "Core/Component/camera_component.h"
#include "Core/Component/light_component.h"
#include "Core/Window/game_window.h"
#include "Core/Managers/input_manager.h"
#include "Core/Actor/player_character.h"

int main(int args, char** argv)
{
	LOG_INFO() << "starting client";


	Hikari::GameEngine* gameEngine = Hikari::GameEngine::Create();
	gameEngine->Initialise();
	Hikari::GameInstance* gameInstance = gameEngine->CreateGameInstance();

	gameInstance->GetGameWindow()->SetTitle("Hikari Client");

	// TEMP - todo
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("OgreExport.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Hikari::PlayerCharacter* actor = new Hikari::PlayerCharacter(gameInstance->GetWorld());
	actor->Initialise();
	actor->SetScale(Ogre::Vector3(10, 10, 10));

	Hikari::MeshComponent* meshComp = actor->AddComponent<Hikari::MeshComponent>();
	meshComp->Initialise();

	Hikari::CameraComponent* camComp = actor->AddComponent<Hikari::CameraComponent>();
	camComp->Initialise();

	Hikari::LightComponent* lightComp = actor->AddComponent<Hikari::LightComponent>();
	lightComp->Initialise();

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
			actor->Rotate(Ogre::Vector3::UNIT_Y, 0.5f);
		}
		if (gameInstance->GetInputManager()->GetKey("a"))
		{
			actor->Rotate(Ogre::Vector3::UNIT_Y, -0.5f);
		}

		if (gameInstance->GetInputManager()->GetKey("up"))
		{
			Ogre::Vector3 vec = actor->GetForwardVector() * 0.06f;
			actor->SetPosition(actor->GetPosition() + vec);
		}
		if (gameInstance->GetInputManager()->GetKey("down"))
		{
			Ogre::Vector3 vec = actor->GetUpVector() * 0.06f;
			actor->SetPosition(actor->GetPosition() + vec);
		}

		gameEngine->TickGameInstance(gameInstance);
	}

	return 0;
}