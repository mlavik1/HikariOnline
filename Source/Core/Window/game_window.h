#ifndef HIKARI_GAMEWINDOW_H
#define HIKARI_GAMEWINDOW_H

#include "OGRE/Ogre.h"

#ifdef _WIN32
#include <Windows.h>
#endif

namespace Hikari
{
	class GameInstance;

	class GameWindow
	{
	private:
		Ogre::RenderWindow* mRenderWindow;
#ifdef _WIN32
		HWND mHWND;
#endif

	public:
		GameWindow();

		void SetTitle(const char* arg_title);

		inline Ogre::RenderWindow* GetRenderWindow()
		{
			return mRenderWindow;
		}
	};
}

#endif
