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
		mMousePressStates = 0;
		mMouseReleaseStates = 0;

		OIS::ParamList oisParamList;
		size_t windowHwnd = 0;
		std::ostringstream windowHndStr;
		arg_gameinstance->GetGameWindow()->GetRenderWindow()->getCustomAttribute("WINDOW", &windowHwnd);
		windowHndStr << windowHwnd;
		oisParamList.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		oisParamList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		oisParamList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		oisParamList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		oisParamList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		oisParamList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		oisParamList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
		oisParamList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		oisParamList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));

		mInputSystem = OIS::InputManager::createInputSystem(oisParamList);

		if (mInputSystem)
		{
			mMouseInputObject = static_cast<OIS::Mouse*>(mInputSystem->createInputObject(OIS::OISMouse, true));
			mKeyboardInputObject = static_cast<OIS::Keyboard*>(mInputSystem->createInputObject(OIS::OISKeyboard, true));

			mKeyboardInputObject->setEventCallback(this);
			mMouseInputObject->setEventCallback(this);
		}

		setupInputMap();
	}

	InputManager::~InputManager()
	{
		if (mInputSystem)
		{
			if (mKeyboardInputObject)
			{
				mInputSystem->destroyInputObject(mKeyboardInputObject);
			}
			if (mMouseInputObject)
			{
				mInputSystem->destroyInputObject(mMouseInputObject);
			}
			mInputSystem->destroyInputSystem(mInputSystem);
		}
	}

	void InputManager::CaptureInput()
	{
		mKeyUpMap.clear();
		mKeyDownMap.clear();
		mMouseMove = Ogre::Vector2::ZERO;

		mMouseInputObject->capture();
		mKeyboardInputObject->capture();
		mMouseReleaseStates = 0;
	}


	bool InputManager::GetKey(const char* arg_key)
	{
		try {
			InputMapKeyCode keyCode = mKeycodeMap.at(arg_key);
			return mKeyPressedMap.at(keyCode);
		}
		catch (const std::out_of_range& oor) {}
		return false;
	}

	bool InputManager::GetKeyDown(const char* arg_key)
	{
		try {
			InputMapKeyCode keyCode = mKeycodeMap.at(arg_key);
			return mKeyUpMap.at(keyCode);
		}
		catch (const std::out_of_range& oor) {}
		return false;
	}

	bool InputManager::GetKeyUp(const char* arg_key)
	{
		try {
			InputMapKeyCode keyCode = mKeycodeMap.at(arg_key);
			return mKeyDownMap.at(keyCode);
		}
		catch (const std::out_of_range& oor) {}
		return false;
	}

	bool InputManager::GetMousePressed(MouseButtonID arg_button)
	{
		return mMousePressStates & ((MouseButtonID)1 << arg_button );
	}

	bool InputManager::GetMouseReleased(MouseButtonID arg_button)
	{
		return mMouseReleaseStates & ((MouseButtonID)1 << arg_button);
	}

	const Ogre::Vector2& InputManager::GetMouseMove() const
	{
		return mMouseMove;
	}

	const Ogre::Vector2& InputManager::GetMousePosition() const
	{
		return mMousePosition;
	}


	/***/
	/***************************** OIS EVENTS *****************************/


	bool InputManager::keyPressed(const OIS::KeyEvent &e)
	{
		mKeyDownMap[e.key] = true;
		mKeyPressedMap[e.key] = true;
		return true;
	}

	bool InputManager::keyReleased(const OIS::KeyEvent &e)
	{
		mKeyPressedMap[e.key] = false;
		mKeyUpMap[e.key] = true;
		return true;
	}

	bool InputManager::mouseMoved(const OIS::MouseEvent &e)
	{
		mMouseMove = Ogre::Vector2(e.state.X.rel, e.state.Y.rel);
		mMousePosition = Ogre::Vector2(e.state.X.abs, e.state.Y.abs);
		return true;
	}

	bool InputManager::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		mMousePressStates |= ((MouseButtonID)1 << id);
		return true;
	}

	bool InputManager::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		mMouseReleaseStates |= ((MouseButtonID)1 << id);
		mMousePressStates &= !((MouseButtonID)1 << id);
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




	void InputManager::setupInputMap()
	{
		// TODO: read from ini-file

		mKeycodeMap["up"] = OIS::KeyCode::KC_UP;
		mKeycodeMap["down"] = OIS::KeyCode::KC_DOWN;
		mKeycodeMap["left"] = OIS::KeyCode::KC_LEFT;
		mKeycodeMap["right"] = OIS::KeyCode::KC_RIGHT;
		mKeycodeMap["space"] = OIS::KeyCode::KC_SPACE;
		mKeycodeMap["return"] = OIS::KeyCode::KC_RETURN;
		mKeycodeMap["w"] = OIS::KeyCode::KC_W;
		mKeycodeMap["a"] = OIS::KeyCode::KC_A;
		mKeycodeMap["s"] = OIS::KeyCode::KC_S;
		mKeycodeMap["d"] = OIS::KeyCode::KC_D;
		mKeycodeMap["1"] = OIS::KeyCode::KC_1;
		mKeycodeMap["2"] = OIS::KeyCode::KC_2;
	}


}
