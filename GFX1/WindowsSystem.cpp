#define _CRT_SECURE_NO_WARNINGS
#include "WindowsSystem.h"
#include "Debug.h"
#include "Thread.h"

#include <Windows.h>
#include <vector>
#include <list>
#include <string>
#include <cassert>


namespace System{
	namespace WindowsSystem{
		static const int DEFAULT_WIDTH = 1024;
		static const int DEFAULT_HEIGHT = 768;
		static const int DEFAULT_FPS = 60;

		struct WindowsSystemData{
			bool exit;
			HWND hwnd;
			WNDCLASSEX wc;
			TCHAR* windowTitle;

			int width;
			int height;
			int fps;

			std::list<std::shared_ptr<ISubSystem>>*subSystems;
			std::list<std::shared_ptr<IWindowProcCallback>>*winProcCallback;

		};//struct WindowsSystemData




		static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
			return std::static_pointer_cast<System::WindowsSystem::WindowsSystem>(ISystem::getInstance())->WindowProc(hwnd, uMsg, wParam, lParam);
		}//static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)


		void WindowsSystem::registerWindowProcCallback(std::shared_ptr<IWindowProcCallback> cb){
			data->winProcCallback->push_back(cb);
		}//void WindowsSystem::registerWindowProcCallback(IWindowProcCallback*cb)


		LRESULT WindowsSystem::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

			if (!data )
				return DefWindowProc(hwnd, uMsg, wParam, lParam);

			int x = 0, y = 0;

			if (data->winProcCallback){
				for (std::shared_ptr<IWindowProcCallback> cb : *data->winProcCallback){
					cb->WindowProc(hwnd, uMsg, wParam, lParam);
				}
			}

			switch (uMsg){
			case WM_CLOSE:
				std::static_pointer_cast<System::WindowsSystem::WindowsSystem>(ISystem::getInstance())->getWindowsData()->exit = true;
				break;
			default:
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}//switch (uMsg)

			return 0;
		}//LRESULT WindowsSystem::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)


		WindowsSystem::WindowsSystem(){
			data = new WindowsSystemData();
			data->exit = false;
			data->subSystems = new std::list<std::shared_ptr<ISubSystem>>();
			data->width = DEFAULT_WIDTH;
			data->height = DEFAULT_HEIGHT;
			data->fps = DEFAULT_FPS;


			WCHAR buffer[MAX_PATH];
			GetModuleFileName(NULL, buffer, MAX_PATH);

			WCHAR* title = wcsrchr(buffer, '\\');
			assert(title != nullptr);
			title++;

			WCHAR*end = wcsrchr(title, '.');
			*end = '\0';

			data->windowTitle = new WCHAR[wcslen(title) + 1];
			wcscpy(data->windowTitle, title);

			data->winProcCallback = new std::list<std::shared_ptr<IWindowProcCallback>>();

		}//WindowsSystem::WindowsSystem()

		WindowsSystem::~WindowsSystem(){
			release();
		}//WindowsSystem::~WindowsSystem()

		bool WindowsSystem::init(char*cmdLine){


			ZeroMemory(&data->wc, sizeof(data->wc));
			data->wc.cbSize = sizeof(WNDCLASSEX);
			data->wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_CLASSDC;
			data->wc.lpfnWndProc = WndProc;
			data->wc.hInstance = GetModuleHandle(NULL);
			data->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			data->wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			data->wc.lpszClassName = data->windowTitle;
			RegisterClassEx(&data->wc);


			RECT rect;
			SetRect(&rect, 0, 0, data->width, data->height);
			const DWORD windowFlags = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_SYSMENU | WS_MINIMIZEBOX;

			AdjustWindowRectEx(&rect, windowFlags, FALSE, 0);
			data->hwnd = CreateWindowEx(0, data->windowTitle, data->windowTitle, windowFlags, 200, 200, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, GetModuleHandle(NULL), NULL);

			if (data->hwnd == NULL){
				UnregisterClass(data->windowTitle, GetModuleHandle(NULL));
				return false;
			}

			GetWindowRect(data->hwnd, &rect);
			RECT system;
			SystemParametersInfo(SPI_GETWORKAREA, 0, &system, 0);
			MoveWindow(data->hwnd, (system.right - system.left) / 2 - (rect.right - rect.left) / 2, (system.bottom - system.top) / 2 - (rect.bottom - rect.top) / 2, rect.right - rect.left, rect.bottom - rect.top, TRUE);

			

			return true;
		}//bool WindowsSystem::init(char*cmdLine)
		
		void WindowsSystem::run(void){

			ShowWindow(data->hwnd, SW_SHOWNORMAL);

			MSG msg;
			ULONGLONG timer = GetTickCount64();

			System::Thread::initThreadPool();
			

			for (auto subSys : *data->subSystems){
				subSys->initalizeStage2();
			}

			while (!data->exit){
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else{//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))

					if (timer <= (GetTickCount64() - 1000 / data->fps)){
						timer = GetTickCount64();

						System::Thread::resumeAllThreads();


						///////////////////////////// startReadPhase
						for (auto subSys : *data->subSystems){
							class Work : public IWorkUnit{
							public:
								std::shared_ptr<ISubSystem> subSys;
								virtual void doWork(void){
									subSys->startReadPhase();
								}
							};
							std::shared_ptr<Work> work = std::shared_ptr<Work>(new Work());
							work->subSys = subSys;
							Thread::pushWorkToLowest(work);	
						}
						while (!Thread::allThreadsWaiting()){
							std::this_thread::sleep_for(std::chrono::microseconds(1));
						}

						///////////////////////////// readPhase
						for (auto subSys : *data->subSystems){
							class Work : public IWorkUnit{
							public:
								std::shared_ptr<ISubSystem> subSys;
								virtual void doWork(void){
									subSys->readPhase();
								}
							};
							std::shared_ptr<Work> work = std::shared_ptr<Work>(new Work());
							work->subSys = subSys;
							Thread::pushWorkToLowest(work);
						}
						while (!Thread::allThreadsWaiting()){
							std::this_thread::sleep_for(std::chrono::microseconds(1));
						}

						///////////////////////////// endReadPhase
						for (auto subSys : *data->subSystems){
							class Work : public IWorkUnit{
							public:
								std::shared_ptr<ISubSystem> subSys;
								virtual void doWork(void){
									subSys->endReadPhase();
								}
							};
							std::shared_ptr<Work> work = std::shared_ptr<Work>(new Work());
							work->subSys = subSys;
							Thread::pushWorkToLowest(work);
						}
						while (!Thread::allThreadsWaiting()){
							std::this_thread::sleep_for(std::chrono::microseconds(1));
						}

						///////////////////////////// startWritePhase
						for (auto subSys : *data->subSystems){
							class Work : public IWorkUnit{
							public:
								std::shared_ptr<ISubSystem> subSys;
								virtual void doWork(void){
									subSys->startWritePhase();
								}
							};
							std::shared_ptr<Work> work = std::shared_ptr<Work>(new Work());
							work->subSys = subSys;
							Thread::pushWorkToLowest(work);
						}
						while (!Thread::allThreadsWaiting()){
							std::this_thread::sleep_for(std::chrono::microseconds(1));
						}

						///////////////////////////// writePhase
						for (auto subSys : *data->subSystems){
							class Work : public IWorkUnit{
							public:
								std::shared_ptr<ISubSystem> subSys;
								virtual void doWork(void){
									subSys->writePhase();
								}
							};
							std::shared_ptr<Work> work = std::shared_ptr<Work>(new Work());
							work->subSys = subSys;
							Thread::pushWorkToLowest(work);
						}
						while (!Thread::allThreadsWaiting()){
							std::this_thread::sleep_for(std::chrono::microseconds(1));
						}

						///////////////////////////// endWritePhase
						for (auto subSys : *data->subSystems){
							class Work : public IWorkUnit{
							public:
								std::shared_ptr<ISubSystem> subSys;
								virtual void doWork(void){
									subSys->endWritePhase();
								}
							};
							std::shared_ptr<Work> work = std::shared_ptr<Work>(new Work());
							work->subSys = subSys;
							Thread::pushWorkToLowest(work);
						}
						while (!Thread::allThreadsWaiting()){
							std::this_thread::sleep_for(std::chrono::microseconds(1));
						}

						System::Thread::pauseAllThreads();
					}//if (timer <= (GetTickCount64() - 1000 / data->fps))

				}//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			}//while (!data->exit)

			for (auto subSys : *data->subSystems){
				subSys->releaseStage1();
			}
			for (auto subSys : *data->subSystems){
				subSys->releaseStage2();
			}
			data->subSystems->clear();
			
			System::Thread::releaseThreadPool();
		}//void WindowsSystem::run(void)

		void WindowsSystem::release(void){

			if (data){

				releaseStage1();
				releaseStage2();

				ShowWindow(data->hwnd, SW_HIDE);

				delete data->winProcCallback;
				data->winProcCallback = nullptr;

				

				delete data->subSystems;
				data->subSystems = nullptr;

				DestroyWindow(data->hwnd);
				UnregisterClass(data->windowTitle, GetModuleHandle(NULL));

				delete data;
				data = nullptr;
			}//if (data)

		}//void WindowsSystem::release(void)


		WindowsSystemData*WindowsSystem::getWindowsData(void){
			return data;
		}//WindowsSystemData*WindowsSystem::getWindowsData(void)

		HWND WindowsSystem::getWindow(void){
			return data->hwnd;
		}//HWND WindowsSystem::getWindow(void)

		int WindowsSystem::getWindowWidth(void){
			RECT rect;
			GetClientRect(getWindow(), &rect);
			return rect.right;
		}//int WindowsSystem::getWindowWidth(void)

		int WindowsSystem::getWindowHeight(void){
			RECT rect;
			GetClientRect(getWindow(), &rect);
			return rect.bottom;
		}//int WindowsSystem::getWindowHeight(void)

		void WindowsSystem::registerSubSystem(std::shared_ptr<ISubSystem> subSystem){
			data->subSystems->remove(subSystem);
			data->subSystems->push_back(subSystem);
		}//void WindowsSystem::registerSubSystem(std::shared_ptr<ISubSystem> subSystem)

		void WindowsSystem::unregisterSubSystem(std::shared_ptr<ISubSystem> subSystem){
			data->subSystems->remove(subSystem);
		}//void WindowsSystem::unregisterSubSystem(std::shared_ptr<ISubSystem subSystem>)


		void WindowsSystem::initalizeStage1(void){
			for (auto subSys : *data->subSystems){
				subSys->initalizeStage1();
			}
		}//void WindowsSystem::initalizeStage1(void)

		void WindowsSystem::initalizeStage2(void){
			for (auto subSys : *data->subSystems){
				subSys->initalizeStage2();
			}
		}//void WindowsSystem::initalizeStage2(void)

		void WindowsSystem::releaseStage1(void){
			for (auto subSys : *data->subSystems){
				subSys->releaseStage1();
			}
		}//void WindowsSystem::releaseStage1(void)

		void WindowsSystem::releaseStage2(void){
			for (auto subSys : *data->subSystems){
				subSys->releaseStage2();
			}
			data->subSystems->clear();
		}//void WindowsSystem::releaseStage2(void)

	}//namespace WindowsSystem
}//namepsace System