#ifndef HIKARI_NETMESSAGEDATA_H
#define HIKARI_NETMESSAGEDATA_H

#include <stdint.h>
#include <algorithm>
#include "Core/Object/objdefs.h"
#include "Core/Serialisation/i_serialisable.h"

namespace Hikari
{
	namespace NetMessageData
	{
		class ClientInfo
		{
		public:
			char mIPAddress[16]; // xxx.xxx.xxx.xxx
			char mAccountName[32];
			NetGUID mNetGUID;
			
			ClientInfo() { }
			ClientInfo(const char* arg_ip, const char* arg_account, NetGUID arg_guid = 0)
			{
				std::memcpy(mAccountName, arg_account, std::min((size_t)32, strlen(arg_account) + 1));
				std::memcpy(mIPAddress, arg_ip, std::min((size_t)16, strlen(arg_ip) + 1));
				mNetGUID = arg_guid;
			}

		};

		class WorldServerInfo
		{
		public:
			char IPAddress[16]; // xxx.xxx.xxx.xxx
			char ServerName[32];
			WorldServerInfo() {}
			WorldServerInfo(const char* arg_ip, const char* arg_name)
			{
				std::memcpy(ServerName, arg_name, std::min((size_t)32, strlen(arg_name) + 1));
				std::memcpy(IPAddress, arg_ip, std::min((size_t)16, strlen(arg_ip) + 1));
			}
		};

		class WorldServerList
		{
		public:
			uint8_t NumServers;
			WorldServerInfo ServerInfos[9];
		};

		class ClientGameServerConnectionData
		{
		public:
			uint32_t GameServerNetworkControllerNetGUID;
			uint32_t ClientNetworkControllerNetGUID;
		};

		class ClientWorldServerConnectionData
		{
		public:
			uint32_t WorldServerNetworkControllerNetGUID;
			uint32_t ClientNetworkControllerNetGUID;
		};

	}
}

#endif
