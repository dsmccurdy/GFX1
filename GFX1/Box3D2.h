#ifndef ___BOX3D_H___
#define ___BOX3D_H___

#include <Windows.h>
#include <d3d9.h>

#include "Vector3f.h"
#include "DirectXGraphics.h"
#include "Color4f.h"

namespace Assignments{
	namespace Box3D2{

		struct Vertex{
			FLOAT x, y, z;
			FLOAT nx, ny, nz;
			DWORD color;
		};//struct Vertex

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

		class Box3D2 :
			public Graphics::IGfxObject,
			public std::enable_shared_from_this<Box3D2>{
		private:

			std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx;

			LPDIRECT3DINDEXBUFFER9 ib;
			LPDIRECT3DVERTEXBUFFER9 vb;
			int size;
			D3DPRIMITIVETYPE type;

			Math::Vector3f pos;
			Math::Vector3f ext;
			Graphics::Color4f color;

			Graphics::Material material;

		public:

			Box3D2(std::shared_ptr<Graphics::IGraphics>, Math::Vector3f position, Math::Vector3f extents, Graphics::Color4f color);
			virtual ~Box3D2();

			void init(void);
			virtual void draw(void);


		};//class Box3D

	}//namespace Box3D
}//namespace Assignments


#endif//___BOX3D_H___