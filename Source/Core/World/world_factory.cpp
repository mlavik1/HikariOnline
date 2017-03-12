#include "world_factory.h"

#include "Core/Actor/actor.h"
#include "Core/Component/mesh_component.h"
#include "Core/Component/terrain_component.h"
#include "Core/Component/light_component.h"

namespace Hikari
{
	void WorldFactory::SetupGameWorld(World* arg_world)
	{
#ifdef HIKARI_CLIENT
		Hikari::Actor* lightActor = new Hikari::Actor(arg_world);
		Hikari::LightComponent* lightComp = lightActor->AddComponent<Hikari::LightComponent>();
		lightComp->Initialise();

		// TODO: load scene from file
		arg_world->GetSceneManager()->setSkyBox(true, "Skybox2", 15000.0f);

		// TODO: make scene settings
		arg_world->GetSceneManager()->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));
#endif

		// TODO: load scene from file
		Hikari::Actor* landscapeTest = new Hikari::Actor(arg_world);
		landscapeTest->SetScale(Ogre::Vector3(100, 100, 100));
		landscapeTest->Rotate(Ogre::Vector3(1.0f, 0.0f, 0.0f), 270.0f);
		landscapeTest->SetPosition(Ogre::Vector3(130.0f, 0.0f, 130.0f));
		landscapeTest->Initialise();
		Hikari::MeshComponent* landscapeComp = landscapeTest->AddComponent<Hikari::MeshComponent>();
		landscapeComp->SetMesh("Plane.mesh");
		landscapeComp->Initialise();
		Hikari::TerrainComponent* terrainComp = landscapeTest->AddComponent<Hikari::TerrainComponent>();
		terrainComp->Initialise();

		arg_world->LoadTerrain();
	}
}
