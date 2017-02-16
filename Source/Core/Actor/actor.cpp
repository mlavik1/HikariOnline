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
		mParent = nullptr;
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

	const Ogre::Quaternion& Actor::GetRotation() const
	{
		return mSceneNode->getOrientation();
	}

	const Ogre::Vector3& Actor::GetForwardVector() const
	{
		return GetRotation().zAxis();
	}

	const Ogre::Vector3& Actor::GetUpVector() const
	{
		return GetRotation().yAxis();
	}

	const Ogre::Vector3& Actor::GetRightVector() const
	{
		return GetRotation().xAxis();
	}

	const Ogre::Vector3& Actor::GetPositionAbsolute() const
	{
		return mSceneNode->_getDerivedPosition();
	}

	const Ogre::Vector3& Actor::GetScaleAbsolute() const
	{
		return mSceneNode->_getDerivedScale();
	}

	const Ogre::Quaternion& Actor::GetRotationAbsolute() const
	{
		return mSceneNode->_getDerivedOrientation();
	}

	const Ogre::Vector3& Actor::GetForwardVectorAbsolute() const
	{
		return GetRotationAbsolute().zAxis();
	}

	const Ogre::Vector3& Actor::GetUpVectorAbsolute() const
	{
		return GetRotationAbsolute().yAxis();
	}

	const Ogre::Vector3& Actor::GetRightVectorAbsolute() const
	{
		return GetRotationAbsolute().xAxis();
	}


	void Actor::SetPosition(const Ogre::Vector3& arg_position)
	{
		mSceneNode->setPosition(arg_position);
	}

	void Actor::SetScale(const Ogre::Vector3& arg_scale)
	{
		mSceneNode->setScale(arg_scale);
	}

	void Actor::Rotate(const Ogre::Vector3& arg_axis, float arg_degrees)
	{
		mSceneNode->rotate(arg_axis, Ogre::Radian(Ogre::Degree(arg_degrees).valueRadians()));
	}
	

	void Actor::SetParent(Actor* arg_parent)
	{
		if (mSceneNode->getParent() != nullptr)
		{
			mSceneNode->getParent()->removeChild(mSceneNode);
		}
		
		mParent = arg_parent;
		mParent->mSceneNode->addChild(mSceneNode);
	}

	void Actor::Initialise()
	{
		ActivateTicable(true);
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