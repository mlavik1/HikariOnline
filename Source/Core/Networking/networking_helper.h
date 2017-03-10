#ifndef HIKARI_NETWORKINGHELPER_H
#define HIKARI_NETWORKINGHELPER_H

#include <sdl2/SDL_net.h>
#include <iostream>

namespace Hikari
{
	static std::string IPToString(IPaddress *ip) {
		char *tmp = new char[4000];
		Uint8 *arr = (Uint8*)&ip->host;
		sprintf_s(tmp, 4000, "%i.%i.%i.%i", arr[0], arr[1], arr[2], arr[3]);
		std::string str(tmp);
		delete[] tmp;
		return str;
	}

	static std::string GetLocalhostIP()
	{
		IPaddress ip;
		ip.host = 0;
		ip.port = 1234;
		const char* host = SDLNet_ResolveIP(&ip);
		SDLNet_ResolveHost(&ip, host, 2999);
		return IPToString(&ip);
	}
}

#endif
