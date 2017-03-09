#ifndef GEOMATRY_QUERIES_H
#define GEOMATRY_QUERIES_H

#include "OGRE/Ogre.h"
#include <vector>

namespace Hikari
{
	class World;

	class GeometryQueries
	{
	public:
		static bool TraceTerrain(Hikari::World* arg_world, Ogre::Vector3 arg_start, Ogre::Vector3 arg_end, float arg_stepsize, float arg_accuracy, Ogre::Vector3* out_hit = nullptr);
	};
}

#endif
