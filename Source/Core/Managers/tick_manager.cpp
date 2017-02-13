#include "tick_manager.h"

namespace Hikari
{
	TickManager::TickManager()
	{
		for (TickGroup tickGroup : TickGroupOrder)
		{
			mTickables.emplace(tickGroup, std::vector<Tickable*>());
		}
	}

	void TickManager::RegisterTickable(Tickable* arg_actor, TickGroup arg_tickgroup)
	{
		mTickables[arg_tickgroup].push_back(arg_actor);
	}

	void TickManager::Tick(float arg_deltatime) // TODO: respect tickintervals
	{
		for (TickGroup tickGroup : TickGroupOrder)
		{
			const std::vector<Tickable*>& tickGroupElements = mTickables[tickGroup];
			for (Tickable* tickable : tickGroupElements)
			{
				tickable->Tick(arg_deltatime); // TODO: get delta time for tickable
			}
		}
	}
}
