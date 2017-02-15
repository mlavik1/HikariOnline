#pragma once

#include "tcp_connection.h"
#include <functional>

namespace Hikari
{
	class ClientConnection : public TcpConnection
	{
	private:
		TCPsocket mServerSocket;

		std::function<void(const char*, int)> mMessageCallback;
		//void(*mMessageCallback)(const char*);
		void(*mServerDisconnectedCallback)() = 0;

	public:
		ClientConnection();
		~ClientConnection();
		virtual void FetchNewMessages() override;
		void SendMessage(const char *arg_message);
		void SendMessage(const char *arg_message, int arg_length);
		bool Connect(const char *arg_host, int port);



		// Callback modifiers
		template<typename Functor>
		inline void SetMessageCallback(Functor arg_func)
		{
			mMessageCallback = arg_func;
		}

		inline void SetServerDisconnectedCallback(void(*arg_func)())
		{
			mServerDisconnectedCallback = arg_func;
		}
	};
}
