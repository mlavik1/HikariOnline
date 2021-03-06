#ifndef HIKARI_CAMERACOMPONENT_H
#define HIKARI_CAMERACOMPONENT_H

#include "component.h"
#include "OGRE/Ogre.h"

namespace Hikari
{
	class CameraComponent : public Hikari::Component
	{
		DEFINE_CLASS(Hikari::CameraComponent, Hikari::Component)
	public:
		virtual void InitialiseObject(ObjectInitialiserParams arg_params) override;

		virtual void Initialise() override;
		virtual void Tick(float arg_deltatime) override;

		Ogre::Vector2 AbsToRelScreenPos(Ogre::Vector2 arg_absolutePosition);
		Ogre::Ray ScreenPosToWorldRay(Ogre::Vector2 arg_screenpos);

	protected:
		Ogre::Camera* mCamera;
	};
}

#endif
