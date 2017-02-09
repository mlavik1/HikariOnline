#include "input_manager.h"
#include "Core/Engine/game_instance.h"
#include "Core/Engine/game_engine.h"
#include "Core/Window/game_window.h"
#include <sstream>

namespace Hikari
{

	InputManager::InputManager(GameInstance* arg_gameinstance)
	{
		mGameInstance = arg_gameinstance;

		OIS::ParamList oisParamList;
		size_t windowHwnd = 0;
		std::ostringstream windowHndStr;
		GameEngine::Instance()->GetGameWindow()->GetRenderWindow()->getCustomAttribute("WINDOW", &windowHwnd);
		windowHndStr << windowHwnd;
		oisParamList.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		mInputSystem = OIS::InputManager::createInputSystem(oisParamList);
		mMouseInputObject = static_cast<OIS::Mouse*>(mInputSystem->createInputObject(OIS::OISMouse, false));
		mKeyboardInputObject = static_cast<OIS::Keyboard*>(mInputSystem->createInputObject(OIS::OISKeyboard, false));
	}

	void InputManager::CaptureInput()
	{
		mMouseInputObject->capture();
		mKeyboardInputObject->capture();
	}

	bool InputManager::keyPressed(const OIS::KeyEvent &e)
	{
		return true;
	}

	bool InputManager::keyReleased(const OIS::KeyEvent &e)
	{
		return true;
	}

	bool InputManager::mouseMoved(const OIS::MouseEvent &e)
	{
		return true;
	}

	bool InputManager::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		return true;
	}

	bool InputManager::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		return true;
	}

	bool InputManager::povMoved(const OIS::JoyStickEvent &e, int pov)
	{
		return true;
	}

	bool InputManager::axisMoved(const OIS::JoyStickEvent &e, int axis)
	{
		return true;
	}

	bool InputManager::sliderMoved(const OIS::JoyStickEvent &e, int sliderID)
	{
		return true;
	}

	bool InputManager::buttonPressed(const OIS::JoyStickEvent &e, int button)
	{
		return true;
	}

	bool InputManager::buttonReleased(const OIS::JoyStickEvent &e, int button)
	{
		return true;
	}

}
