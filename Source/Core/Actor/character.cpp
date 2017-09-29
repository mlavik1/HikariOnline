#include "character.h"
#include "Core/Component/movement_component.h"

IMPLEMENT_CLASS(Hikari::Character)

namespace Hikari
{
	Character::Character()
		: Actor::Actor()
	{
		mMovementComponent = AddComponent<Hikari::MovementComponent>();
		mMovementComponent->Initialise(); // TODO: this should not be necessary to call manually
	}

	MovementComponent* Character::GetMovementComponent()
	{
		return mMovementComponent;
	}
}
