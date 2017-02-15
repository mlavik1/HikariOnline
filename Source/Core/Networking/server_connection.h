#pragma once

#include "tcp_connection.h"
#include <functional>

namespace Hikari
{
	class ServerConnection : public TcpConnection
	{
	private:
		TCPsocket mClients[100];
		bool mClientIsFree[100];
		int mMaxClients;

		// Callbacks:
		std::function<void(int, const char*, int)> mMessageCallback;
		std::function<void(int)> mClientConnectedCallback;
		std::function<void(int)> mClientDisconnectedCallback;

		inline TCPsocket getServerSocket() { return mClients[0]; }

	public:
		ServerConnection(int max_clients);
		~ServerConnection();

		bool Connect(int port);
		void SendMessage(int socket_index, const char *message);
		void SendMessage(int socket_index, const char *message, int arg_length);
		void SendMessageToAll(const char *message);
		void SendMessageToAll(const char *message, int arg_length);

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
