#include "game_window.h"

#include "Core/Engine/game_engine.h"
#include "Core/Debug/st_assert.h"

namespace Hikari
{
	GameWindow::GameWindow(GameEngine* arg_engine)
	{
		mRenderWindow = arg_engine->GetOgreRoot()->initialise(true, "Hikari");
		mRenderWindow->setFullscreen(false, 600, 400);

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
