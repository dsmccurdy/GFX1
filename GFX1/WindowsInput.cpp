#include <vector>
#include <list>

#include "WindowsSystem.h"
#include "WindowsInput.h"
#include "IKeyCallback.h"

#include "Debug.h"

namespace Input{
	namespace WindowsInput{

		struct WindowsInputData{
			std::shared_ptr<System::WindowsSystem::WindowsSystem> system;

			std::list<std::shared_ptr<IMouseCallback>>*mouseCallback;

			float mouseX;
			float mouseY;
			float mouseWheel[2];
			bool mouseButton[16];

			std::list<std::shared_ptr<IKeyCallback>>*keyCallback;

			bool keyMap[256];
		};//struct WindowsInputData



		
		WindowsInput::WindowsInput(std::shared_ptr<System::WindowsSystem::WindowsSystem> ws){
			data = new WindowsInputData();
			data->system = ws;
			data->keyCallback = new std::list<std::shared_ptr<IKeyCallback>>();
			data->mouseCallback = new std::list<std::shared_ptr<IMouseCallback>>();

			data->mouseX = 0.5f;
			data->mouseY = 0.5f;
			data->mouseWheel[0] = data->mouseWheel[1] = 0.0f;
			memset(data->mouseButton, 0, sizeof(data->mouseButton));

			memset(data->keyMap, 0, sizeof(data->keyMap));

		}//WindowsInput::WindowsInput(std::shared_ptr<System::WindowsSystem::WindowsSystem> ws)

		WindowsInput::~WindowsInput(){
			releaseStage1();
			releaseStage2();
		}//WindowsInput::~WindowsInput()
		
		void WindowsInput::initalizeStage1(void){

			setDefaultInstance(shared_from_this());

			//data->system->registerSubSystem(shared_from_this());
			data->system->registerWindowProcCallback(shared_from_this());

		}//bool WindowsInput::initalizeStage1(System::WindowsSystem::WindowsSystem*system)

		LRESULT WindowsInput::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

			Input::VKEY::VKEY key;

			switch (uMsg){
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				if ((lParam & (1 << 30)) == 0){

					key = mapWindowsKey(wParam, lParam);
					data->keyMap[key] = true;

					for (std::shared_ptr<IKeyCallback> kc : *data->keyCallback){
						kc->keyDownCallback(key);
					}

				}//if ((lParam & (1 << 30)) == 0)
				break;
			case WM_KEYUP:
			case WM_SYSKEYUP:
				//if ((lParam >> 30)) == 1){

					key = mapWindowsKey(wParam, lParam);
					data->keyMap[key] = false;

					for (std::shared_ptr<IKeyCallback> kc : *data->keyCallback){
						kc->keyUpCallback(key);
					}

				//}//if ((lParam & (1 << 30)) == 0)
				break;
			case WM_MOUSEMOVE:
				data->mouseX = LOWORD(lParam);
				data->mouseY = HIWORD(lParam);
				data->mouseX /= data->system->getWindowWidth();
				data->mouseY /= data->system->getWindowHeight();

				for (std::shared_ptr < IMouseCallback> cb : *data->mouseCallback){
					cb->mouseMove(data->mouseX, data->mouseY);
				}

				break;
			case WM_LBUTTONDOWN:
				data->mouseButton[MouseButton::LEFT] = true;
				for (std::shared_ptr<IMouseCallback> cb : *data->mouseCallback){
					cb->mouseButtonDown(MouseButton::LEFT);
				}
				break;
			case WM_LBUTTONUP:
				data->mouseButton[MouseButton::LEFT] = false;
				for (std::shared_ptr<IMouseCallback> cb : *data->mouseCallback){
					cb->mouseButtonUp(MouseButton::LEFT);
				}
				break;
			case WM_MBUTTONDOWN:
				data->mouseButton[MouseButton::MIDDLE] = true;
				for (std::shared_ptr<IMouseCallback> cb : *data->mouseCallback){
					cb->mouseButtonDown(MouseButton::MIDDLE);
				}
				break;
			case WM_MBUTTONUP:
				data->mouseButton[MouseButton::MIDDLE] = false;
				for (std::shared_ptr<IMouseCallback> cb : *data->mouseCallback){
					cb->mouseButtonUp(MouseButton::MIDDLE);
				}
				break;
			case WM_RBUTTONDOWN:
				data->mouseButton[MouseButton::RIGHT] = true;
				for (std::shared_ptr<IMouseCallback> cb : *data->mouseCallback){
					cb->mouseButtonDown(MouseButton::RIGHT);
				}
				break;
			case WM_RBUTTONUP:
				data->mouseButton[MouseButton::RIGHT] = false;
				for (std::shared_ptr<IMouseCallback> cb : *data->mouseCallback){
					cb->mouseButtonUp(MouseButton::RIGHT);
				}
				break;
			case WM_MOUSEWHEEL:
				data->mouseWheel[0] += HIWORD(wParam);
				for (std::shared_ptr<IMouseCallback> cb : *data->mouseCallback){
					cb->mouseWheel(HIWORD(wParam), data->mouseWheel[0]);
				}
				break;
			case WM_MOUSEHWHEEL:
				data->mouseWheel[1] += HIWORD(wParam);
				for (std::shared_ptr<IMouseCallback> cb : *data->mouseCallback){
					cb->mouseHorizontalWheel(HIWORD(wParam), data->mouseWheel[1]);
				}
				break;
			}//switch (uMsg)

			return 0;
		}//LRESULT WindowsInput::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)

		void WindowsInput::releaseStage2(void){
			if (data){
				delete data->keyCallback;
				delete data->mouseCallback;

				delete data;
				data = nullptr;
			}
		}//void WindowsInput::releaseStage2(void)

		void WindowsInput::registerMouseCallback(std::shared_ptr<IMouseCallback> cb){
			data->mouseCallback->push_back(cb);
		}//void WindowsInput::registerMouseCallback(std::shared_ptr<IMouseCallback>)

		void WindowsInput::unregisterMouseCallback(std::shared_ptr<IMouseCallback> cb){
			data->mouseCallback->remove(cb);
		}//void WindowsInput::unregisterMouseCallback(std::shared_ptr<IMouseCallback>)


		void WindowsInput::registerKeyboardCallback(std::shared_ptr<IKeyCallback> cb){
			data->keyCallback->remove(cb);
			data->keyCallback->push_back(cb);
		}//void WindowsInput::registerKeyboardCallback(IKeyCallback*cb)

		void WindowsInput::unregisterKeyboardCallback(std::shared_ptr<IKeyCallback> cb){
			data->keyCallback->remove(cb);
		}//void WindowsInput::unregisterKeyboardCallback(IKeyCallback*cb)

		bool WindowsInput::keyIsDown(Input::VKEY::VKEY vkey){
			return data->keyMap[vkey];
		}//bool WindowsInput::keyIsDown(Input::VKEY::VKEY vkey)

		float WindowsInput::mouseX(void){
			return data->mouseX;
		}//float WindowsInput::mouseX(void)

		float WindowsInput::mouseY(void){
			return data->mouseY;
		}//float WindowsInput::mouseY(void)

		float WindowsInput::mouseWheel(void){
			return data->mouseWheel[0];
		}//float WindowsInput::mouseWheel(void)

		float WindowsInput::mouseHorizontalWheel(void){
			return data->mouseWheel[1];
		}//float WindowsInput::mouseHorizontalWheel(void)

		bool WindowsInput::mouseButtonIsDown(MouseButton mb){
			return data->mouseButton[mb];
		}//bool WindowsInput::mouseButtonIsDown(MouseButton)

		Input::VKEY::VKEY WindowsInput::mapWindowsKey(WPARAM wParam, LPARAM lParam){

			Input::VKEY::VKEY key = Input::VKEY::VKEY_UNKNOWN;
			switch (wParam){

			case VK_BACK:
				key = Input::VKEY::VKEY_BACKSPACE;
				break;
			case VK_TAB:
				key = Input::VKEY::VKEY_TAB;
				break;
			case VK_RETURN:
				key = Input::VKEY::VKEY_ENTER;
				break;
			case VK_PAUSE:
				key = Input::VKEY::VKEY_PAUSE;
				break;
			case VK_CAPITAL:
				key = Input::VKEY::VKEY_CAPSLOCK;
				break;
			case VK_ESCAPE:
				key = Input::VKEY::VKEY_ESC;
				break;
			case VK_SPACE:
				key = Input::VKEY::VKEY_SPACE;
				break;
			case VK_PRIOR:
				key = Input::VKEY::VKEY_PGUP;
				break;
			case VK_NEXT:
				key = Input::VKEY::VKEY_PGDN;
				break;
			case VK_END:
				key = Input::VKEY::VKEY_END;
				break;
			case VK_HOME:
				key = Input::VKEY::VKEY_HOME;
				break;
			case VK_LEFT:
				key = Input::VKEY::VKEY_LARROW;
				break;
			case VK_UP:
				key = Input::VKEY::VKEY_UARROW;
				break;
			case VK_RIGHT:
				key = Input::VKEY::VKEY_RARROW;
				break;
			case VK_DOWN:
				key = Input::VKEY::VKEY_DARROW;
				break;
			case VK_PRINT:
				key = Input::VKEY::VKEY_PRINTSCREEN;
				break;
			case VK_SNAPSHOT:
				key = Input::VKEY::VKEY_PRINTSCREEN;
				break;
			case VK_INSERT:
				key = Input::VKEY::VKEY_DELETE;
				break;
			case VK_DELETE:
				key = Input::VKEY::VKEY_DELETE;
				break;
			case 0x30:
				key = Input::VKEY::VKEY_0;
				break;
			case 0x31:
				key = Input::VKEY::VKEY_1;
				break;
			case 0x32:
				key = Input::VKEY::VKEY_2;
				break;
			case 0x33:
				key = Input::VKEY::VKEY_3;
				break;
			case 0x34:
				key = Input::VKEY::VKEY_4;
				break;
			case 0x35:
				key = Input::VKEY::VKEY_5;
				break;
			case 0x36:
				key = Input::VKEY::VKEY_6;
				break;
			case 0x37:
				key = Input::VKEY::VKEY_7;
				break;
			case 0x38:
				key = Input::VKEY::VKEY_8;
				break;
			case 0x39:
				key = Input::VKEY::VKEY_9;
				break;
			case 0x41:
				key = Input::VKEY::VKEY_A;
				break;
			case 0x42:
				key = Input::VKEY::VKEY_B;
				break;
			case 0x43:
				key = Input::VKEY::VKEY_C;
				break;
			case 0x44:
				key = Input::VKEY::VKEY_D;
				break;
			case 0x45:
				key = Input::VKEY::VKEY_E;
				break;
			case 0x46:
				key = Input::VKEY::VKEY_F;
				break;
			case 0x47:
				key = Input::VKEY::VKEY_G;
				break;
			case 0x48:
				key = Input::VKEY::VKEY_H;
				break;
			case 0x49:
				key = Input::VKEY::VKEY_I;
				break;
			case 0x4A:
				key = Input::VKEY::VKEY_J;
				break;
			case 0x4B:
				key = Input::VKEY::VKEY_K;
				break;
			case 0x4C:
				key = Input::VKEY::VKEY_L;
				break;
			case 0x4D:
				key = Input::VKEY::VKEY_M;
				break;
			case 0x4E:
				key = Input::VKEY::VKEY_N;
				break;
			case 0x4F:
				key = Input::VKEY::VKEY_O;
				break;
			case 0x50:
				key = Input::VKEY::VKEY_P;
				break;
			case 0x51:
				key = Input::VKEY::VKEY_Q;
				break;
			case 0x52:
				key = Input::VKEY::VKEY_R;
				break;
			case 0x53:
				key = Input::VKEY::VKEY_S;
				break;
			case 0x54:
				key = Input::VKEY::VKEY_T;
				break;
			case 0x55:
				key = Input::VKEY::VKEY_U;
				break;
			case 0x56:
				key = Input::VKEY::VKEY_V;
				break;
			case 0x57:
				key = Input::VKEY::VKEY_W;
				break;
			case 0x58:
				key = Input::VKEY::VKEY_X;
				break;
			case 0x59:
				key = Input::VKEY::VKEY_Y;
				break;
			case 0x5A:
				key = Input::VKEY::VKEY_Z;
				break;
			case VK_NUMPAD0:
				key = Input::VKEY::VKEY_NUM0;
				break;
			case VK_NUMPAD1:
				key = Input::VKEY::VKEY_NUM1;
				break;
			case VK_NUMPAD2:
				key = Input::VKEY::VKEY_NUM2;
				break;
			case VK_NUMPAD3:
				key = Input::VKEY::VKEY_NUM3;
				break;
			case VK_NUMPAD4:
				key = Input::VKEY::VKEY_NUM4;
				break;
			case VK_NUMPAD5:
				key = Input::VKEY::VKEY_NUM5;
				break;
			case VK_NUMPAD6:
				key = Input::VKEY::VKEY_NUM6;
				break;
			case VK_NUMPAD7:
				key = Input::VKEY::VKEY_NUM7;
				break;
			case VK_NUMPAD8:
				key = Input::VKEY::VKEY_NUM8;
				break;
			case VK_NUMPAD9:
				key = Input::VKEY::VKEY_NUM9;
				break;
			case VK_MULTIPLY:
				key = Input::VKEY::VKEY_NUMMULT;
				break;
			case VK_ADD:
				key = Input::VKEY::VKEY_NUMPLUS;
				break;
			case VK_SUBTRACT:
				key = Input::VKEY::VKEY_NUMMINUS;
				break;
			case VK_DECIMAL:
				key = Input::VKEY::VKEY_NUMPERIOD;
				break;
			case VK_DIVIDE:
				key = Input::VKEY::VKEY_NUMDIVIDE;
				break;
			case VK_F1:
				key = Input::VKEY::VKEY_F1;
				break;
			case VK_F2:
				key = Input::VKEY::VKEY_F2;
				break;
			case VK_F3:
				key = Input::VKEY::VKEY_F3;
				break;
			case VK_F4:
				key = Input::VKEY::VKEY_F4;
				break;
			case VK_F5:
				key = Input::VKEY::VKEY_F5;
				break;
			case VK_F6:
				key = Input::VKEY::VKEY_F6;
				break;
			case VK_F7:
				key = Input::VKEY::VKEY_F7;
				break;
			case VK_F8:
				key = Input::VKEY::VKEY_F8;
				break;
			case VK_F9:
				key = Input::VKEY::VKEY_F9;
				break;
			case VK_F10:
				key = Input::VKEY::VKEY_F10;
				break;
			case VK_F11:
				key = Input::VKEY::VKEY_F11;
				break;
			case VK_F12:
				key = Input::VKEY::VKEY_F12;
				break;
			case VK_NUMLOCK:
				key = Input::VKEY::VKEY_NUMLOCK;
				break;
			case VK_SCROLL:
				key = Input::VKEY::VKEY_SCROLLLOCK;
				break;
			case VK_SHIFT:
				key = (GetKeyState(VK_RSHIFT) & 0xFF0) ? Input::VKEY::VKEY_RSHIFT : Input::VKEY::VKEY_LSHIFT;
				break;
			case VK_CONTROL:
				key = ((lParam & 0x01000000) != 0) ? Input::VKEY::VKEY_RCTRL : Input::VKEY::VKEY_LCTRL;
				break;
			case 220:
				key = Input::VKEY::VKEY_BACKSLASH;
				break;
			case 186:
				key = Input::VKEY::VKEY_SEMICOLIN;
				break;
			case 222:
				key = Input::VKEY::VKEY_QUOTE;
				break;
			case 18:
				key = ((lParam & 0x01000000) != 0) ? Input::VKEY::VKEY_RALT : Input::VKEY::VKEY_LALT;
				break;
			case 188:
				key = Input::VKEY::VKEY_COMMA;
				break;
			case 190:
				key = Input::VKEY::VKEY_PERIOD;
				break;
			case 191:
				key = Input::VKEY::VKEY_FORWARDSLASH;
				break;
			case 192:
				key = Input::VKEY::VKEY_TILDA;
				break;
			case 189:
				key = Input::VKEY::VKEY_MINUS;
				break;
			case 187:
				key = Input::VKEY::VKEY_PLUS;
				break;
			case 219:
				key = Input::VKEY::VKEY_LBRACKET;
				break;
			case 221:
				key = Input::VKEY::VKEY_RBRACKET;
				break;

			default:
				Debug::Print("Unknown key %d\n", wParam);
				break;

			}//switch (wParam)

			//Debug::Print("Key Pressed %s\n", Input::VKEY::keyToString(key).c_str());

			return key;
		}//System::VKEY mapWindowsKey(WPARAM wParam, LPARAM lParam)
		
	}//namespace WindowsInput
}//namespace Input