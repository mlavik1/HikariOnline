#ifndef HIKARI_NETWORKCONTROLLER_H
#define HIKARI_NETWORKCONTROLLER_H

#include "Core/Object/game_object.h"

namespace Hikari
{
	class NetworkController : public Hikari::GameObject
	{
		DEFINE_CLASS(Hikari::NetworkController, Hikari::GameObject)

	public:
		NetworkController();
	};
}

#endif
