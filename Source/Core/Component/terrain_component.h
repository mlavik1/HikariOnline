#ifndef HIKARI_TERRAINCOMPONENT_H
#define HIKARI_TERRAINCOMPONENT_H

#include "component.h"
#include "OGRE/Ogre.h"

namespace Hikari
{
	class TerrainComponent : public Hikari::Component
	{
		DEFINE_CLASS(Hikari::TerrainComponent, Hikari::Component)
	public:
		virtual void InitialiseObject(ObjectInitialiserParams arg_params) override;

		virtual void Initialise() override;

	};
}

#endif
