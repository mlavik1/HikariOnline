#include "client.h"
#include "Core/Debug/st_assert.h"
#include "Core/Controller/client_controller.h"
#include "Core/Controller/ingame_controller.h"
#include "Core/Networking/net_message_data.h"
#include "game_instance.h"
#include "Core/Managers/network_manager.h"
#include "Core/Networking/rpc.h"
#include "Core/Networking/rpc.h"

namespace Hikari
{
	Client::Client(GameInstance* arg_gameinstance)
	{
		__Assert(arg_gameinstance != nullptr);
		mGameInstance = arg_gameinstance;
		mGameServerNetworkController = nullptr;
		mClientNetworkController = nullptr;

		// TEMP!  this should happen hafter joining game
		mInGameController = new InGameController(this);
		mClientController = mInGameController;

		mGameServerConnection = nullptr;
		mWorldServerConnection = nullptr;

		mAccountName = "mlavik1"; // TEMP
	}

	Client::~Client()
	{
		if (mGameServerConnection != nullptr)
		{
			mGameServerConnection->Close();
			delete(mGameServerConnection);
		}
		if (mWorldServerConnection != nullptr)
		{
			mWorldServerConnection->Close();
			delete(mWorldServerConnection);
		}

	}

	void Client::TickClient(float arg_deltatime)
	{
#ifdef HIKARI_CLIENT
		if (mClientController != nullptr)
		{
			mClientController->Tick(arg_deltatime);
		}

		FetchIncomingNetworkMessages(); // TEMP - call from somewhere else
		HandleIncomingNetworkMessages(); // TEMP - call from somewhere else
		SendOutgoingNetworkMessages(); // TEMP - call from somewhere else
#endif
	}

	void Client::ConnectToGameServer(const char* arg_ip)
	{
		if (mGameServerConnection != nullptr)
		{
			mGameServerConnection->Close();
			delete(mGameServerConnection);
		}
		mGameServerConnection = new ServerConnection();

		mGameServerConnection->Connect(arg_ip, PORT_GAMESERVER_CLIENT);

		NetMessage* connMessage = new NetMessage(NetMessageType::EstablishConnection, mAccountName);
		mOutgoingGameServerMessages.push_back(connMessage);

		mGameServerConnection->SetMessageCallback([&](const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from game server";
			NetMessage* incomingMessage = new NetMessage(arg_message);
			mIncomingGameServerMessages.push_back(incomingMessage);
		});
	}

	void Client::ConnectToWorldServer(const char* arg_ip)
	{
		LOG_INFO() << "Connecting to WorldServer: " << arg_ip;
		if (mWorldServerConnection != nullptr)
		{
			mWorldServerConnection->Close();
			delete(mWorldServerConnection);
		}
		mWorldServerConnection = new ServerConnection();
		mWorldServerConnection->Connect(arg_ip, PORT_WORLDSERVER_CLIENT);

		mWorldServerConnection->SetMessageCallback([&](const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from world server";
			NetMessage* incomingMessage = new NetMessage(arg_message);
			mIncomingWorldServerMessages.push_back(incomingMessage);
		});

		NetMessage* connMessage = new NetMessage(NetMessageType::EstablishConnection, mAccountName.c_str());
		mOutgoingWorldServerMessages.push_back(connMessage);
	}

	void Client::SendOutgoingNetworkMessages()
	{
		if (mGameServerConnection != nullptr && mGameServerConnection->IsConnected())
		{
			for (NetMessage* message : mOutgoingGameServerMessages)
			{
				mGameServerConnection->SendNetworkMessage(message);
				delete(message);
			}
			mOutgoingGameServerMessages.clear();
		}

		if (mWorldServerConnection != nullptr && mWorldServerConnection->IsConnected())
		{
			for (NetMessage* message : mOutgoingWorldServerMessages)
			{
				mWorldServerConnection->SendNetworkMessage(message);
				delete(message);
			}
			mOutgoingWorldServerMessages.clear();
		}	
		
	}

	void Client::FetchIncomingNetworkMessages()
	{
		if (mGameServerConnection != nullptr && mGameServerConnection->IsConnected())
		{
			mGameServerConnection->FetchNewMessages();
		}

		if (mWorldServerConnection != nullptr && mWorldServerConnection->IsConnected())
		{
			mWorldServerConnection->FetchNewMessages();
		}
	}

	void Client::HandleIncomingNetworkMessages()
	{
		if (mGameServerConnection != nullptr && mGameServerConnection->IsConnected())
		{
			for (NetMessage* message : mIncomingGameServerMessages)
			{
				const NetMessageType& messageType = message->GetMessageType();
				switch (messageType)
				{
					case NetMessageType::WorldServerListUpdate:
					{
						NetMessageData::WorldServerList serverList = *reinterpret_cast<const NetMessageData::WorldServerList*>(message->GetMessageData());
						if (serverList.NumServers > 0)
						{
							ConnectToWorldServer(serverList.ServerInfos[0].IPAddress);
						}
						break;
					}
					case NetMessageType::ClientInitGameServerConnection:
					{
						NetMessageData::ClientGameServerConnectionData initGSNetMgr = *reinterpret_cast<const NetMessageData::ClientGameServerConnectionData*>(message->GetMessageData());
						LOG_INFO() << "Creating GameServerNetworkController, with GUID: " << (int)initGSNetMgr.GameServerNetworkControllerNetGUID;
						mGameServerNetworkController = new GameServerNetworkController(mGameInstance);
						mGameServerNetworkController->SetNetGUID(initGSNetMgr.GameServerNetworkControllerNetGUID);
						mGameInstance->GetNetworkManager()->RegisterObject(mGameServerNetworkController);
						LOG_INFO() << "Creating ClientNetworkController, with GUID: " << (int)initGSNetMgr.ClientNetworkControllerNetGUID;
						mClientNetworkController = new ClientNetworkController(mGameInstance);
						mClientNetworkController->SetNetGUID(initGSNetMgr.ClientNetworkControllerNetGUID);
						mGameInstance->GetNetworkManager()->RegisterObject(mClientNetworkController);
						break;
					}
					case NetMessageType::RPC:
					{
						RPCCaller::HandleIncomingRPC(message, mGameInstance);
						break;
					}
				}
				delete(message);
			}
			mIncomingGameServerMessages.clear();
		}

		if (mWorldServerConnection != nullptr && mWorldServerConnection->IsConnected())
		{
			for (NetMessage* message : mIncomingWorldServerMessages)
			{
				const NetMessageType& messageType = message->GetMessageType();
				switch (messageType)
				{
				
				}
				delete(message);
			}
			mIncomingWorldServerMessages.clear();
		}
	}

	void Client::SendMessageToGameServer(NetMessage* arg_message)
	{
		mOutgoingGameServerMessages.push_back(arg_message);
	}

	void Client::SendMessageToWorldServer(NetMessage* arg_message)
	{
		mOutgoingWorldServerMessages.push_back(arg_message);
	}


	InGameController* Client::GetInGameController()
	{
		return mInGameController;
	}

	GameInstance* Client::GetGameInstance()
	{
		return mGameInstance;
	}

	GameServerNetworkController* Client::GetGameServerNetworkController()
	{
		return mGameServerNetworkController;
	}

	ClientNetworkController* Client::GetClientNetworkController()
	{
		return mClientNetworkController;
	}
}
