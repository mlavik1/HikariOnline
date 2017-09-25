#include "base_window.h"
#include "Core/Window/game_window.h"
#include "Core/Engine/game_engine.h"

IMPLEMENT_CLASS(Hikari::BaseWindow)

namespace Hikari
{
	void BaseWindow::ShowWindow()
	{
		if (mRootWidget == nullptr)
		{
			const int& win_width = GameEngine::Instance()->GetGameWindow()->GetWidth();
			const int& win_height = GameEngine::Instance()->GetGameWindow()->GetHeight();
			mRootWidget = GameEngine::Instance()->GetGameWindow()->GetMyGUI()->createWidget<MyGUI::Window>("", 0, 0, win_width, win_height, MyGUI::Align::Default, "Main");
		}
	}

	void BaseWindow::CloseWindow()
	{
		GameEngine::Instance()->GetGameWindow()->GetMyGUI()->destroyWidget(mRootWidget);
	}

	void BaseWindow::LoadLayout(const char* arg_layout)
	{
		MyGUI::VectorWidgetPtr roots = MyGUI::LayoutManager::getInstance().loadLayout(arg_layout, "", mRootWidget);
	}
}
