#ifndef HIKARI_TICKMANAGER_H
#define HIKARI_TICKMANAGER_H

#include "Core/Engine/tickable.h"
#include <unordered_map>
#include <vector>

namespace Hikari
{

	class TickManager
	{
	private:
		std::unordered_map<TickGroup, std::vector<Tickable*>> mTickables;
		const TickGroup TickGroupOrder[2] = { TickGroup::Actors, TickGroup::Components };

	public:
		TickManager();

		void RegisterTickable(Tickable* arg_actor, TickGroup arg_tickgroup);
		void Tick(float arg_deltatime);
	};
}

#endif
