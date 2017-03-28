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

		class ClientGameServerConnectionData
		{
		public:
			uint32_t GameServerNetworkControllerNetGUID;
			uint32_t ClientNetworkControllerNetGUID;
		};

		class ChatMessage
		{
		public:
			char Message[100];

			ChatMessage(){}

			ChatMessage(const char* arg_message)
			{
				memcpy(Message, arg_message, strlen(arg_message) + 1);
			}
		};

	}
}

#endif
