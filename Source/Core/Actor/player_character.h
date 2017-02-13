#ifndef HIKARI_PLAYERCHARACTER_H
#define HIKARI_PLAYERCHARACTER_H

#include "character.h"

namespace Hikari
{
	class PlayerCharacter : public Hikari::Character
	{
		DEFINE_CLASS(Hikari::PlayerCharacter, Hikari::Character)
	public:
		PlayerCharacter(Hikari::World* arg_world);
	};
}

#endif
