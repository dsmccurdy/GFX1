#ifndef ___WINDOWPROCCALLBACK_H___
#define ___WINDOWPROCCALLBACK_H___

#include <Windows.h>

namespace System{
	namespace WindowsSystem{

		class IWindowProcCallback{
		public:

			IWindowProcCallback(){};
			virtual ~IWindowProcCallback(){};

			virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
		};

	}//namespace WindowsSystem
}//namepsace System

#endif//___WINDOWPROCCALLBACK_H___