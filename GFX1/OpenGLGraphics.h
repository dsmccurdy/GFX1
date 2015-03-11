#ifndef ___OPENGLGRAPHICS_H___
#define ___OPENGLGRAPHICS_H___

#include "IGraphics.h"
#include "ISystem.h"

namespace Graphics{
	namespace OpenGL{

		struct OpenGLGraphicsData;
		class OpenGLGraphics : 
			public IGraphics,
			public std::enable_shared_from_this<OpenGLGraphics>{
		private:

			OpenGLGraphicsData*data;

		public:

			OpenGLGraphics();
			virtual ~OpenGLGraphics();

			bool init(std::shared_ptr<System::ISystem>);
			bool run(void);
			void release(void);

			virtual void addObject(std::shared_ptr<IGfxObject>obj);
			virtual	void removeObject(std::shared_ptr<IGfxObject> obj);

		};//class OpenGLGraphics


		void _checkOpenGlError(const char* file, const long line);
		#define checkOpenGlError() _checkOpenGlError(__FILE__,__LINE__);

	}//namesapce OpenGL
}//namespace Graphics

#endif//___OPENGLGRAPHICS_H___