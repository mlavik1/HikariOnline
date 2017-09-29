#include "game_object.h"

#include "Core/Managers/input_manager.h"
#include "Core/Managers/tick_manager.h"
#include "Core/World/world.h"

#include "Core/Networking/rpc.h"
#include "Core/Networking/initial_replication_data.h"

IMPLEMENT_CLASS(Hikari::GameObject)

REGISTER_CLASSPROPERTIES(Hikari::GameObject)

namespace Hikari
{
	GameObject::GameObject()
	{
	}

	GameObject* GameObject::CreateGameObject(Class* arg_class)
	{
		__Assert(arg_class->IsA(GameObject::GetStaticClass()));

		GameObject* gameObject = static_cast<GameObject*>(arg_class->CreateInstance());
		gameObject->InitialiseObject(ObjectInitialiserParams()); // todo
		return gameObject;
	}


	void GameObject::Initialise()
	{

	}

	void GameObject::OnStart()
	{

	}

	void GameObject::OnStop()
	{

	}

	void GameObject::ReplicateInitialData()
	{
#ifndef HIKARI_CLIENT
		InitialReplicationData* repData = CreateInitialReplicationData();
		if (repData != nullptr)
		{
			SerialisedDataContainer serialisedDataContainer;
			serialisedDataContainer.SetData(repData, repData->GetSize());
			ClientCall(-1, this, ClientReceiveInitialReplicationData, serialisedDataContainer);
		}
#endif
	}

	void GameObject::ClientReceiveInitialReplicationData(SerialisedDataContainer arg_datacontainer)
	{
		ClientOnInitialReplication((InitialReplicationData*)arg_datacontainer.GetData());
	}

}
