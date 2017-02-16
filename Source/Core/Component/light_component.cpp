#include "light_component.h"

#include "Core/World/world.h"

IMPLEMENT_CLASS(Hikari::LightComponent)

namespace Hikari
{
	void LightComponent::InitialiseObject(ObjectInitialiserParams arg_params)
	{
		Hikari::Component::InitialiseObject(arg_params);
	}

	void LightComponent::Initialise()
	{
		mLight = mWorld->GetSceneManager()->createLight(mObjectName);
		mLight->setType(Ogre::Light::LT_DIRECTIONAL); // todo: make function
		mLight->setDirection(Ogre::Vector3(0.1, -1, 0.1)); // todo: use SceneNode's forward vector

		mWorld->GetSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);  // TEMP
	}
}
