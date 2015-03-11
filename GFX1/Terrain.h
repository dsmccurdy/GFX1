#ifndef ___TERRAIN_H___
#define ___TERRAIN_H___

#include <Windows.h>
#include <d3d9.h>

#include "Vector3f.h"
#include "DirectXGraphics.h"
#include "Color4f.h"

namespace Assignments{
	namespace Terrain{

		struct Vertex{
			FLOAT x, y, z;
			FLOAT nx, ny, nz;
			DWORD color;
			FLOAT u, v;
		};//struct Vertex

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;

		class Terrain :
			public Graphics::IGfxObject,
			public std::enable_shared_from_this<Terrain>{
		private:
			std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx;

			LPDIRECT3DVERTEXBUFFER9 vb;
			int size;

			
			Graphics::Material material;

			LPDIRECT3DTEXTURE9 texture;

			unsigned char voxels[128][128][32];

			void generateTerrain(void);

		public:

			Terrain(std::shared_ptr<Graphics::IGraphics>);
			virtual ~Terrain();

			void init(void);
			virtual void draw(void);


		};//class Terrain

	}//namespace Terrain
}//namespace Assignmens


#endif//___TERRAIN_H___