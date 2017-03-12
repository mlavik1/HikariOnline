#include "network_manager.h"

namespace Hikari
{
	Hikari::Object* NetworkManager::GetObject(NetworkGUID arg_guid)
	{
		auto objIter = mNetworkObjects.find(arg_guid);
		Hikari::Object* obj = (objIter != mNetworkObjects.end()) ? (*objIter).second : nullptr;
		return obj;
	}

	void NetworkManager::RegisterObject(Hikari::Object* arg_object)
	{
		const NetworkGUID& guid = arg_object->GetNetworkGUID();
		mNetworkObjects[guid] = arg_object;
	}

	void NetworkManager::UnRegisterObject(Hikari::Object* arg_object)
	{
		mNetworkObjects.erase(arg_object->GetNetworkGUID());
	}
}
