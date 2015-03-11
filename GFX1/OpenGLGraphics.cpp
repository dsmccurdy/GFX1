#define _CRT_SECURE_NO_WARNINGS
#include "OpenGLGraphics.h"
#include "WindowsSystem.h"
#include "Debug.h"

#include <Windows.h>
#include <gl/GL.h>
#include <cassert>
#include <vector>
#include <list>

namespace Graphics{
	namespace OpenGL{

		void _checkOpenGlError(const char* file, const long line){

			char*str = "Unkown";
			int error = glGetError();
			switch (error){
			case GL_NO_ERROR:
				return;
				break;
			case GL_INVALID_ENUM:
				str = "GL_INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				str = "GL_INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				str = "GL_INVALID_OPERATION";
				break;
			case GL_OUT_OF_MEMORY:
				str = "GL_OUT_OF_MEMORY";
				break;
			case GL_STACK_UNDERFLOW:
				str = "GL_STACK_UNDERFLOW";
				break;
			case GL_STACK_OVERFLOW:
				str = "GL_STACK_OVERFLOW";
				break;
			};//switch (error)

			Debug::Print("OpenGL error \"%s\" thrown at \"%s\": %d  \n", str, file, line);
			assert(false);
		}//void _checkOpenGlError(const char* file, const long line)

		struct OpenGLGraphicsData{
			std::shared_ptr<System::ISystem> system;

			HDC device;
			HGLRC context;

			std::list<std::shared_ptr<IGfxObject>>*objects;

		};//struct OpenGLGraphicsData


		OpenGLGraphics::OpenGLGraphics(){
			data = new OpenGLGraphicsData();
			data->objects = new std::list<std::shared_ptr<IGfxObject>>();

		}//OpenGLGraphics::OpenGLGraphics()

		OpenGLGraphics::~OpenGLGraphics(){
			release();
		}//OpenGLGraphics::~OpenGLGraphics()


		bool OpenGLGraphics::init(std::shared_ptr<System::ISystem> system){

			setInstance(shared_from_this());

			data->system = system;

			PIXELFORMATDESCRIPTOR pfd;
			memset(&pfd, 0, sizeof(pfd));

			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | LPD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 16;

			data->device = GetDC(std::static_pointer_cast<System::WindowsSystem::WindowsSystem>(data->system)->getWindow());
			assert(data->device);

			int pf = ChoosePixelFormat(data->device, &pfd);
			SetPixelFormat(data->device, pf, &pfd);
			DescribePixelFormat(data->device, pf, sizeof(pfd), &pfd);

			data->context = wglCreateContext(data->device);
			assert(data->context);
			assert(wglMakeCurrent(data->device, data->context));

			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

			checkOpenGlError();

			Debug::Print("OpenGLGraphics::Init Complete\n");
			return true;
		}//bool OpenGLGraphics::init(ISystem*system)

		bool OpenGLGraphics::run(void){
			Debug::Print("OpenGLGraphics::Run Start\n");
			wglMakeCurrent(data->device, data->context);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			checkOpenGlError();

			for (std::shared_ptr<IGfxObject> obj : *data->objects){
				obj->draw();
			}

			checkOpenGlError();

			wglSwapLayerBuffers(data->device, WGL_SWAP_MAIN_PLANE);

			return true;
		}//bool OpenGLGraphics::run(void)

		void OpenGLGraphics::release(void){

			if (data){
				assert(wglMakeCurrent(NULL, NULL));
				assert(wglDeleteContext(data->context));
				assert(ReleaseDC(std::static_pointer_cast<System::WindowsSystem::WindowsSystem>(data->system)->getWindow(), data->device));

				delete data->objects;
				delete data;
				data = nullptr;
			}

		}//void OpenGLGraphics::release(void)


		void OpenGLGraphics::addObject(std::shared_ptr<IGfxObject> obj){
			data->objects->remove(obj);
			data->objects->push_back(obj);
		}//void OpenGLGraphics::addObject(IGfxObject*obj)

		void OpenGLGraphics::removeObject(std::shared_ptr<IGfxObject> obj){
			data->objects->remove(obj);
		}//void OpenGLGraphics::removeObject(IGfxObject*obj)

	}//namespace OpenGL
}//namespace Graphics