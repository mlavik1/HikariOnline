#ifndef HIKARI_LIGHTCOMPONENT_H
#define HIKARI_LIGHTCOMPONENT_H

#include "component.h"
#include "OGRE/Ogre.h"

namespace Hikari
{
	class LightComponent : public Hikari::Component
	{
		DEFINE_CLASS(Hikari::LightComponent, Hikari::Component)
	public:
		virtual void InitialiseObject(ObjectInitialiserParams arg_params) override;

		virtual void Initialise() override;

	protected:
		Ogre::Light* mLight;
	};
}

#endif
