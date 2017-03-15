#ifndef HIKARI_NETMESSAGEDATA_H
#define HIKARI_NETMESSAGEDATA_H

#include <stdint.h>

namespace Hikari
{
	namespace NetMessageData
	{
		class WorldServerInfo
		{
		public:
			int test;
			char IPAddress[16]; // xxx.xxx.xxx.xxx
			char ServerName[32];

		};

		class WorldServerList
		{
		public:
			uint8_t NumServers;
			WorldServerInfo ServerInfos[9];
		};

	}
}

#endif
