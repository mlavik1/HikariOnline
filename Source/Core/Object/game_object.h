#ifndef HIKARI_GAMEOBJECT_H
#define HIKARI_GAMEOBJECT_H

#include "Core/Object/object.h"
#include "Core/Debug/st_assert.h"

#include "Core/Networking/initial_replication_data.h"
#include "Core/Serialisation/serialised_data_container.h"

namespace Hikari
{
	class TickManager;
	class InputManager;
	class InitialReplicationData;

	class GameObject : public Hikari::Object
	{
		DEFINE_CLASS(Hikari::GameObject, Hikari::Object)

	public:
		GameObject();

		static GameObject* CreateGameObject(Class* arg_class);

		template<typename T>
		static T* CreateGameObject()
		{
			__AssertComment((std::is_base_of<GameObject, T>::value), "Must be subclass of GameObject");
			return static_cast<T*>(CreateGameObject(T::GetStaticClass()));
		}

		virtual void Initialise();
		//virtual void Tick() = 0;
		virtual void OnStart();
		virtual void OnStop();

		virtual InitialReplicationData* CreateInitialReplicationData() { return nullptr; }
		virtual void ClientOnInitialReplication(InitialReplicationData* arg_data) {}

		virtual void ReplicateInitialData();
		virtual void ClientReceiveInitialReplicationData(SerialisedDataContainer arg_datacontainer);

		DEFINE_FUNCTION(ReplicateInitialData)
		DEFINE_FUNCTION(ClientReceiveInitialReplicationData, SerialisedDataContainer)

		BEGIN_REGISTER_CLASSPROPERTIES(Hikari::GameObject)
			REGISTER_CLASS_FUNCTION(Hikari::GameObject, ReplicateInitialData)
			REGISTER_CLASS_FUNCTION(Hikari::GameObject, ClientReceiveInitialReplicationData)
		END_REGISTER_CLASSPROPERTIES(Hikari::GameObject)

	};
}

#endif
