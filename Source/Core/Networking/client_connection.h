#pragma once

#include "tcp_connection.h"
#include <functional>

namespace Hikari
{
	class ClientConnection : public TcpConnection
	{
	private:
		TCPsocket mClients[9000];
		bool mClientIsFree[9000];
		int mMaxClients;
		char textBuffer[BUFFER_SIZE]; // buffer used when receiving data

		// Callbacks:
		std::function<void(int, const char*, int)> mMessageCallback;
		std::function<void(int)> mClientConnectedCallback;
		std::function<void(int)> mClientDisconnectedCallback;

		inline TCPsocket getServerSocket() { return mClients[0]; }

	public:
		ClientConnection(int max_clients);
		~ClientConnection();

		bool Connect(int port);
		void SendNetworkMessage(int socket_index, const NetMessage* message);
		void SendNetworkMessageToAll(const NetMessage* message);

		std::string GetSocketIPAddress(int socket_index);

		// Virtual functions:
		virtual void FetchNewMessages() override;


		// Callback modifiers
		template<typename Functor>
		inline void SetMessageCallback(Functor arg_func)
		{
			mMessageCallback = arg_func;
		}

		template<typename Functor>
		inline void SetClientConnectedCallback(Functor arg_func)
		{
			mClientConnectedCallback = arg_func;
		}

		template<typename Functor>
		inline void SetClientDisconnectedCallback(Functor arg_func)
		{
			mClientDisconnectedCallback = arg_func;
		}

	};
}
