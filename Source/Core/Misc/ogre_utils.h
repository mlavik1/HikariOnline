#ifndef HIKARI_OGREUTILS_H
#define HIKARI_OGREUTILS_H

#include <vector>
#include "OGRE/Ogre.h"
#include "Core/Actor/actor.h"

namespace Hikari
{
	class OgreUtils
	{
	public:
		/**
		* Gets information about the mesh: vertices & indices.
		* The absolute transform of the actor will be applied to the coordinates.
		*/
		static void GetMeshInfo(Hikari::Actor* arg_actor, std::vector<Ogre::Vector3>& out_vertices, std::vector<unsigned>& out_indices);

		/**
		*
		* Modified version of: http://www.ogre3d.org/tikiwiki/RetrieveVertexData
		*/
		static void GetMeshInfo(Ogre::Mesh* mesh, std::vector<Ogre::Vector3> &vertices, std::vector<unsigned> &indices,
			const Ogre::Vector3 &position = Ogre::Vector3::ZERO,
			const Ogre::Quaternion &orient = Ogre::Quaternion::IDENTITY, const Ogre::Vector3 &scale = Ogre::Vector3::UNIT_SCALE);
	};
}

#endif
