#include "rpc.h"
#include "Core/Object/game_object.h"
#include "Core/Engine/game_instance.h"
#include "Core/Engine/client.h"
#include "Core/Managers/network_manager.h"

namespace Hikari
{
	void RPCCaller::RPC_GameServerCall(GameObject* arg_object, const char* arg_function, FunctionArgContainer arg_funcargs)
	{
		// Get Network GUID
		NetGUID guid = arg_object->GetNetGUID();

		// Create message
		const size_t funcNameLen = std::strlen(arg_function) + 1;
		size_t dataSize = sizeof(NetGUID) + funcNameLen + sizeof(size_t) + arg_funcargs.mSize;
		char* data = new char[dataSize];
		memcpy(data, &guid, sizeof(NetGUID));
		memcpy(data + sizeof(NetGUID), arg_function, funcNameLen);
		memcpy(data + sizeof(NetGUID) + funcNameLen, &arg_funcargs.mSize, sizeof(size_t));
		memcpy(data + sizeof(NetGUID) + funcNameLen + sizeof(size_t), arg_funcargs.mData, arg_funcargs.mSize);
		NetMessage* rpcMessage = new NetMessage(NetMessageType::RPC);
		rpcMessage->SetMessageDataPtr(data, dataSize);

		// Send message
#ifdef HIKARI_CLIENT
		Client* client = arg_object->GetGameInstance()->GetClient();
		client->SendMessageToGameServer(rpcMessage);
#endif

		// TODO: #ifdef HIKARI_WORLDSERVER
	}

	void RPCCaller::HandleIncomingRPC(const NetMessage* arg_message, GameInstance* arg_gameinstance)
	{
		const char* dataPtr = arg_message->GetMessageData();
		NetGUID guid = *reinterpret_cast<const NetGUID*>(dataPtr);
		dataPtr += sizeof(NetGUID);
		std::string funcName(dataPtr);
		dataPtr += funcName.size() + 1;
		FunctionArgContainer funcArgs;
		funcArgs.mSize = *reinterpret_cast<const size_t*>(dataPtr);
		dataPtr += sizeof(size_t);
		funcArgs.mData = new char[funcArgs.mSize];
		memcpy(funcArgs.mData, dataPtr, funcArgs.mSize);

		Hikari::GameObject* obj = static_cast<Hikari::GameObject*>(arg_gameinstance->GetNetworkManager()->GetObject(guid));
		if (obj != nullptr)
		{
			Hikari::Function* func = obj->GetClass()->GetFunctionByName(funcName.c_str());
			if (func != nullptr)
			{
				obj->CallFunction(func, funcArgs);
			}
			else
			{
				LOG_ERROR() << "Function not found: " << funcName.c_str();
			}
		}
		else
		{
			LOG_ERROR() << "Cannot find object with GUID: " << guid;
		}
	}
}
