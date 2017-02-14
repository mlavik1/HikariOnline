#include "component.h"

#include "Core/Debug/st_assert.h"
#include "Core/World/world.h"
#include "Core/Managers/tick_manager.h"

IMPLEMENT_CLASS(Hikari::Component)

namespace Hikari
{
	void Component::InitialiseObject(ObjectInitialiserParams arg_params)
	{
		mParent = nullptr;
	}

	void Component::Initialise()
	{
		ActivateTicable(true);
	}

	void Component::OnStart()
	{

	}

	void Component::OnStop()
	{

	}


	void Component::Tick(float arg_deltatime)
	{

	}

	void Component::ActivateTicable(bool arg_activate)
	{
		if (arg_activate)
		{
			GetTickManager()->RegisterTickable(this, TickGroup::Components);
		}
		else
		{
			// TODO
		}
	}
}
