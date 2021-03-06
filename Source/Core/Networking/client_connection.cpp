#include "client_connection.h"
#include <assert.h>
#include <iostream>
#include "net_message.h"
#include "Core/Debug/st_assert.h"

namespace Hikari
{
	ClientConnection::ClientConnection(int max_clients)
	{
		mMaxClients = max_clients;
		mClientIsFree[0] = false; // server

		for (int i = 1; i < max_clients; i++)
		{
			mClients[i] = 0;
			mClientIsFree[i] = true;
			mFreeClients.insert(i);
		}

		mSocketSet = SDLNet_AllocSocketSet(max_clients);
	}

	ClientConnection::~ClientConnection()
	{
		SDLNet_TCP_Close(mClients[0]);
	}

	void ClientConnection::FetchNewMessages()
	{
		TCPsocket new_tcpsock;

		new_tcpsock = SDLNet_TCP_Accept(getServerSocket());
		if (new_tcpsock)
		{
			if (!new_tcpsock) {
				std::cout << "server_connection.cpp: error on accepting incoming client connection: " << SDLNet_GetError() << std::endl;
			}
			else {
				IPaddress *ip = SDLNet_TCP_GetPeerAddress(new_tcpsock);

				int iFreeClient = *mFreeClients.begin();

				mClients[iFreeClient] = new_tcpsock;
				mClientIsFree[iFreeClient] = false;
				mFreeClients.erase(iFreeClient);

				SDLNet_TCP_AddSocket(mSocketSet, new_tcpsock);

				if (mClientConnectedCallback)
					mClientConnectedCallback(iFreeClient);
			}
		}


	FetchMessages:
		for (int i = 1; i < mMaxClients; i++)
		{
			if (SDLNet_CheckSockets(mSocketSet, 0) > 0 && SDLNet_SocketReady(mClients[i]))
			{
				char* text = textBuffer;
				int bytesReceived = SDLNet_TCP_Recv(mClients[i], text, BUFFER_SIZE);
				if (bytesReceived > 0)
				{
					NetMessage netMsg;
					int bytesLeft = bytesReceived;
					while (bytesLeft > 0)
					{
						netMsg.SetMessageHeader(text);
						const int& msgLen = netMsg.GetTotalLength();
						bytesLeft -= msgLen;
						__Assert(bytesLeft >= 0);
						if (mMessageCallback)
							mMessageCallback(i, text, bytesReceived);
						text += msgLen;
					}
				}
				else
				{
					SDLNet_TCP_Close(mClients[i]);
					mClientIsFree[i] = true;
					mFreeClients.insert(i);
					if (mClientDisconnectedCallback)
						mClientDisconnectedCallback(i);
				}
			}
		}
	}

	bool ClientConnection::Connect(int port)
	{
		setHost("");

		IPaddress ip;
		if (!getHostIPAddress(ip, port))
			return false;


		// Client #0 = server
		mClients[0] = SDLNet_TCP_Open(&ip);
		mClientIsFree[0] = false;

		if (!mClients[0])
		{
			std::cout << "failed to connect to server" << std::endl;
			return false;
		}

		// Add server socket to socket set
		SDLNet_TCP_AddSocket(mSocketSet, mClients[0]);

		SetConnected(true);

		return true;
	}

	void ClientConnection::SendNetworkMessage(int socket_index, const NetMessage* message)
	{
		TcpConnection::sendMessage(mClients[socket_index], message);
	}

	void ClientConnection::SendNetworkMessageToAll(const NetMessage* message)
	{
		for (int i = 1; i < mMaxClients; i++) // TODO!!!
		{
			if (!mClientIsFree[i])
				sendMessage(mClients[i], message);
		}
	}

	std::string ClientConnection::GetSocketIPAddress(int socket_index)
	{
		IPaddress *ip = SDLNet_TCP_GetPeerAddress(mClients[socket_index]);
		std::string strIP = IPToString(ip);
		if (strIP == "127.0.0.1")
			strIP = GetLocalhostIP();
		return strIP;
	}
}
