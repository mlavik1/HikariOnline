#ifndef HIKARI_RPC_H
#define HIKARI_RPC_H

#include "Core/Object/function.h"

namespace Hikari
{
	class GameObject;
	class NetMessage;
	class GameInstance;

	class RPCCaller
	{
	public:
		static void RPC_GameServerCall(GameObject* arg_object, const char* arg_function, FunctionArgContainer arg_funcargs);

		static void HandleIncomingRPC(const NetMessage* arg_message, GameInstance* arg_gameinstance);
	};
}


//#if defined(HIKARI_CLIENT) || defined(HIKARI_WORLDSERVER)
#define GameServerCall(objectptr, functionname, ...) \
	RPCCaller::RPC_GameServerCall(objectptr, #functionname, objectptr->getargs_##functionname##(__VA_ARGS__));
//#endif

#endif
