#ifndef HIKARI_NETWORKMANAGER_H
#define HIKARI_NETWORKMANAGER_H

#include "Core/Object/object.h"
#include <unordered_map>

namespace Hikari
{
	class NetworkManager
	{
	private:
		std::unordered_map<NetworkGUID, Hikari::Object*> mNetworkObjects;

	public:
		Hikari::Object* GetObject(NetworkGUID arg_guid);
		void RegisterObject(Hikari::Object* arg_object);
		void UnRegisterObject(Hikari::Object* arg_object);
	};
}

#endif
