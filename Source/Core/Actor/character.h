#ifndef HIKARI_CHARACTER_H
#define HIKARI_CHARACTER_H

#include "actor.h"

namespace Hikari
{
	class Character : public Hikari::Actor
	{
		DEFINE_CLASS(Hikari::Character, Hikari::Actor)
	public:
		Character(Hikari::World* arg_world);
	};
}

#endif
