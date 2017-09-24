#include "game_server_network_controller.h"
#include "Core/Debug/debug.h"
#include "Core/Networking/rpc.h"
#include "Core/Engine/game_instance.h"
#include "Core/Engine/game_server.h"
#ifdef HIKARI_CLIENT
#include "Core/Managers/window_manager.h"
#include "GUI/game_hud.h"
#endif

namespace Hikari
{
	IMPLEMENT_CLASS(Hikari::GameServerNetworkController)

	REGISTER_CLASSPROPERTIES(Hikari::GameServerNetworkController)

	GameServerNetworkController::GameServerNetworkController(GameInstance* arg_gameinstance)
		:NetworkController(arg_gameinstance)
	{

	}

	void GameServerNetworkController::ServerSendMessage(NetMessageData::ChatMessage arg_message)
	{
		LOG_INFO() << "Called ServerSendMessage: " << arg_message.Message;

#ifdef HIKARI_GAMESERVER
		auto clientList = mGameInstance->GetGameServer()->GetConnectedClients();
		for (auto client : clientList)
		{
			ClientCall(client.second.mClientID, this, ClientSendMessage, arg_message);
		}
#endif
	}

	void GameServerNetworkController::ClientSendMessage(NetMessageData::ChatMessage arg_message)
	{
		LOG_INFO() << "Called ClientSendMessage: " << arg_message.Message;
#ifdef HIKARI_CLIENT
		GameHUD* hud = (GameHUD*)mGameInstance->GetWindowManager()->GetWindow(GameHUD::GetStaticClass());
		hud->AddChatMessage(arg_message.Message);
#endif
	}
}
