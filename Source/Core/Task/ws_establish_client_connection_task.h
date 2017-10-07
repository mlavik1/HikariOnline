#ifndef HIKARI_WSESTABLISHCLIENTCONNECTIONTASK_H
#define HIKARI_WSESTABLISHCLIENTCONNECTIONTASK_H

#include "task.h"
#include "Core/Networking/player.h"
#include "Core/Networking/net_message_data.h"

namespace Hikari
{
	class WSEstablishClientConnectionTask : public Task
	{
	private:
		enum ConnectionStage
		{
			HandleRequest = 0,
			RequestClientIntoFromGS = 1,
			Completed = 2
		};

		int mConnectionStage = 0;
		ClientConnectionData mClientConnectionData;
		bool mHasReceivedClientInfo = false;
		NetMessageData::ClientInfo mClientInfo;
		
	public:
		WSEstablishClientConnectionTask(const ClientConnectionData& arg_conndata);
		virtual bool Execute() override;

		void OnReceivedClientInfoFromGS(const NetMessageData::ClientInfo& arg_info);
	};
}

#endif
