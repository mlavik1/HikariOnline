#ifndef HIKARI_PLAYERCHARACTER_H
#define HIKARI_PLAYERCHARACTER_H

#include "character.h"

namespace Hikari
{
	struct InitialReplicationData_PlayerCharacter : InitialReplicationData
	{
		Ogre::Vector3 Position;
	};

	class PlayerCharacter : public Hikari::Character
	{
		DEFINE_CLASS(Hikari::PlayerCharacter, Hikari::Character)
	public:
		PlayerCharacter(Hikari::World* arg_world);

		virtual InitialReplicationData* GetInitialReplicationData() override;
		virtual void ClientOnInitialReplication(InitialReplicationData* arg_data) override;
	};
}

#endif
