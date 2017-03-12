#include "client.h"
#include "Core/Debug/st_assert.h"
#include "Core/Controller/client_controller.h"
#include "Core/Controller/ingame_controller.h"

namespace Hikari
{
	Client::Client(GameInstance* arg_gameinstance)
	{
		__Assert(arg_gameinstance != nullptr);
		mGameInstance = arg_gameinstance;

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

		NetMessage* connMessage = new NetMessage(NetMessageType::EstablishConnection, mAccountName.c_str());
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
		if (mWorldServerConnection != nullptr)
		{
			mWorldServerConnection->Close();
			delete(mWorldServerConnection);
		}
		mWorldServerConnection = new ServerConnection();

		mWorldServerConnection->Connect(arg_ip, PORT_WORLDSERVER_CLIENT);

		NetMessage* connMessage = new NetMessage(NetMessageType::EstablishConnection, mAccountName.c_str());
		mOutgoingWorldServerMessages.push_back(connMessage);

		mGameServerConnection->SetMessageCallback([&](const char* arg_message, int arg_bytes) -> void
		{
			LOG_INFO() << "Received message from world server";
			NetMessage* incomingMessage = new NetMessage(arg_message);
			mIncomingGameServerMessages.push_back(incomingMessage);
		});
	}

	void Client::SendOutgoingNetworkMessages()
	{
		if (mGameServerConnection != nullptr && mGameServerConnection->IsConnected())
		{
			for (NetMessage* message : mOutgoingGameServerMessages)
			{
				mGameServerConnection->SendNetworkMessage(message->GetStringRepresentation().c_str(), message->GetTotalLength());
			}
		}

		if (mWorldServerConnection != nullptr && mWorldServerConnection->IsConnected())
		{
			for (NetMessage* message : mOutgoingWorldServerMessages)
			{
				mWorldServerConnection->SendNetworkMessage(message->GetStringRepresentation().c_str(), message->GetTotalLength());
			}
		}

		mOutgoingGameServerMessages.clear();
		mOutgoingWorldServerMessages.clear();
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

				}
			}
		}

		if (mWorldServerConnection != nullptr && mWorldServerConnection->IsConnected())
		{
			for (NetMessage* message : mIncomingWorldServerMessages)
			{
				const NetMessageType& messageType = message->GetMessageType();
				switch (messageType)
				{

				}
			}
		}
	}

	InGameController* Client::GetInGameController()
	{
		return mInGameController;
	}

	GameInstance* Client::GetGameInstance()
	{
		return mGameInstance;
	}
}
