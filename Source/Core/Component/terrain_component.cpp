#include "terrain_component.h"

#include "Core/World/world.h"

IMPLEMENT_CLASS(Hikari::TerrainComponent)

namespace Hikari
{
	void TerrainComponent::InitialiseObject(ObjectInitialiserParams arg_params)
	{
		Hikari::Component::InitialiseObject(arg_params);
	}

	void TerrainComponent::Initialise()
	{
		Component::Initialise();


	}
}
