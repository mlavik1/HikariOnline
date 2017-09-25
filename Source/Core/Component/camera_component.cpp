#include "camera_component.h"

#include "Core/Actor/actor.h"
#include "Core/World/world.h"
#include "Core/Engine/game_engine.h"
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

		mCamera = GameEngine::Instance()->GetGameWindow()->GetMainCamera();
	}

	void CameraComponent::Tick(float arg_deltatime)
	{
		const Ogre::Vector3& parentPos = mParent->GetPositionAbsolute();
		mCamera->setPosition(parentPos);
		mCamera->lookAt(parentPos + mParent->GetForwardVectorAbsolute() * 10.0f);
	}

	Ogre::Vector2 CameraComponent::AbsToRelScreenPos(Ogre::Vector2 arg_absolutePosition)
	{
		const GameWindow* gameWindow = GameEngine::Instance()->GetGameWindow();
		return arg_absolutePosition / Ogre::Vector2(gameWindow->GetWidth(), gameWindow->GetHeight());
	}

	Ogre::Ray CameraComponent::ScreenPosToWorldRay(Ogre::Vector2 arg_screenpos)
	{
		return mCamera->getCameraToViewportRay(arg_screenpos.x, arg_screenpos.y);
	}
}
