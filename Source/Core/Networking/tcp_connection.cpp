#include "tcp_connection.h"
#include "net_message.h"

namespace Hikari
{

	TcpConnection::TcpConnection()
	{
		mConnected = false;
	}

	TcpConnection::~TcpConnection()
	{
		SDLNet_FreeSocketSet(mSocketSet);

	}

	void TcpConnection::setHost(const char *arg_host)
	{
		mHost = arg_host;
	}

	std::string TcpConnection::GetHost()
	{
		return mHost;
	}

	void TcpConnection::Close()
	{
		SDLNet_FreeSocketSet(mSocketSet);
	}

	bool TcpConnection::getHostIPAddress(IPaddress &out, int port)
	{
		const char *host = NULL;
		if (mHost != "")
			host = mHost.c_str();

		if (SDLNet_ResolveHost(&out, host, port))
		{
			return false;
		}
		else
			return true;
	}

	void TcpConnection::SetConnected(bool arg_connected)
	{
		mConnected = arg_connected;
	}


	void TcpConnection::sendMessage(TCPsocket &socket, const NetMessage* arg_message)
	{
		int bytesSent = SDLNet_TCP_Send(socket, arg_message->GetStringRepresentation().c_str(), arg_message->GetTotalLength());
	}

	bool TcpConnection::IsConnected()
	{
		return mConnected;
	}
}
