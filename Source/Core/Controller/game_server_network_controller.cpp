#include "game_server_network_controller.h"
#include "Core/Debug/debug.h"
#include "Core/Networking/rpc.h"
#include "Core/Engine/game_server.h"
#include "Core/Engine/game_engine.h"
#ifdef HIKARI_CLIENT
#include "Core/Managers/window_manager.h"
#include "GUI/game_hud.h"
#endif

namespace Hikari
{
	IMPLEMENT_CLASS(Hikari::GameServerNetworkController)

	REGISTER_CLASSPROPERTIES(Hikari::GameServerNetworkController)

	GameServerNetworkController::GameServerNetworkController()
		:NetworkController()
	{

	}

	void GameServerNetworkController::ServerSendMessage(std::string arg_message)
	{
		LOG_INFO() << "Called ServerSendMessage: " << arg_message;

#ifdef HIKARI_GAMESERVER
		auto clientList = GameEngine::Instance()->GetGameServer()->GetConnectedClients();
		for (auto client : clientList)
		{
			ClientCall(client.second.mClientID, this, ClientSendMessage, arg_message);
		}
#endif
	}

	void GameServerNetworkController::ClientSendMessage(std::string arg_message)
	{
		LOG_INFO() << "Called ClientSendMessage: " << arg_message;
#ifdef HIKARI_CLIENT
		GameHUD* hud = (GameHUD*)GameEngine::Instance()->GetWindowManager()->GetWindow(GameHUD::GetStaticClass());
		hud->AddChatMessage(arg_message.c_str());
#endif
	}
}
