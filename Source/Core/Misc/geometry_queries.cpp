#include "geometry_queries.h"
#include "Core/World/world.h"

namespace Hikari
{
	bool GeometryQueries::TraceTerrain(Hikari::World* arg_world, Ogre::Vector3 arg_start, Ogre::Vector3 arg_end, float arg_stepsize, float arg_accuracy, Ogre::Vector3* out_hit)
	{
		Ogre::Vector3 dir = arg_end - arg_start;
		float length = dir.length();
		int requiredSteps = length / arg_stepsize + 1;
		float tStepSize = 1.0f / (float)requiredSteps;
		float t = 0.0f + tStepSize;
		bool bWasAbove = arg_world->GetTerrainHeight(arg_start.x, arg_start.z) < arg_start.y;
		bool bContinue = true;
		while (bContinue)
		{
			Ogre::Vector3 currentPos = arg_end * t + arg_start * (1.0f - t);
			float height = arg_world->GetTerrainHeight(currentPos.x, currentPos.z);
			bool bIsAbove = height < currentPos.y;
			if (bIsAbove != bWasAbove)
			{
				float a_t = t - tStepSize;
				float b_t = t;
				float c_t = b_t;
				Ogre::Vector3 a = arg_end * a_t + arg_start * (1.0f - a_t);
				Ogre::Vector3 b = currentPos;
				Ogre::Vector3 c = currentPos;
				while (true)
				{
					float heightDiff = std::abs(height - c.y);
					if (heightDiff > arg_accuracy)
					{
						if ((c.y < height) == bIsAbove)
						{
							a_t = c_t;
							a = c;
						}
						else
						{
							b_t = c_t;
							b = c;
						}
						c_t = (a_t + b_t) / 2.0f;
						c = arg_end * c_t + arg_start * (1.0f - c_t);
						height = arg_world->GetTerrainHeight(c.x, c.z);
					}
					else
					{
						if (out_hit)
						{
							*out_hit = c;
						}
						return true;
					}
				}
			}

			if (t < 1.0f)
			{
				t = std::min(t + tStepSize, 1.0f);
			}
			else
			{
				bContinue = false;
			}
		}
		return false;
	}
}
