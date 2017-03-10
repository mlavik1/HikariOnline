#include "server_connection.h"

namespace Hikari
{
	ServerConnection::ServerConnection()
	{
		mSocketSet = SDLNet_AllocSocketSet(1);
	}

	ServerConnection::~ServerConnection()
	{
		SDLNet_TCP_Close(mServerSocket);
	}

	void ServerConnection::FetchNewMessages()
	{
		if (SDLNet_CheckSockets(mSocketSet, 0) > 0 && SDLNet_SocketReady(mServerSocket))
		{
			char text[BUFFER_SIZE];
			int bytesReceived = SDLNet_TCP_Recv(mServerSocket, text, BUFFER_SIZE);
			if (bytesReceived > 0)
			{
				if (mMessageCallback)
					mMessageCallback(text, bytesReceived);
			}
			else
			{
				if (mServerDisconnectedCallback)
					mServerDisconnectedCallback();
			}
		}
	}

	void ServerConnection::SendNetworkMessage(const char * arg_message)
	{
		TcpConnection::sendMessage(mServerSocket, arg_message);
	}

	void ServerConnection::SendNetworkMessage(const char * arg_message, int arg_length)
	{
		TcpConnection::sendMessage(mServerSocket, arg_message, arg_length);
	}

	bool ServerConnection::Connect(const char *arg_host, int port)
	{
		setHost(arg_host);

		IPaddress ip;
		if (!getHostIPAddress(ip, port))
			return false;

		mServerSocket = SDLNet_TCP_Open(&ip);

		if (!mServerSocket)
		{
			return false;
		}

		// Add server socket to socket set
		SDLNet_TCP_AddSocket(mSocketSet, mServerSocket);

		SetConnected(true);

		return true;
	}

}
