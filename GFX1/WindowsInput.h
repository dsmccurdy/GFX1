#ifndef ___WINDOWSINPUT_H___
#define ___WINDOWSINPUT_H___

#include <memory>

#include "ISubSystem.h"
#include "IInput.h"
#include "WindowsSystem.h"
#include "KeyCodes.h"

namespace Input{
	namespace WindowsInput{

		struct WindowsInputData;

		class WindowsInput : 
			public Input::IInput, 
			public System::ISubSystem,
			public System::WindowsSystem::IWindowProcCallback,
			public std::enable_shared_from_this<WindowsInput>{
		private:

			WindowsInputData*data;

			Input::VKEY::VKEY mapWindowsKey(WPARAM wParam, LPARAM lParam);

		public:

			WindowsInput(std::shared_ptr<System::WindowsSystem::WindowsSystem> ws);
			virtual ~WindowsInput();

			virtual void initalizeStage1(void);

			virtual void releaseStage2(void);

			virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			virtual void registerKeyboardCallback(std::shared_ptr<IKeyCallback>);
			virtual void unregisterKeyboardCallback(std::shared_ptr<IKeyCallback>);

			virtual void registerMouseCallback(std::shared_ptr<IMouseCallback>);
			virtual void unregisterMouseCallback(std::shared_ptr<IMouseCallback>);

			virtual bool keyIsDown(Input::VKEY::VKEY);

			virtual float mouseX(void);
			virtual float mouseY(void);

			virtual float mouseWheel(void);
			virtual float mouseHorizontalWheel(void);

			virtual bool mouseButtonIsDown(MouseButton);
			
		};//class WindowsInput

	}//namespace WindowsInput
}//namespace Input

#endif//___WINDOWSINPUT_H___