#ifndef HIKARI_TIMEMANAGER_H
#define HIKARI_TIMEMANAGER_H

#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"
#include "Core/Common/singleton.h"

namespace Hikari
{
	class TimeManager
	{
		__DeclareSingleton(TimeManager)
	private:
		sf::Clock mClock;
	public:
		TimeManager();

		float GetTimeSeconds();
		int GetTimeMilliseconds();
	};
}

#endif
