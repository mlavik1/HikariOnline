#ifndef HIKARI_CLIENTNETWORKCONTROLLER_H
#define HIKARI_CLIENTNETWORKCONTROLLER_H

/*=============================================================================================
Controller for one-way communication from server to a client.

==============================================================================================*/

#include "network_controller.h"

namespace Hikari
{
	class PlayerCharacter;

	class ClientNetworkController : public Hikari::NetworkController
	{
		DEFINE_CLASS(Hikari::ClientNetworkController, Hikari::NetworkController)

	public:
		ClientNetworkController();
		/*
		void ServerCreateNetworkedObjectByClass(Class* arg_class);
		void ClintCreateNetworkedObjectByClass(std::string arg_classname, NetGUID arg_guid);

		DEFINE_FUNCTION(ClintCreateNetworkedObjectByClass, std::string, NetGUID)

		BEGIN_REGISTER_CLASSPROPERTIES(Hikari::ClientNetworkController)
			REGISTER_CLASS_FUNCTION(Hikari::ClientNetworkController, ClintCreateNetworkedObjectByClass)
		END_REGISTER_CLASSPROPERTIES(Hikari::ClientNetworkController)
		*/
	};
}

#endif
