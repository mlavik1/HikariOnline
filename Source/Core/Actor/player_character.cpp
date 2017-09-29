#include "player_character.h"
#include "Core/Debug/debug.h"
#include "Core/Component/mesh_component.h"
#include "Core/Engine/game_engine.h"
#include "Core/Engine/client.h"
#include "Core/Controller/ingame_controller.h"

IMPLEMENT_CLASS(Hikari::PlayerCharacter)

namespace Hikari
{
	PlayerCharacter::PlayerCharacter()
		: Character::Character()
	{

	}

	InitialReplicationData* PlayerCharacter::CreateInitialReplicationData()
	{
		InitialReplicationData_PlayerCharacter* repData = new InitialReplicationData_PlayerCharacter();

		repData->Position = GetPosition();

		return repData;
	}

	void PlayerCharacter::ClientOnInitialReplication(InitialReplicationData* arg_data)
	{
#ifdef HIKARI_CLIENT
		InitialReplicationData_PlayerCharacter* repData = (InitialReplicationData_PlayerCharacter*)arg_data;
		if (repData == nullptr)
		{
			LOG_ERROR() << "PlayerCharacter::ClientOnInitialReplication received bad data";
			return;
		}

		Initialise();
		SetScale(Ogre::Vector3(1, 1, 1));
		//SetPosition(Ogre::Vector3(130.0f, 2.0f, 130.0f));
		SetPosition(repData->Position);

		MeshComponent* meshComp = AddComponent<Hikari::MeshComponent>();
		meshComp->SetMesh("GMObject0.mesh");
		meshComp->Initialise(); // TODO: MAKE AUTOMATIC
		
		// TEMP: DO FROM RPC
		GameEngine::Instance()->GetClient()->GetInGameController()->SetControlledCharacter(this);
#endif
	}
}
