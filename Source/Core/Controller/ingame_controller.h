#ifndef HIKARI_INGAMECONTROLLER_H
#define HIKARI_INGAMECONTROLLER_H

#include "client_controller.h"
#include "Core/Object/objectptr.h"
#include "OGRE/Ogre.h"

namespace Hikari
{
	class PlayerCharacter;
	class Client;
	class Actor;
	class CameraComponent;

	class InGameController : public ClientController
	{
	protected:
		ObjectPtr<PlayerCharacter> mControlledCharacter;
		Actor* mCameraActor = nullptr;
		Actor* mCameraAttachPoint = nullptr;
		CameraComponent* mCameraComponent = nullptr;
		Ogre::Vector3 mTargetPoint = Ogre::Vector3::ZERO;

	public:
		InGameController(Client* arg_client);
		
		virtual void Tick(float arg_deltatime) override;
		
		void SetControlledCharacter(PlayerCharacter* arg_character);
	};
}

#endif
