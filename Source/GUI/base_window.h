#ifndef HIKARI_BASEWINDOW_H
#define HIKARI_BASEWINDOW_H

#include "MYGUI/MyGUI.h"
#include "COre/Object/object.h"
#include "Core/Object/objdefs.h"

namespace Hikari
{
	class BaseWindow : public Object
	{
		DEFINE_CLASS(Hikari::BaseWindow, Hikari::Object)
	protected:
		MyGUI::WidgetPtr mRootWidget = nullptr;

	public:
		virtual void ShowWindow();
		virtual void CloseWindow();
		void LoadLayout(const char* arg_layout);
	};
}

#endif
