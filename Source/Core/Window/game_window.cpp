#include "game_window.h"

#include "Core/Engine/game_engine.h"
#include "Core/Debug/st_assert.h"

namespace Hikari
{
	GameWindow::GameWindow()
	{
		mRenderWindow = GameEngine::Instance()->GetOgreRoot()->initialise(true, "Hikari");
		mRenderWindow->setFullscreen(false, 800, 600);

#ifdef _WIN32
		mRenderWindow->getCustomAttribute("WINDOW", &mHWND);
		__Assert(IsWindow(mHWND));
#endif
	}

	void GameWindow::SetTitle(const char* arg_title)
	{
#ifdef _WIN32
		SetWindowText(mHWND, arg_title);
#else
		LOG_WARNING() << "Unhandled OS is GameWindow::SetTitle";
#endif
	}
}
