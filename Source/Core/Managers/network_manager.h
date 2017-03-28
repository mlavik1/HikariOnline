#ifndef HIKARI_NETWORKMANAGER_H
#define HIKARI_NETWORKMANAGER_H

#include "Core/Object/object.h"
#include <unordered_map>

#ifdef HIKARI_GAMESERVER
#define GUIDRANGE_START 1
#elif HIKARI_WORLDSERVER
#define GUIDRANGE_START 10000
#endif

namespace Hikari
{
	class NetworkManager
	{
	private:
		std::unordered_map<NetGUID, Hikari::Object*> mNetworkObjects;
#if defined(HIKARI_GAMESERVER) || defined(HIKARI_WORLDSERVER)
		uint32_t mNetGUIDSequence = GUIDRANGE_START;
#endif

	public:
		Hikari::Object* GetObjectByGUID(NetGUID arg_guid);

#if defined(HIKARI_GAMESERVER) || defined(HIKARI_WORLDSERVER)
		void GenerateNetGUID(Hikari::Object* arg_object);
#endif
		void RegisterObject(Hikari::Object* arg_object);
		void UnRegisterObject(Hikari::Object* arg_object);
	};
}

#endif
