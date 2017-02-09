#ifndef HIKARI_INPUTMANAGER_H
#define HIKARI_INPUTMANAGER_H

#include "OIS/OIS.h"

namespace Hikari
{
	class GameInstance;

	class InputManager : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
	{
	public:
		InputManager(GameInstance* arg_gameinstance);

		void CaptureInput();

	private:
		GameInstance* mGameInstance;

		OIS::InputManager* mInputSystem;
		OIS::Keyboard* mKeyboardInputObject;
		OIS::Mouse* mMouseInputObject;

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
