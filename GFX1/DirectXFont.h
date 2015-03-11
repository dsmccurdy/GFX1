#ifndef ___DIRECTXFONT_H___
#define ___DIRECTXFONT_H___

#include <d3dx9.h> 


#include "DirectXGraphics.h"
#include "ISystem.h"

namespace Graphics{
	namespace DirectX{


		struct FontData;
		class Font{
		private:

			FontData*data;

		public:

			Font(std::shared_ptr<DirectXGraphics>gfx, std::shared_ptr<System::ISystem>sys);
			virtual ~Font();

			bool init(const std::string& name, int size);
			void release(void);

			void Draw(const std::string& str, int x, int y,DWORD color);
		};
	}
}


#endif//___DIRECTXFONT_H___