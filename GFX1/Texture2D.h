#ifndef ___TEXTURE2D_H___
#define ___TEXTURE2D_H___

#include <Windows.h>
#include <d3d9.h>
#include <string>

#include "Vector3f.h"
#include "DirectXGraphics.h"
#include "Color4f.h"


namespace Assignments{
	namespace Texture2D{


		struct Vertex{
			FLOAT x, y, z, w;
			DWORD color;
			FLOAT u, v;
		};//struct Vertex

		static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

		class Texture2D :
			public Graphics::IGfxObject,
			public std::enable_shared_from_this<Texture2D>{

		private:

			std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx;

			LPDIRECT3DVERTEXBUFFER9 vb;
			D3DPRIMITIVETYPE type;

			LPDIRECT3DTEXTURE9 texture;

			float x, y;

			Graphics::Material material;

			std::string fileName;

		public:

			Texture2D(std::shared_ptr<Graphics::IGraphics> gfx,std::string fileName, float x,float y);
			virtual ~Texture2D();

			void init(void);
			virtual void draw(void);
		};


	}//namespace Texture2D
}//namesapce Assignments


#endif//___TEXTURE2D_H___