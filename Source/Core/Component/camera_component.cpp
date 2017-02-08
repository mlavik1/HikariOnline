#include "camera_component.h"

#include "Core/World/world.h"

IMPLEMENT_CLASS(Hikari::CameraComponent)

namespace Hikari
{
	void CameraComponent::InitialiseObject(ObjectInitialiserParams arg_params)
	{
		Hikari::Component::InitialiseObject(arg_params);
	}

	void CameraComponent::Initialise()
	{
		mCamera = mWorld->GetSceneManager()->createCamera(mObjectName);
		mCamera->setPosition(Ogre::Vector3(0, 0, 50));  // todo: make function
		mCamera->lookAt(Ogre::Vector3(0, 0, 0)); // todo: use SceneNOde's orientation
		mCamera->setNearClipDistance(5); // todo: make function
	}
}
