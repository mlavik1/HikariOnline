#include "movement_component.h"
#include "Core/Debug/st_assert.h"
//#include "Core/Actor/character.h"
#include "Core/Actor/actor.h"
#include "Core/Networking/rpc.h"

IMPLEMENT_CLASS(Hikari::MovementComponent)

REGISTER_CLASSPROPERTIES(Hikari::MovementComponent)

namespace Hikari
{
	void MovementComponent::InitialiseObject(ObjectInitialiserParams arg_params)
	{
		Hikari::Component::InitialiseObject(arg_params);

		mVelocity = Ogre::Vector3::ZERO;
		mRequestedInput = Ogre::Vector3::ZERO;
		mMovementMode = MovementMode::Walking;

		MovementModeSettings defaultMovementModeSettings;
		defaultMovementModeSettings.Acceleration = 10.0f;
		defaultMovementModeSettings.MaxSpeed = 2.2f;
		SetMovementModeSettings(MovementMode::Walking, defaultMovementModeSettings);
		defaultMovementModeSettings.Acceleration = 1.2f;
		defaultMovementModeSettings.MaxSpeed = 2.5f;
		SetMovementModeSettings(MovementMode::Flying, defaultMovementModeSettings);
		SetMovementModeSettings(MovementMode::None, MovementModeSettings());
	}

	void MovementComponent::Initialise()
	{
		Component::Initialise();
		// TODO: add a RequireComponent-marco (like Unity does), and check before adding component to actor.
		//__Assert(mParent != nullptr && mParent->GetClass()->IsA(Hikari::Character::GetStaticClass()));
	}

	void MovementComponent::Tick(float arg_deltatime)
	{
		const MovementModeSettings& movementModeSettings = GetMovementModeSettings();
		mVelocity += (mRequestedInput * movementModeSettings.Acceleration * arg_deltatime);
		const float& currentSpeed = GetSpeed();
		if (currentSpeed > movementModeSettings.MaxSpeed)
		{
			mVelocity = (mVelocity / currentSpeed)* movementModeSettings.MaxSpeed;
		}

		mParent->SetPosition(mParent->GetPosition() + mVelocity * arg_deltatime);

		// Replicate movement
		if (mTimeSinceReplicationSent > 0.5f)
		{
#ifdef HIKARI_WORLDSERVER
			ReplicateMovementToClients(); // Replicate movement data to clients
#endif
#ifdef HIKARI_CLIENT
			if(mParent->IsOwningClient())
				ReplicateMovementToServer(); // Replicate movement data to server, if owning client
#endif
			mTimeSinceReplicationSent = 0.0f;
		}
		else
		{
			mTimeSinceReplicationSent += arg_deltatime;
		}

	}

	const MovementModeSettings& MovementComponent::GetMovementModeSettings()
	{
		return mMovementModeSettings[mMovementMode];
	}

	float MovementComponent::GetSpeed() const
	{
		return mVelocity.length();
	}

	void MovementComponent::SetMovementMode(MovementMode arg_mode)
	{
		mMovementMode = arg_mode;
	}

	void MovementComponent::SetMovementModeSettings(MovementMode arg_mode, MovementModeSettings arg_settings)
	{
		mMovementModeSettings[arg_mode] = arg_settings;
	}

	void MovementComponent::AddInput(Ogre::Vector3 arg_direction)
	{
		mRequestedInput = arg_direction;
		mRequestedInput.normalise();
	}

	void MovementComponent::SetVelocity(Ogre::Vector3 arg_velocity)
	{
		mRequestedInput = Ogre::Vector3::ZERO;
		mVelocity = arg_velocity;
	}

	void MovementComponent::ReplicateMovementToClients()
	{
		Ogre::Vector3 pos = mParent->GetPosition();
#ifdef HIKARI_WORLDSERVER
		ClientCall(-1, this, ClientOnReplicateMovement, pos, mVelocity);
#endif
	}

	void MovementComponent::ReplicateMovementToServer()
	{
		Ogre::Vector3 pos = mParent->GetPosition();
#ifdef HIKARI_CLIENT
		WorldServerCall(this, ServerOnReceiveClientMovement, pos, mVelocity);
#endif
	}

	void MovementComponent::ServerOnReceiveClientMovement(Ogre::Vector3 arg_position, Ogre::Vector3 arg_velocity)
	{
		// TODO
		mParent->SetPosition(arg_position);
		SetVelocity(arg_velocity);
	}

	void MovementComponent::ClientOnReplicateMovement(Ogre::Vector3 arg_position, Ogre::Vector3 arg_velocity)
	{
		if (mParent->IsOwningClient())
			return; // TODO
		// TODO
		mParent->SetPosition(arg_position);
		SetVelocity(arg_velocity);
	}

}
