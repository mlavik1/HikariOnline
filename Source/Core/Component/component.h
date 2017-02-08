#ifndef HIKARI_COMPONENT_H
#define HIKARI_COMPONENT_H

#include "Core/Object/game_object.h"

namespace Hikari
{
	class Actor;
	class World;

	class Component : public Hikari::GameObject
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

	protected:
		Actor* mParent;
	};
}

#endif
