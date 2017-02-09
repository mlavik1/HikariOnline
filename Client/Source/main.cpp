#include "Core/Debug/debug.h"
#include "OGRE/Ogre.h"

#include "Core/Engine/game_engine.h"
#include "Core/Engine/game_instance.h"
#include "Core/Actor/actor.h"
#include "Core/Component/mesh_component.h"
#include "Core/Component/camera_component.h"
#include "Core/Component/light_component.h"
#include "Core/Window/game_window.h"

int main(int args, char** argv)
{
	LOG_INFO() << "starting client";
	

	Hikari::GameEngine* gameEngine = Hikari::GameEngine::Create();
	gameEngine->Initialise();
	Hikari::GameInstance* gameInstance = gameEngine->CreateGameInstance();

	gameEngine->GetGameWindow()->SetTitle("Hikari Client");

	// TEMP - todo
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("OgreExport.zip", "Zip");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Hikari::Actor* actor = new Hikari::Actor(gameInstance->GetWorld());
	actor->Initialise();

	Hikari::MeshComponent* meshComp = actor->AddComponent<Hikari::MeshComponent>();
	meshComp->Initialise();

	Hikari::CameraComponent* camComp = actor->AddComponent<Hikari::CameraComponent>();
	camComp->Initialise();

	Hikari::LightComponent* lightComp = actor->AddComponent<Hikari::LightComponent>();
	lightComp->Initialise();

	// TODO: initialise components and actors from game engine!

	while (1)
	{
		gameEngine->TickGameInstance(gameInstance);
	}

	return 0;
}