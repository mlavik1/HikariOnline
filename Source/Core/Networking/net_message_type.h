#ifndef NETMESSAGETYPE_H
#define NETMESSAGETYPE_H

namespace Hikari
{
	enum NetMessageType
	{
		Ignored,
		RPC,
		ObjectReplication,
		EstablishConnection,
		ConnectionEstablishedAck,
		WorldServerListUpdate,
		ClientInitGameServerConnection,
		ClientInitWorldServerConnection,
		WorldServerInitGameServerConnection
	};
}

#endif // #ifndef NETMESSAGETYPE_H
