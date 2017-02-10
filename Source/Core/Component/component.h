#ifndef HIKARI_COMPONENT_H
#define HIKARI_COMPONENT_H

#include "Core/Object/game_object.h"
#include "Core/Engine/tickable.h"

namespace Hikari
{
	class Actor;
	class World;

	class Component : public Hikari::GameObject, public Hikari::Tickable
	{
		DEFINE_CLASS(Hikari::Component, Hikari::GameObject)

			friend class Actor;
	public:
		/**
		* Subclasses of component should override this, rather than using empty constructors.
		**/
		virtual void InitialiseObject(ObjectInitialiserParams arg_params) override;

		virtual void Initialise() override;
		virtual void OnStart() override;
		virtual void OnStop() override;

		virtual void Tick(float arg_deltatime) override;
		virtual void ActivateTicable(bool arg_activate) override;

	protected:
		Actor* mParent;
	};
}

#endif
