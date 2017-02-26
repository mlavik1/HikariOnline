#ifndef HIKARI_CLIENTCONTROLLER_H
#define HIKARI_CLIENTCONTROLLER_H

namespace Hikari
{
	class Client;

	class ClientController
	{
	protected:
		Client* mClient;

	public:
		ClientController(Client* arg_client);
		virtual void Tick(float arg_deltatime);
	};
}

#endif
