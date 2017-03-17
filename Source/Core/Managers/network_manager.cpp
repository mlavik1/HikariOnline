#include "network_manager.h"

namespace Hikari
{
	Hikari::Object* NetworkManager::GetObject(NetGUID arg_guid)
	{
		auto objIter = mNetworkObjects.find(arg_guid);
		Hikari::Object* obj = (objIter != mNetworkObjects.end()) ? (*objIter).second : nullptr;
		return obj;
	}

#if defined(HIKARI_GAMESERVER) || defined(HIKARI_WORLDSERVER)
	void NetworkManager::GenerateNetGUID(Hikari::Object* arg_object)
	{
		arg_object->SetNetGUID(mNetGUIDSequence++);
	}
#endif

	void NetworkManager::RegisterObject(Hikari::Object* arg_object)
	{
		const NetGUID& guid = arg_object->GetNetGUID();
		mNetworkObjects[guid] = arg_object;
	}

	void NetworkManager::UnRegisterObject(Hikari::Object* arg_object)
	{
		mNetworkObjects.erase(arg_object->GetNetGUID());
	}
}
