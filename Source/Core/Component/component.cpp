#include "component.h"

#include "Core/Debug/st_assert.h"
#include "Core/World/world.h"

IMPLEMENT_CLASS(Hikari::Component)

namespace Hikari
{
	void Component::InitialiseObject(ObjectInitialiserParams arg_params)
	{
		mParent = nullptr;
	}

	void Component::Initialise()
	{

	}
	void Component::OnStart()
	{

	}
	void Component::OnStop()
	{

	}
}
