#include "Core/Debug/debug.h"
#include "OGRE/Ogre.h"

#include "Core/Engine/game_engine.h"

int main(int args, char** argv)
{
	LOG_INFO() << "starting client";

	Hikari::GameEngine* gameEngine = new Hikari::GameEngine();
	Hikari::GameInstance* gameInstance = gameEngine->CreateGameInstance();

	//Ogre::Root* root = new Ogre::Root("plugins_d.cfg");

	//if (!root->showConfigDialog())
	{
		//return -1;
	}

	//Ogre::RenderWindow* window = root->initialise(true, "Ogre3D test");
	//window->setFullscreen(false, 600, 400);

	//Ogre::SceneManager* sceneManager = root->createSceneManager(Ogre::ST_GENERIC);

	while (1)
	{

	}

	return 0;
}