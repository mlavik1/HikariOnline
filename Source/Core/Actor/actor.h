#ifndef HIKARI_ACTOR_H
#define HIKARI_ACTOR_H

#include "Core/Object/object.h"
#include "OGRE/Ogre.h"

namespace Hikari
{
	class World;

	class Actor : public Object
	{
		DEFINE_CLASS(Hikari::Actor, Hikari::Object)

	protected:
		Ogre::SceneNode* mSceneNode;
		World* mWorld;

	public:
		Actor(Hikari::World* arg_world);

		const Ogre::Vector3& GetPosition() const;
		const Ogre::Vector3& GetScale() const;

		void SetPosition(const Ogre::Vector3& arg_position);
		void SetScale(const Ogre::Vector3& arg_scale);
	};
}
#endif
