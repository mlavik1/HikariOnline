#include "camera_component.h"

#include "Core/World/world.h"
#include "Core/Engine/game_engine.h"
#include "Core/Engine/game_instance.h"
#include "Core/Window/game_window.h"

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
		mCamera->setPosition(Ogre::Vector3(-20, 20, 0));  // todo: make function
		mCamera->lookAt(Ogre::Vector3(0, 0, 0)); // todo: use SceneNOde's orientation
		mCamera->setNearClipDistance(5); // todo: make function

		// TEMP -todo
		Ogre::Viewport* viewport = mWorld->GetGameInstance()->GetGameWindow()->GetRenderWindow()->addViewport(mCamera);
		viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 1.0f));
	}
}
