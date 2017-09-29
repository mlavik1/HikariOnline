#ifndef HIKARI_PLAYERCHARACTER_H
#define HIKARI_PLAYERCHARACTER_H

#include "character.h"

#include "Core/Networking/initial_replication_data.h"

namespace Hikari
{
	class InitialReplicationData_PlayerCharacter : public InitialReplicationData
	{
	public:
		Ogre::Vector3 Position;

		virtual size_t GetSize() override { return sizeof(*this); }
	};

	class PlayerCharacter : public Hikari::Character
	{
		DEFINE_CLASS(Hikari::PlayerCharacter, Hikari::Character)
	public:
		PlayerCharacter();

		virtual InitialReplicationData* CreateInitialReplicationData() override;
		virtual void ClientOnInitialReplication(InitialReplicationData* arg_data) override;
	};
}

#endif
