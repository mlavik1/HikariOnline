#include "ingame_controller.h"
#include "Core/Actor/player_character.h"
#include "Core/Debug/st_assert.h"
#include "Core/Engine/client.h"
#include "Core/Engine/game_instance.h"
#include "Core/World/world.h"
#include "Core/Component/movement_component.h"
#include "Core/Component/mesh_component.h"
#include "Core/Managers/input_manager.h"

namespace Hikari
{
	InGameController::InGameController(Client* arg_client)
		: ClientController(arg_client)
	{

	}

	void InGameController::Tick(float arg_deltatime)
	{
		ClientController::Tick(arg_deltatime);

		if (mControlledCharacter != nullptr)
		{
			GameInstance* gameInstance = mClient->GetGameInstance();
			MeshComponent* meshComp = mControlledCharacter->GetComponentOfType<MeshComponent>();

			// TODO: do this in MovementCOmponent
			float terrainHeight = gameInstance->GetWorld()->GetTerrainHeight(mControlledCharacter->GetPositionAbsolute().x, mControlledCharacter->GetPositionAbsolute().z);
			//std::cout << terrainHeight << std::endl;
			mControlledCharacter->SetPosition(Ogre::Vector3(mControlledCharacter->GetPosition().x, terrainHeight, mControlledCharacter->GetPosition().z));
			
			if (gameInstance->GetInputManager()->GetKeyDown("1"))
			{
				meshComp->SetActiveAnimation("idle");
			}
			else if (gameInstance->GetInputManager()->GetKeyDown("2"))
			{
				meshComp->SetActiveAnimation("walk");
			}

			if (gameInstance->GetInputManager()->GetKey("d"))
			{
				mControlledCharacter->Rotate(Ogre::Vector3::UNIT_Y, 1.8f);
			}
			if (gameInstance->GetInputManager()->GetKey("a"))
			{
				mControlledCharacter->Rotate(Ogre::Vector3::UNIT_Y, -1.8f);
			}

			if (gameInstance->GetInputManager()->GetKey("up"))
			{
				mControlledCharacter->GetMovementComponent()->AddInput(mControlledCharacter->GetForwardVector());
			}
			else if (gameInstance->GetInputManager()->GetKey("down"))
			{
				mControlledCharacter->GetMovementComponent()->AddInput(mControlledCharacter->GetUpVector());
			}
			else
			{
				mControlledCharacter->GetMovementComponent()->SetVelocity(Ogre::Vector3::ZERO);
			}
		}
	}

	void InGameController::SetControlledCharacter(PlayerCharacter* arg_character)
	{
		mControlledCharacter = arg_character;
	}
}
