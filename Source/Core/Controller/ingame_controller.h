#ifndef HIKARI_INGAMECONTROLLER_H
#define HIKARI_INGAMECONTROLLER_H

#include "client_controller.h"
#include "Core/Object/objectptr.h"

namespace Hikari
{
	class PlayerCharacter;
	class Client;

	class InGameController : public ClientController
	{
	protected:
		ObjectPtr<PlayerCharacter> mControlledCharacter;

	public:
		InGameController(Client* arg_client);
		
		virtual void Tick(float arg_deltatime) override;
		
		void SetControlledCharacter(PlayerCharacter* arg_character);
	};
}

#endif
