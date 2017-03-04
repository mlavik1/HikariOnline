#include "game_window.h"

#include "Core/Engine/game_engine.h"
#include "Core/Debug/st_assert.h"
#include "Core/Engine/game_instance.h"
#include "Core/World/world.h"

namespace Hikari
{
	GameWindow::GameWindow(GameInstance* arg_gameinstance)
	{
		mRenderWindow = GameEngine::Instance()->GetOgreRoot()->initialise(true, "Hikari");
		//mRenderWindow->setFullscreen(false, 1024, 768);
		
#ifdef _WIN32
		mRenderWindow->getCustomAttribute("WINDOW", &mHWND);
		__Assert(IsWindow(mHWND));
#endif

		mMainCamera = arg_gameinstance->GetWorld()->GetSceneManager()->createCamera("DefaultCamera");
		mMainCamera->setNearClipDistance(0.01);
		Ogre::Viewport* viewport = GetRenderWindow()->addViewport(mMainCamera);
		viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 1.0f));
		
		MyGUI::OgrePlatform* mPlatform;
		mPlatform = new MyGUI::OgrePlatform();
		mPlatform->initialise(mRenderWindow, arg_gameinstance->GetWorld()->GetSceneManager());
		mMyGUI = new MyGUI::Gui();
		mMyGUI->initialise();
	}

	void GameWindow::SetTitle(const char* arg_title)
	{
#ifdef _WIN32
		SetWindowText(mHWND, arg_title);
#else
		LOG_WARNING() << "Unhandled OS is GameWindow::SetTitle";
#endif
	}

	MyGUI::Gui* GameWindow::GetMyGUI()
	{
		return mMyGUI;
	}

	Ogre::Camera* GameWindow::GetMainCamera()
	{
		return mMainCamera;
	}

	Ogre::Viewport* GameWindow::GetMainViewport()
	{
		return mMainViewport;
	}

	Ogre::RenderWindow* GameWindow::GetRenderWindow()
	{
		return mRenderWindow;
	}

	int GameWindow::GetWidth() const
	{
		return mRenderWindow->getWidth();
	}

	int GameWindow::GetHeight() const
	{
		return mRenderWindow->getHeight();
	}

	void GameWindow::Resize(int arg_width, int arg_height)
	{
		// TODO: notify listeners (GUI, inputmanager(mouse), ...)
		mRenderWindow->resize(arg_width, arg_height);
	}
}
