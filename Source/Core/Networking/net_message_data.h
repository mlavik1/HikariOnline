#ifndef HIKARI_NETMESSAGEDATA_H
#define HIKARI_NETMESSAGEDATA_H

#include <stdint.h>
#include <algorithm>

namespace Hikari
{
	namespace NetMessageData
	{
		class ClientInfo
		{
		public:
			char IPAddress[16]; // xxx.xxx.xxx.xxx
			char AccountName[32];
			ClientInfo() {}
			ClientInfo(const char* arg_ip, const char* arg_account)
			{
				std::memcpy(AccountName, arg_account, std::min((size_t)32, strlen(arg_account) + 1));
				std::memcpy(IPAddress, arg_ip, std::min((size_t)16, strlen(arg_ip) + 1));
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

	}
}

#endif
