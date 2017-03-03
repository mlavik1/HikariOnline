#include "window_manager.h"
#include "GUI/base_window.h"
#include "Core/Engine/game_engine.h"
#include "Core/Engine/game_instance.h"

namespace Hikari
{
	WindowManager::WindowManager(GameInstance* arg_gameinstance)
	{
		mGameInstance = arg_gameinstance;
	}
	
	BaseWindow* WindowManager::ShowWindow(Hikari::Class* arg_class)
	{
		BaseWindow* window = GetWindow(arg_class);
		if (window == nullptr)
		{
			window = AddUniqueWindow(arg_class);
		}
		if (window != nullptr)
		{
			window->ShowWindow();
		}
		return window;
	}

	BaseWindow* WindowManager::AddUniqueWindow(Hikari::Class* arg_class)
	{
		BaseWindow* window = GetWindow(arg_class);
		if (window == nullptr)
		{
			window = static_cast<BaseWindow*>(arg_class->CreateInstance());
			window->InitialiseObject(ObjectInitialiserParams()); // todo
			window->SetGameInstance(mGameInstance);
		}
		return window;
	}

	BaseWindow* WindowManager::GetWindow(Hikari::Class* arg_class)
	{
		__Assert(arg_class == BaseWindow::GetStaticClass() || arg_class->IsSubclassOf(BaseWindow::GetStaticClass()));
		
		auto wndIter = mWindows.find(arg_class);
		if (wndIter != mWindows.end())
			return wndIter->second;
		return nullptr;
	}

	BaseWindow* WindowManager::GetWindow(const char* arg_classname)
	{
		Hikari::Class* wndClass = Hikari::BaseWindow::GetStaticClass()->GetBaseClass()->GetChildClassByName(arg_classname, false);
		if (wndClass != nullptr)
		{
			return GetWindow(wndClass);
		}
		return nullptr;
	}

}
