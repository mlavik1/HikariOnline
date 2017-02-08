#ifndef HIKARI_MESHCOMPONENT_H
#define HIKARI_MESHCOMPONENT_H

#include "component.h"

namespace Hikari
{
	class MeshComponent : public Hikari::Component
	{
		DEFINE_CLASS(Hikari::MeshComponent, Hikari::Component)
	public:
		virtual void InitialiseObject(ObjectInitialiserParams arg_params) override;

		virtual void Initialise() override;

	};
}

#endif
