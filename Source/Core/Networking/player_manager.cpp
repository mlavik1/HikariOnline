#include "player_manager.h"

namespace Hikari
{
	PlayerManager::PlayerManager()
	{

	}

	bool PlayerManager::AddPlayer(const NetGUID& arg_guid, const ClientConnectionData& arg_conndata)
	{
		auto foundEntry = mPlayers.find(arg_guid);
		if (foundEntry != mPlayers.end())
			return false;

		Player* player = new Player();
		player->mNetGUID = arg_guid;
		player->mConnectionData = arg_conndata;
		mPlayers[arg_guid] = player;

		return true;
	}

	Player* PlayerManager::GetPlayer(const NetGUID& arg_guid)
	{
		auto foundEntry = mPlayers.find(arg_guid);
		if (foundEntry != mPlayers.end())
		{
			return foundEntry->second;
		}
		
		return nullptr;
	}
}
