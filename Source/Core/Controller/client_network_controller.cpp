#include "client_network_controller.h"
/*
#include "Core/Actor/player_character.h"
#include "Core/Component/mesh_component.h"
#include "Core/Controller/client_controller.h"
#include "Core/Engine/client.h"
#include "Core/Engine/world_server.h"
#include "Core/Managers/network_manager.h"
#include "Core/Networking/rpc.h"
*/
namespace Hikari
{
	IMPLEMENT_CLASS(Hikari::ClientNetworkController)

		ClientNetworkController::ClientNetworkController()
		:NetworkController()
	{

	}
	/*
	void ClientNetworkController::ServerCreateNetworkedObjectByClass(Class* arg_class)
	{
#ifdef HIKARI_WORLDSERVER
		Object* obj = arg_class->CreateInstance();
		GameEngine::Instance()->GetNetworkManager()->GenerateNetGUID(obj);

		std::string className = arg_class->GetName();
		NetGUID netGUID = obj->GetNetGUID();

		auto clientList = GameEngine::Instance()->GetWorldServer()->GetConnectedClients();
		for (auto client : clientList)
		{
			ClientCall(client.second.mClientID, this, ClintCreateNetworkedObjectByClass, className, netGUID);
		}
#endif
	}

	void ClientNetworkController::ClintCreateNetworkedObjectByClass(std::string arg_classname, NetGUID arg_guid)
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

	PlayerCharacter* ClientNetworkController::CreatePlayerInternal()
	{
		Hikari::PlayerCharacter* actor = new Hikari::PlayerCharacter(GameEngine::Instance()->GetWorld());
		actor->Initialise();
		actor->SetScale(Ogre::Vector3(1, 1, 1));
		actor->SetPosition(Ogre::Vector3(130.0f, 2.0f, 130.0f));

		Hikari::MeshComponent* meshComp = actor->AddComponent<Hikari::MeshComponent>();
		meshComp->SetMesh("GMObject0.mesh");
		meshComp->Initialise();

		GameEngine::Instance()->GetClient()->GetInGameController()->SetControlledCharacter(actor);

		return actor;
	}*/
	
}
