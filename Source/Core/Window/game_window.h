#ifndef HIKARI_GAMEWINDOW_H
#define HIKARI_GAMEWINDOW_H

#include "OGRE/Ogre.h"

#ifdef _WIN32
#include <Windows.h>
#endif
#include "MYGUI/MyGUI.h"
#include "MyGUI/MyGUI_OgrePlatform.h"

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
		MyGUI::Gui* mMyGUI;

		/**
		* Main camera of the client.
		*/
		Ogre::Camera* mMainCamera;
		/**
		* Main viewport of the client.
		*/
		Ogre::Viewport* mMainViewport;

	public:
		GameWindow(GameInstance* arg_gameinstance);

		MyGUI::Gui* GetMyGUI();
		Ogre::Camera* GetMainCamera();
		Ogre::Viewport* GetMainViewport();
		Ogre::RenderWindow* GetRenderWindow();

		int GetWidth() const;
		int GetHeight() const;

		void SetTitle(const char* arg_title);
		void Resize(int arg_width, int arg_height);
	};
}

#endif
