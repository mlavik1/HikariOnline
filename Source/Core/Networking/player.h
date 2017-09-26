#ifndef HIKARI_PLAYER_H
#define HIKARI_PLAYER_H

#include "Core/Object/object.h"

namespace Hikari
{
	struct ClientConnectionData
	{
	public:
		std::string mIPAddress;
		int mClientID;
		std::string mAccountName;
	};

	class Player
	{
	public:
		NetGUID mNetGUID;
		ClientConnectionData mConnectionData;
	};
}

#endif
