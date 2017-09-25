#ifndef HIKARI_RPC_H
#define HIKARI_RPC_H

#include "Core/Object/function.h"

namespace Hikari
{
	class GameObject;
	class NetMessage;

	class RPCCaller
	{
	public:
		static void RPC_GameServerCall(GameObject* arg_object, const char* arg_function, FunctionArgContainer arg_funcargs);
		static void RPC_ClientCall(int arg_clientid, GameObject* arg_object, const char* arg_function, FunctionArgContainer arg_funcargs);
		
		static void ClientSendMessage(int arg_clientid, NetMessage* arg_message);

		static void HandleIncomingRPC(const NetMessage* arg_message);

	private:
		static NetMessage* createNetMessage(const NetGUID& arg_guid, const char* arg_function, const FunctionArgContainer& arg_funcargs);
	};
}


//#if defined(HIKARI_CLIENT) || defined(HIKARI_WORLDSERVER)
#define GameServerCall(objectptr, functionname, ...) \
	RPCCaller::RPC_GameServerCall(objectptr, #functionname, objectptr->getargs_##functionname##(__VA_ARGS__));
//#endif
#define ClientCall(clientid, objectptr, functionname, ...) \
	RPCCaller::RPC_ClientCall(clientid, objectptr, #functionname, objectptr->getargs_##functionname##(__VA_ARGS__));

#endif
