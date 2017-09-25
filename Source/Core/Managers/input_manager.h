#ifndef HIKARI_INPUTMANAGER_H
#define HIKARI_INPUTMANAGER_H

#include "OIS/OIS.h"
#include <unordered_map>
#include <stdint.h>
#include "OGRE/Ogre.h"

namespace Hikari
{
	typedef OIS::KeyCode InputMapKeyCode;
	typedef unsigned int MouseButtonID;

	class InputManager : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
	{
	public:
		InputManager();
		~InputManager();

		void CaptureInput();

		bool GetKey(const char* arg_key);
		bool GetKeyDown(const char* arg_key);
		bool GetKeyUp(const char* arg_key);

		bool GetMousePressed(MouseButtonID arg_button);
		bool GetMouseReleased(MouseButtonID arg_button);

		const Ogre::Vector2& GetMouseMove() const;
		const Ogre::Vector2& GetMousePosition() const;

		OIS::Keyboard* GetKeyboardInputObject() { return mKeyboardInputObject; }
		OIS::Mouse* GetMouseInputObject() { return mMouseInputObject; }

	private:
		OIS::InputManager* mInputSystem;
		OIS::Keyboard* mKeyboardInputObject;
		OIS::Mouse* mMouseInputObject;
		
		std::unordered_map<std::string, InputMapKeyCode> mKeycodeMap;

		std::unordered_map<InputMapKeyCode, bool> mKeyDownMap;
		std::unordered_map<InputMapKeyCode, bool> mKeyUpMap;
		std::unordered_map<InputMapKeyCode, bool> mKeyPressedMap;

		MouseButtonID mMousePressStates;
		MouseButtonID mMouseReleaseStates;

		Ogre::Vector2 mMouseMove;
		Ogre::Vector2 mMousePosition;

		void setupInputMap();
		bool keyPressed(const OIS::KeyEvent &e) override;
		bool keyReleased(const OIS::KeyEvent &e) override;
		bool mouseMoved(const OIS::MouseEvent &e) override;
		bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) override;
		bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) override;
		bool povMoved(const OIS::JoyStickEvent &e, int pov) override;
		bool axisMoved(const OIS::JoyStickEvent &e, int axis) override;
		bool sliderMoved(const OIS::JoyStickEvent &e, int sliderID) override;
		bool buttonPressed(const OIS::JoyStickEvent &e, int button) override;
		bool buttonReleased(const OIS::JoyStickEvent &e, int button) override;
		
	};
}

#endif
