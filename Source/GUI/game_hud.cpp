#include "game_hud.h"
#include "Core/Engine/game_engine.h"
#include "Core/Window/game_window.h"
#include "Core/Debug/st_assert.h"
#include "Core/Networking/rpc.h"
#include "Core/Networking/net_message_data.h"
#include "Core/Controller/game_server_network_controller.h"
#include "Core/Engine/client.h"

IMPLEMENT_CLASS(Hikari::GameHUD)

namespace Hikari
{

	void GameHUD::ShowWindow()
	{
		BaseWindow::ShowWindow();
		
		LoadLayout(mGameHUDLayout);
		LoadLayout(mGameChatLayout);
		
		mChatWindow = GameEngine::Instance()->GetGameWindow()->GetMyGUI()->findWidget<MyGUI::Window>("ChatWindow");
		mChatInputBox = GameEngine::Instance()->GetGameWindow()->GetMyGUI()->findWidget<MyGUI::EditBox>("ChatInput");
		mChatMessageBox = GameEngine::Instance()->GetGameWindow()->GetMyGUI()->findWidget<MyGUI::EditBox>("ChatMessages");
		mSubmitButton = GameEngine::Instance()->GetGameWindow()->GetMyGUI()->findWidget<MyGUI::Button>("SubmitButton");
		
		__Assert(mChatInputBox != nullptr);
		__Assert(mChatInputBox != nullptr);
		__Assert(mChatMessageBox != nullptr);
		__Assert(mSubmitButton != nullptr);

		//mChatWindow->setAlpha(0.1f);
		//mChatMessageBox->setAlpha(1.0f);
		//mChatMessageBox->setColour(MyGUI::Colour(1.0f, 1.0f, 1.0f, 0.01f));
		//mChatMessageBox->setInheritsAlpha(false);

		mChatInputBox->eventKeyButtonPressed += MyGUI::newDelegate(this, &GameHUD::notify_ChatInputBoxInput);
		mSubmitButton->eventMouseButtonClick += MyGUI::newDelegate(this, &GameHUD::notify_SubmitButtonClicked);
	}

	void GameHUD::CloseWindow()
	{
		BaseWindow::CloseWindow();
	}

	void GameHUD::notify_SubmitButtonClicked(MyGUI::Widget* _sender)
	{
		SendChatMessage(std::string(mChatInputBox->getCaption()).c_str());
		mChatInputBox->setCaption("");
	}

	void GameHUD::notify_ChatInputBoxInput(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char)
	{
		// TODO: move to ChatSystem (call ChatSystem::ChatInput(...))
		switch (_key.getValue())
		{
			case MyGUI::KeyCode::Return:
			case MyGUI::KeyCode::NumpadEnter:
				SendChatMessage(std::string(mChatInputBox->getCaption()).c_str());
				mChatInputBox->setCaption("");
				break;
			case MyGUI::KeyCode::LeftShift:
			case MyGUI::KeyCode::RightShift:
				break;
			case MyGUI::KeyCode::Backspace:
				break;
			default:
				break;
		}
	}

	void GameHUD::AddChatMessage(const char* arg_message)
	{
		mChatMessageBox->setCaption(mChatMessageBox->getCaption() + "\n" + arg_message);

	}

	void GameHUD::SendChatMessage(const char* arg_message)
	{
		AddChatMessage(((std::string("You: ") + std::string(arg_message)).c_str()));
#ifdef HIKARI_CLIENT // TODO: don't include GUI source folder in server projects
		std::string chatMessage(arg_message);
		GameServerCall(GameEngine::Instance()->GetClient()->GetGameServerNetworkController(), ServerSendMessage, chatMessage);
#endif
	}

}
