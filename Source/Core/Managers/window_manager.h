#ifndef HIKARI_WINDOWMANAGER_H
#define HIKARI_WINDOWMANAGER_H

#include "Core/Common/singleton.h"
#include <unordered_map>
#include "Core/Object/object.h"

namespace Hikari
{
	class GameInstance;
	class BaseWindow;
	class WindowManager
	{
	private:
		GameInstance* mGameInstance;
		std::unordered_map<Hikari::Class*, BaseWindow*> mWindows;

	public:
		WindowManager(GameInstance* arg_gameinstance);

		BaseWindow* ShowWindow(Hikari::Class* arg_class);
		BaseWindow* AddUniqueWindow(Hikari::Class* arg_class);
		BaseWindow* GetWindow(Hikari::Class* arg_class);
		BaseWindow* GetWindow(const char* arg_classname);

	};
}

#endif
