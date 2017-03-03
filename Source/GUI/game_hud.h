#ifndef HIKARI_GAMEHUD_H
#define HIKARI_GAMEHUD_H

#include "base_window.h"

namespace Hikari
{
	class GameHUD : public BaseWindow
	{
		DEFINE_CLASS(Hikari::GameHUD, Hikari::BaseWindow)
	private:
		const char* mGameHUDLayout = "GameHUD.layout";
		const char* mGameChatLayout = "GameChat.layout";
		MyGUI::EditBox* mChatInputBox = nullptr;
		MyGUI::EditBox* mChatMessageBox = nullptr;

	public:
		virtual void ShowWindow() override;
		virtual void CloseWindow() override;

		void AddChatMessage(const char* arg_message);

	private:
		void notify_ChatInputBoxInput(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char);
	};
}

#endif
