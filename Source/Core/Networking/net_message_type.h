#ifndef NETMESSAGETYPE_H
#define NETMESSAGETYPE_H

namespace Hikari
{
	enum NetMessageType
	{
		Ignored = 0x0000,
		RPC = 0x0001,
		ObjectReplication = 0x0002,
		EstablishConnection = 0x0004,
		ConnectionEstablishedAck = 0x0008
	};
}

#endif // #ifndef NETMESSAGETYPE_H
