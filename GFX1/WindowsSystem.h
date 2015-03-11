#ifndef ___WINDOWSSYSTEM_H___
#define ___WINDOWSSYSTEM_H___

#include "ISystem.h"
#include "WindowProcCallback.h"

#include <windows.h>

namespace System{
	namespace WindowsSystem{

		struct WindowsSystemData;

		class WindowsSystem : public ISystem{
		private:
			WindowsSystemData*data;

		public:

			WindowsSystem();
			virtual ~WindowsSystem();

			bool init(char*cmdLine);

			void run(void);

			void release(void);

			WindowsSystemData*getWindowsData(void);
			HWND getWindow(void);
			virtual int getWindowWidth(void);
			virtual int getWindowHeight(void);

			virtual void registerSubSystem(std::shared_ptr<ISubSystem>);
			virtual void unregisterSubSystem(std::shared_ptr<ISubSystem>);

			LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			void registerWindowProcCallback(std::shared_ptr<IWindowProcCallback> cb);
			

			virtual void initalizeStage1(void);
			virtual void initalizeStage2(void);

			virtual void releaseStage1(void);
			virtual void releaseStage2(void);

		};//class WindowsSystem

	}//namespace WindowsSystem
}//namespace System
#endif //___WINDOWSSYSTEM_H___