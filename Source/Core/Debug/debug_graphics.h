#ifndef HIKARI_DEBUGGRAPHICS_H
#define HIKARI_DEBUGGRAPHICS_H

#include "OGRE/Ogre.h"
#include "Core/World/world.h"
#include <vector>

namespace Hikari
{
	class DebugGraphics
	{
	public:
		static void DrawDebugLine(World* arg_world, Ogre::Vector3 arg_start, Ogre::Vector3 arg_end, Ogre::ColourValue arg_colour, float arg_lifetime);
		static void DrawDebugPoints(World* arg_world, std::vector<Ogre::Vector3> arg_points, Ogre::Real arg_pointsize, Ogre::ColourValue arg_colour, float arg_lifetime);
	};
}

#endif
