#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <string>
#include "networking_helper.h"

#define BUFFER_SIZE 4000

#define PORT_GAMESERVER_WORLDSERVER 2110
#define PORT_GAMESERVER_CLIENT 2120
#define PORT_WORLDSERVER_CLIENT 2130

namespace Hikari
{
	class TcpConnection
	{
	protected:
		SDLNet_SocketSet mSocketSet;
		std::string mHost;
		bool mConnected;

		void sendMessage(TCPsocket &socket, const char *arg_message);
		void sendMessage(TCPsocket &socket, const char *arg_message, int arg_length);
		void setHost(const char *arg_host);
		bool getHostIPAddress(IPaddress &out, int port);

		void SetConnected(bool arg_connected);


	public:
		TcpConnection();
		~TcpConnection();

		bool IsConnected();

		std::string GetHost();
		void Close();

		virtual void FetchNewMessages() = 0;

	};
}
