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
		ConnectionRejected,
		WorldServerListUpdate,
		ClientInitGameServerConnection,
		ClientInitWorldServerConnection,
		WorldServerInitGameServerConnection,
		WSRequestClientInfoFromGS,
		GSSendClientInfoTOWS
	};
}

#endif // #ifndef NETMESSAGETYPE_H
