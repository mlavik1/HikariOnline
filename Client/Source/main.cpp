#include "Core/Debug/debug.h"
#include "OGRE/Ogre.h"

#include "Core/Engine/game_engine.h"
#include "Core/Engine/game_instance.h"
#include "Core/Actor/actor.h"
#include "Core/Component/mesh_component.h"
#include "Core/Component/camera_component.h"
#include "Core/Component/light_component.h"

int main(int args, char** argv)
{
	LOG_INFO() << "starting client";
	

	Hikari::GameEngine* gameEngine = new Hikari::GameEngine();
	Hikari::GameInstance* gameInstance = gameEngine->CreateGameInstance();

	Ogre::RenderWindow* window = gameEngine->GetOgreRoot()->initialise(true, "Ogre3D test");
	window->setFullscreen(false, 600, 400);

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

	/*
	Ogre::Root* root = new Ogre::Root("plugins_d.cfg");

	if (!root->showConfigDialog())
	{
		return -1;
	}*/

	//Ogre::RenderWindow* window = root->initialise(true, "Ogre3D test");
	//window->setFullscreen(false, 600, 400);

	//Ogre::SceneManager* sceneManager = root->createSceneManager(Ogre::ST_GENERIC);

	while (1)
	{

	}

	return 0;
}