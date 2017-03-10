#include "ingame_controller.h"
#include "Core/Actor/player_character.h"
#include "Core/Debug/st_assert.h"
#include "Core/Engine/client.h"
#include "Core/Engine/game_instance.h"
#include "Core/World/world.h"
#include "Core/Component/movement_component.h"
#include "Core/Component/mesh_component.h"
#include "Core/Managers/input_manager.h"
#include "Core/Component/camera_component.h"
#include "Core/Misc/geometry_queries.h"
#include "Core/Debug/debug_graphics.h"

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
			mControlledCharacter->SetPosition(Ogre::Vector3(mControlledCharacter->GetPosition().x, terrainHeight, mControlledCharacter->GetPosition().z));
			
			// move camera with character
			mCameraAttachPoint->SetPosition(mControlledCharacter->GetPositionAbsolute());

			Hikari::InputManager* inputManager = gameInstance->GetInputManager();

			bool bRotateWithMouse = inputManager->GetMousePressed(1);

			if (bRotateWithMouse)
			{
				const Ogre::Vector2& inputAxis = inputManager->GetMouseMove();
				if (inputAxis.squaredLength() > 0.0f)
				{
					const float mouseSensitivity = 25.0f;
					Ogre::Vector3 rotationAxis3D = Ogre::Vector3::UNIT_Y * -1.0f * inputAxis.x;
					rotationAxis3D += mCameraAttachPoint->GetRightVector() * 1.0f * inputAxis.y;
					mCameraAttachPoint->Rotate(rotationAxis3D.normalisedCopy(), rotationAxis3D.length() * arg_deltatime * mouseSensitivity);
				}
			}

			bool bIsMoving = false;

			if (gameInstance->GetInputManager()->GetKey("d"))
			{
				mControlledCharacter->Rotate(Ogre::Vector3::UNIT_Y, -85.0f * arg_deltatime);
			}
			if (gameInstance->GetInputManager()->GetKey("a"))
			{
				mControlledCharacter->Rotate(Ogre::Vector3::UNIT_Y, 85.0f * arg_deltatime);
			}

			if (gameInstance->GetInputManager()->GetKey("w"))
			{
				mControlledCharacter->GetMovementComponent()->AddInput(mControlledCharacter->GetForwardVector());
				bIsMoving = true;
			}
			else if (gameInstance->GetInputManager()->GetKey("s"))
			{
				mControlledCharacter->GetMovementComponent()->AddInput(mControlledCharacter->GetUpVector());
				bIsMoving = true;
			}
			else if (mTargetPoint != Ogre::Vector3::ZERO)
			{
				bIsMoving = true;
			}
			else 
			{
				mControlledCharacter->GetMovementComponent()->SetVelocity(Ogre::Vector3::ZERO);
			}


			if (bIsMoving)
			{
				if (meshComp->GetActiveAnimation() == nullptr || meshComp->GetActiveAnimation()->GetName() == "idle")
				{
					meshComp->SetActiveAnimation("walk");
				}
			}
			else
			{
				if (meshComp->GetActiveAnimation() != nullptr && meshComp->GetActiveAnimation()->GetName() == "walk")
				{
					meshComp->SetActiveAnimation("idle");
				}
			}

			// Set new target point?
			if (inputManager->GetMouseReleased(0))
			{
				const Ogre::Vector2& mousePos = inputManager->GetMousePosition();
				Ogre::Vector2 mouseRelativePos = mCameraComponent->AbsToRelScreenPos(mousePos);
				Ogre::Ray mouseRay = mCameraComponent->ScreenPosToWorldRay(mouseRelativePos);
				Ogre::Vector3 terrainPos;
				bool bHit = GeometryQueries::TraceTerrain(gameInstance->GetWorld(), mouseRay.getOrigin(), mouseRay.getOrigin() + mouseRay.getDirection() * 500.0f, 0.5f, 0.01f, &terrainPos);
				if (bHit)
				{
					mTargetPoint = terrainPos;

					Ogre::Vector3 lookatTarget = mTargetPoint;
					lookatTarget.y = mControlledCharacter->GetPositionAbsolute().y;
					mControlledCharacter->LookAt(lookatTarget);
					mControlledCharacter->GetMovementComponent()->SetVelocity(Ogre::Vector3::ZERO);

					std::vector<Ogre::Vector3> points;
					points.push_back(terrainPos);
					DebugGraphics::DrawDebugPoints(gameInstance->GetWorld(), points, 15.0f, Ogre::ColourValue::Red, 10.0f);
				}
			}

			// Move towards target point
			if (mTargetPoint != Ogre::Vector3::ZERO)
			{
				Ogre::Vector3 dir = mTargetPoint - mControlledCharacter->GetPositionAbsolute();
				mControlledCharacter->GetMovementComponent()->AddInput(dir);
			}
		} // if (mControlledCharacter != nullptr)
	}

	void InGameController::SetControlledCharacter(PlayerCharacter* arg_character)
	{
		mControlledCharacter = arg_character;

		GameInstance* gameInstance = mClient->GetGameInstance();

		mCameraActor = new Hikari::Actor(gameInstance->GetWorld());
		mCameraAttachPoint = new Hikari::Actor(gameInstance->GetWorld());
		mCameraActor->SetPosition(Ogre::Vector3(0.0f, 0.0f, -7.0f));
		mCameraActor->Rotate(Ogre::Vector3::UNIT_X, 0.0f);
		mCameraComponent = mCameraActor->AddComponent<Hikari::CameraComponent>();

		mCameraActor->SetParent(mCameraAttachPoint);

		mCameraAttachPoint->Rotate(Ogre::Vector3(1.0f, 0.0f, 0.0f), 40.0f);


		MeshComponent* meshComp = mControlledCharacter->GetComponentOfType<MeshComponent>();
		meshComp->SetActiveAnimation("idle");
		
		mCameraComponent->Initialise();
	}
}
