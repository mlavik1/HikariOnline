#include "client_network_controller.h"

#include "Core/Actor/player_character.h"
#include "Core/Component/mesh_component.h"
#include "Core/Controller/client_controller.h"
#include "Core/Engine/client.h"
#include "Core/Engine/world_server.h"
#include "Core/Managers/network_manager.h"
#include "Core/Networking/rpc.h"

namespace Hikari
{
	IMPLEMENT_CLASS(Hikari::ClientNetworkController)

		ClientNetworkController::ClientNetworkController()
		:NetworkController()
	{

	}
	/*
	void ClientNetworkController::WorldServerCreatePlayer()
	{
#ifdef HIKARI_WORLDSERVER
		PlayerCharacter* playerChar = CreatePlayerInternal();
		GameEngine::Instance()->GetNetworkManager()->GenerateNetGUID(playerChar);

		auto clientList = GameEngine::Instance()->GetWorldServer()->GetConnectedClients();
		for (auto client : clientList)
		{
			ClientCall(client.second.mClientID, this, ClientSendMessage, arg_message);
		}
#endif
	}

	void ClientNetworkController::ClientCreatePlayer(NetGUID arg_netguid, bool arg_owner)
	{
		PlayerCharacter* playerChar = CreatePlayerInternal();
		playerChar->SetNetGUID(arg_netguid);

		if (arg_owner)
		{
			GameEngine::Instance()->GetClient()->GetInGameController()->SetControlledCharacter(actor);
		}
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
	}
	*/
}
