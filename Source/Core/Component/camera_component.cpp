#include "camera_component.h"

#include "Core/Actor/actor.h"
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
		Hikari::Component::Initialise();

		mCamera = mWorld->GetSceneManager()->createCamera(mObjectName);
		mCamera->setNearClipDistance(5); // todo: make function
		
		// TEMP -todo
		Ogre::Viewport* viewport = mWorld->GetGameInstance()->GetGameWindow()->GetRenderWindow()->addViewport(mCamera);
		viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 1.0f));
	}

	void CameraComponent::Tick(float arg_deltatime)
	{
		const Ogre::Vector3& parentPos = mParent->GetPositionAbsolute();
		mCamera->setPosition(parentPos);
		mCamera->lookAt(parentPos + mParent->GetForwardVectorAbsolute() * 10.0f);
	}
}
