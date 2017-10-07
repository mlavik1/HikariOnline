#ifdef HIKARI_WORLDSERVER
#include "ws_establish_client_connection_task.h"

#include "Core/Engine/world_server.h"
#include "Core/Engine/game_engine.h"
#include "Core/Managers/network_manager.h"
#include "Core/Actor/player_character.h"
#include "Core/Controller/client_network_controller.h"

namespace Hikari
{
	WSEstablishClientConnectionTask::WSEstablishClientConnectionTask(const ClientConnectionData& arg_conndata)
	{
		mClientConnectionData = arg_conndata;
	}

	bool WSEstablishClientConnectionTask::Execute()
	{
		Task::Execute();

		switch (mConnectionStage)
		{
			case ConnectionStage::HandleRequest:
			{
				WorldServer* worldServer = GameEngine::Instance()->GetWorldServer();

				// Request client info from GameServer
				NetMessageData::ClientInfo clientInfo(mClientConnectionData.mIPAddress.c_str(), mClientConnectionData.mAccountName.c_str());
				NetMessage* msgRequestClientInfo = new NetMessage(NetMessageType::WSRequestClientInfoFromGS, sizeof(NetMessageData::ClientInfo), reinterpret_cast<char*>(&clientInfo));
				worldServer->SendMessageToGameServer(msgRequestClientInfo);
	
				mConnectionStage++;
				break;
			}
			case ConnectionStage::RequestClientIntoFromGS:
			{
				if (mHasReceivedClientInfo)
				{
					WorldServer* worldServer = GameEngine::Instance()->GetWorldServer();

					if (mClientInfo.mNetGUID != NetGUIDNone)
					{
						worldServer->RegisterClient(mClientConnectionData, mClientInfo.mNetGUID);

						// Tell client to initialise WorldServerNetworkController, and set its GUID
						NetMessageData::ClientWorldServerConnectionData initGSNetController;
						initGSNetController.WorldServerNetworkControllerNetGUID = worldServer->GetWorldServerNetworkController()->GetNetGUID();
						initGSNetController.ClientNetworkControllerNetGUID = mClientInfo.mNetGUID;
						NetMessage *initGSNetControllerMsg = new NetMessage(NetMessageType::ClientInitWorldServerConnection, sizeof(NetMessageData::ClientGameServerConnectionData), reinterpret_cast<char*>(&initGSNetController));
						worldServer->SendMessageToClient(mClientConnectionData.mClientID, initGSNetControllerMsg);

						// Send ack
						NetMessage* msgAck = new NetMessage(NetMessageType::ConnectionEstablishedAck, "");
						worldServer->SendMessageToClient(mClientConnectionData.mClientID, msgAck);

						// Create PlayerCharacter on server and clients
						PlayerCharacter* playerChar = (PlayerCharacter*)worldServer->GetWorldServerNetworkController()->ServerCreateNetworkedObjectByClass(PlayerCharacter::GetStaticClass());
						if (playerChar != nullptr)
						{
							GameEngine::Instance()->GetNetworkManager()->RegisterObject(playerChar);

							GameEngine::Instance()->GetNetworkManager()->GenerateNetGUID((Object*)playerChar->GetMovementComponent());
							GameEngine::Instance()->GetNetworkManager()->RegisterObject((Object*)playerChar->GetMovementComponent());
							playerChar->SetPosition(Ogre::Vector3(130.0f, 2.0f, 130.0f));
							playerChar->SetOwningClientGUID(worldServer->GetClientNetworkController(mClientConnectionData.mClientID)->GetNetGUID());
							playerChar->ReplicateInitialData();
						}
					}
					else
					{
						// Connection request rejected
						NetMessage* msg = new NetMessage(NetMessageType::ConnectionRejected, "Rejected by GameServer");
						worldServer->SendMessageToClient(mClientConnectionData.mClientID, msg);

					}

					mConnectionStage++;
				}
				break;
			}
		}

		return mConnectionStage == ConnectionStage::Completed;
	}

	void WSEstablishClientConnectionTask::OnReceivedClientInfoFromGS(const NetMessageData::ClientInfo& arg_info)
	{
		mHasReceivedClientInfo = true;
		mClientInfo = arg_info;
	}
}

#endif // HIKARI_WORLDSERVER
