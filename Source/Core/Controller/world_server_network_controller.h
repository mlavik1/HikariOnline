#ifndef HIKARI_WORLDSERVERNETWORKCONTROLLER_H
#define HIKARI_WORLDSERVERNETWORKCONTROLLER_H

/*=============================================================================================
Class used for communication between world server and clients.
==============================================================================================*/

#include "network_controller.h"

namespace Hikari
{
	class PlayerCharacter;

	class WorldServerNetworkController : public Hikari::NetworkController
	{
		DEFINE_CLASS(Hikari::WorldServerNetworkController, Hikari::NetworkController)

	public:
		WorldServerNetworkController();

		Object* ServerCreateNetworkedObjectByClass(Class* arg_class);
		void ClientCreateNetworkedObjectByClass(std::string arg_classname, NetGUID arg_guid);

		DEFINE_FUNCTION(ClientCreateNetworkedObjectByClass, std::string, NetGUID)

		BEGIN_REGISTER_CLASSPROPERTIES(Hikari::WorldServerNetworkController)
			REGISTER_CLASS_FUNCTION(Hikari::WorldServerNetworkController, ClientCreateNetworkedObjectByClass)
		END_REGISTER_CLASSPROPERTIES(Hikari::WorldServerNetworkController)
	};
}

#endif
