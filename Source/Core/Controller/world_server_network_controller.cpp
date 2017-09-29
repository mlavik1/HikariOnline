#include "world_server_network_controller.h"

#include "Core/Actor/player_character.h"
#include "Core/Component/mesh_component.h"
#include "Core/Controller/client_controller.h"
#include "Core/Engine/client.h"
#include "Core/Engine/world_server.h"
#include "Core/Managers/network_manager.h"
#include "Core/Networking/rpc.h"

IMPLEMENT_CLASS(Hikari::WorldServerNetworkController)

REGISTER_CLASSPROPERTIES(Hikari::WorldServerNetworkController)

namespace Hikari
{
	WorldServerNetworkController::WorldServerNetworkController()
		:NetworkController()
	{

	}

	Object* WorldServerNetworkController::ServerCreateNetworkedObjectByClass(Class* arg_class)
	{
		Object* obj = nullptr;
#ifdef HIKARI_WORLDSERVER
		obj = arg_class->CreateInstance();
		GameEngine::Instance()->GetNetworkManager()->GenerateNetGUID(obj);

		std::string className = arg_class->GetName();
		NetGUID netGUID = obj->GetNetGUID();

		auto clientList = GameEngine::Instance()->GetWorldServer()->GetConnectedClients();
		for (auto client : clientList)
		{
			ClientCall(client.second.mClientID, this, ClientCreateNetworkedObjectByClass, className, netGUID);
		}
#endif
		return obj;
	}

	void WorldServerNetworkController::ClientCreateNetworkedObjectByClass(std::string arg_classname, NetGUID arg_guid)
	{
#ifdef HIKARI_CLIENT
		Class* objClass = Class::GetClassByName(arg_classname.c_str(), false);
		if (objClass != nullptr)
		{
			Object* obj = objClass->CreateInstance();
			obj->SetNetGUID(arg_guid);
			GameEngine::Instance()->GetNetworkManager()->RegisterObject(obj);
		}
#endif
	}

}
