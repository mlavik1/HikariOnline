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

	protected:
		Ogre::Camera* mCamera;
	};
}

#endif
