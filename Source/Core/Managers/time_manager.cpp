#include "time_manager.h"

namespace Hikari
{
	__ImplementSingleton(TimeManager)

	TimeManager::TimeManager()
	{
		__ConstructSingleton(TimeManager)
		mClock.restart();
	}

	float TimeManager::GetTimeSeconds()
	{
		return mClock.getElapsedTime().asSeconds();
	}

	int TimeManager::GetTimeMilliseconds()
	{
		return (int)mClock.getElapsedTime().asMilliseconds();
	}
}
