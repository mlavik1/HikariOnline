#include "mesh_component.h"

#include "Core/World/world.h"
#include "Core/Actor/actor.h"
#include "OGRE/Ogre.h"

IMPLEMENT_CLASS(Hikari::MeshComponent)

namespace Hikari
{
	void MeshComponent::InitialiseObject(ObjectInitialiserParams arg_params)
	{
		Hikari::Component::InitialiseObject(arg_params);
	}

	void MeshComponent::Initialise()
	{
		// THIS IS TEMP

		Ogre::Entity* ent = mWorld->GetSceneManager()->createEntity("GMObject0.mesh");
		mParent->GetSceneNode()->attachObject(ent);
	}
	
}
