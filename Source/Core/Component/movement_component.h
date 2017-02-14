#ifndef HIKARI_MOVEMENTCOMPONENT_H
#define HIKARI_MOVEMENTCOMPONENT_H

#include "Core/Component/component.h"
#include "OGRE/Ogre.h"
#include <unordered_map>

namespace Hikari
{
	enum class MovementMode
	{
		None,
		Walking,
		Flying
	};

	struct MovementModeSettings
	{
		float MaxSpeed = 0.0f;
		float Acceleration = 0.0f;
	};

	class MovementComponent : public Hikari::Component
	{
		DEFINE_CLASS(Hikari::MovementComponent, Hikari::Component)
	public:
		virtual void InitialiseObject(ObjectInitialiserParams arg_params) override;

		virtual void Initialise() override;

		virtual void Tick(float arg_deltatime) override;

		const MovementModeSettings& GetMovementModeSettings();
		float GetSpeed() const;

		void SetMovementMode(MovementMode arg_mode);
		void SetMovementModeSettings(MovementMode arg_mode, MovementModeSettings arg_settings);

		void AddInput(Ogre::Vector3 arg_direction);
		void SetVelocity(Ogre::Vector3 arg_velocity);

	protected:
		Ogre::Vector3 mVelocity;
		Ogre::Vector3 mRequestedInput;
		MovementMode mMovementMode;
		std::unordered_map<MovementMode, MovementModeSettings> mMovementModeSettings;
	};
}

#endif
