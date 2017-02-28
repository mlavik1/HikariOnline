#ifndef HIKARI_INGAMECONTROLLER_H
#define HIKARI_INGAMECONTROLLER_H

#include "client_controller.h"
#include "Core/Object/objectptr.h"

namespace Hikari
{
	class PlayerCharacter;
	class Client;
	class Actor;

	class InGameController : public ClientController
	{
	protected:
		ObjectPtr<PlayerCharacter> mControlledCharacter;
		Actor* mCameraActor = nullptr;
		Actor* mCameraAttachPoint = nullptr;

	public:
		InGameController(Client* arg_client);
		
		virtual void Tick(float arg_deltatime) override;
		
		void SetControlledCharacter(PlayerCharacter* arg_character);
	};
}

#endif
