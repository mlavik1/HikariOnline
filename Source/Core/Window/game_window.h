#ifndef HIKARI_GAMEWINDOW_H
#define HIKARI_GAMEWINDOW_H

#include "OGRE/Ogre.h"

#ifdef _WIN32
#include <Windows.h>
#endif

namespace Hikari
{
	class GameEngine;

	class GameWindow
	{
	private:
		Ogre::RenderWindow* mRenderWindow;
#ifdef _WIN32
		HWND mHWND;
#endif

	public:
		GameWindow(GameEngine* arg_engine);

		void SetTitle(const char* arg_title);
	};
}

#endif
