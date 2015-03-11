#ifndef ___IINPUT_H___
#define ___IINPUT_H___

#include "IKeyCallback.h"
#include "IMouseCallback.h"

namespace Input{

	class IInput{
	private:

		static std::shared_ptr<IInput> _instance;

	public:

		static std::shared_ptr<IInput> getDefaultInstance(void);
		static void setDefaultInstance(std::shared_ptr<IInput>);

		virtual void registerKeyboardCallback(std::shared_ptr<IKeyCallback>) = 0;
		virtual void unregisterKeyboardCallback(std::shared_ptr<IKeyCallback>) = 0;

		virtual void registerMouseCallback(std::shared_ptr<IMouseCallback>) = 0;
		virtual void unregisterMouseCallback(std::shared_ptr<IMouseCallback>) = 0;

		virtual bool keyIsDown(Input::VKEY::VKEY) = 0;

		virtual float mouseX(void) = 0;
		virtual float mouseY(void) = 0;

		virtual float mouseWheel(void) = 0;
		virtual float mouseHorizontalWheel(void) = 0;

		virtual bool mouseButtonIsDown(MouseButton) = 0;


	};//class IInput

}//namespace Input

#endif//___IINPUT_H___