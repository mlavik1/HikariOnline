#include "server_connection.h"
#include "net_message.h"
#include "Core/Debug/st_assert.h"

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
		while (SDLNet_CheckSockets(mSocketSet, 0) > 0 && SDLNet_SocketReady(mServerSocket))
		{
			char* text = textBuffer;
			int bytesReceived = SDLNet_TCP_Recv(mServerSocket, text, BUFFER_SIZE);
			if (bytesReceived > 0)
			{
				int bytesLeft = bytesReceived;
				NetMessage netMsg;
				while (bytesLeft > 0)
				{
					netMsg.SetMessageHeader(text);
					const size_t& msgLength = netMsg.GetTotalLength();
					bytesLeft -= msgLength;
					__Assert(bytesReceived >= 0);
					if (mMessageCallback)
						mMessageCallback(text, bytesReceived);
					text += msgLength;
				}
			}
			else
			{
				if (mServerDisconnectedCallback)
					mServerDisconnectedCallback();
			}
		}
	}

	void ServerConnection::SendNetworkMessage(const NetMessage* arg_message)
	{
		TcpConnection::sendMessage(mServerSocket, arg_message);
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
