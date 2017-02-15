#ifndef NETMESSAGETYPE_H
#define NETMESSAGETYPE_H

namespace Hikari
{
	enum NetMessageType
	{
		Ignored = 0x0000,
		ObjectReplication = 0x0001,
		LuaCall = 0x0002
	};
}

#endif // #ifndef NETMESSAGETYPE_H
