#include "Core/Debug/debug.h"
#include "OGRE/Ogre.h"

#include "Core/Engine/game_engine.h"
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

using namespace Hikari;

int main(int args, char** argv)
{
	LOG_INFO() << "starting client";

	SDL_Init(SDL_INIT_EVERYTHING);

	Hikari::GameEngine* gameEngine = Hikari::GameEngine::Create();
	gameEngine->Initialise();

	GameEngine::Instance()->GetGameWindow()->SetTitle("Hikari Client");

	
	Hikari::PlayerCharacter* actor = new Hikari::PlayerCharacter(GameEngine::Instance()->GetWorld());
	actor->Initialise();
	actor->SetScale(Ogre::Vector3(1, 1, 1));
	actor->SetPosition(Ogre::Vector3(130.0f, 2.0f, 130.0f));

	Hikari::MeshComponent* meshComp = actor->AddComponent<Hikari::MeshComponent>();
	meshComp->SetMesh("GMObject0.mesh");
	meshComp->Initialise();

	Hikari::WorldFactory::SetupGameWorld(GameEngine::Instance()->GetWorld());
	// TODO: initialise components and actors from game engine!

	GameEngine::Instance()->GetClient()->GetInGameController()->SetControlledCharacter(actor);

	Hikari::GameHUD* gameHUD = (Hikari::GameHUD*)GameEngine::Instance()->GetWindowManager()->ShowWindow(Hikari::GameHUD::GetStaticClass());

	GameEngine::Instance()->GetClient()->ConnectToGameServer("127.0.0.1");

	while (1)
	{

		gameEngine->TickEngine();
	}

	return 0;
}