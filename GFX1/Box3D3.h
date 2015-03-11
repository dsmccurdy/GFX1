#ifndef ___BOX3D3_H___
#define ___BOX3D3_H___

#include <Windows.h>
#include <d3d9.h>

#include "Vector3f.h"
#include "DirectXGraphics.h"
#include "Color4f.h"

namespace Assignments{
	namespace Box3D3{

		struct Vertex{
			FLOAT x, y, z;
			FLOAT nx, ny, nz;
			DWORD color;
			FLOAT u, v;
		};//struct Vertex

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;

		class Box3D3 :
			public Graphics::IGfxObject,
			public std::enable_shared_from_this<Box3D3>{
		private:

			std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx;

			LPDIRECT3DVERTEXBUFFER9 vb;
			int size;
			D3DPRIMITIVETYPE type;
			int boxType;

			Math::Vector3f pos;
			Math::Vector3f ext;

			Graphics::Material material;

			LPDIRECT3DTEXTURE9 texture;

		public:

			Box3D3(std::shared_ptr<Graphics::IGraphics>, Math::Vector3f position, Math::Vector3f extents, int boxType);
			virtual ~Box3D3();

			void init(void);
			virtual void draw(void);


		};//class Box3D3

	}//namespace Box3D3
}//namespace Assignments


#endif//___BOX3D3_H___