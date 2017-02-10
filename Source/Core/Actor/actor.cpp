#include "actor.h"

#include "Core/World/world.h"
#include "Core/Component/component.h"
#include "Core/Managers/tick_manager.h"
#include "Core/Engine/game_instance.h"

IMPLEMENT_CLASS(Hikari::Actor)

namespace Hikari
{
	Actor::Actor(Hikari::World* arg_world)
	{
		__Assert(arg_world != nullptr);
		mWorld = arg_world;
		mSceneNode = mWorld->GetSceneManager()->getRootSceneNode()->createChildSceneNode(mObjectName);
	}

	const Ogre::Vector3& Actor::GetPosition() const
	{
		return mSceneNode->getPosition();
	}

	const Ogre::Vector3& Actor::GetScale() const
	{
		return mSceneNode->getScale();
	}

	void Actor::SetPosition(const Ogre::Vector3& arg_position)
	{
		mSceneNode->setPosition(arg_position);
	}

	void Actor::SetScale(const Ogre::Vector3& arg_scale)
	{
		mSceneNode->setScale(arg_scale);
	}


	void Actor::Initialise()
	{

	}

	void Actor::OnStart()
	{

	}

	void Actor::OnStop()
	{
		
	}


	void Actor::Tick(float arg_deltatime)
	{

	}

	void Actor::ActivateTicable(bool arg_activate)
	{
		if (arg_activate)
		{
			GetTickManager()->RegisterTickable(this, TickGroup::Actors);
		}
		else
		{
			// TODO
		}	
	}

	
}