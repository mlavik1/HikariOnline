#include "base_window.h"
#include "Core/Engine/game_instance.h"
#include "Core/Window/game_window.h"

IMPLEMENT_CLASS(Hikari::BaseWindow)

namespace Hikari
{
	void BaseWindow::SetGameInstance(GameInstance* arg_gameinstance)
	{
		mGameInstance = arg_gameinstance;
	}

	void BaseWindow::ShowWindow()
	{
		if (mRootWidget == nullptr)
		{
			const int& win_width = mGameInstance->GetGameWindow()->GetWidth();
			const int& win_height = mGameInstance->GetGameWindow()->GetHeight();
			mRootWidget = mGameInstance->GetGameWindow()->GetMyGUI()->createWidget<MyGUI::Window>("", 0, 0, win_width, win_height, MyGUI::Align::Default, "Main");
		}
	}

	void BaseWindow::CloseWindow()
	{
		mGameInstance->GetGameWindow()->GetMyGUI()->destroyWidget(mRootWidget);
	}

	void BaseWindow::LoadLayout(const char* arg_layout)
	{
		MyGUI::VectorWidgetPtr roots = MyGUI::LayoutManager::getInstance().loadLayout(arg_layout, "", mRootWidget);
	}
}
