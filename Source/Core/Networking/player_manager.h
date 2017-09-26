#ifndef HIKARI_PLAYERMANAGER_H
#define HIKARI_PLAYERMANAGER_H

#include <unordered_map>
#include "Core/Networking/player.h"

namespace Hikari
{
	class PlayerManager
	{
	private:
		std::unordered_map<NetGUID, Player*> mPlayers;

	public:
		PlayerManager();
		
		bool AddPlayer(const NetGUID& arg_guid, const ClientConnectionData& arg_conndata);
		Player* GetPlayer(const NetGUID& arg_guid);
	};
}

#endif
