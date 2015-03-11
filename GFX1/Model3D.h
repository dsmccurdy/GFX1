#ifndef ___MODEL3D_H___
#define ___MODEL3D_H___

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "Vector3f.h"
#include "DirectXGraphics.h"
#include "Color4f.h"

namespace Assignments{
	namespace Model3D{

		struct Vertex{
			FLOAT x, y, z;
			FLOAT nx, ny, nz;
			DWORD color;
			FLOAT u, v;
		};//struct Vertex

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;

		class Model3D :
			public Graphics::IGfxObject,
			public std::enable_shared_from_this<Model3D>{
		private:
			std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx;

			
			Graphics::Material material;

			

			std::string fileName;

			LPD3DXMESH mesh;
			std::vector<D3DMATERIAL9> mats;
			std::vector<LPDIRECT3DTEXTURE9> textures;
			DWORD numParts;

		public:

			Model3D(std::shared_ptr<Graphics::IGraphics>,const std::string str);
			virtual ~Model3D();

			void init(void);
			virtual void draw(void);


		};//class Model3D

	}//namespace Model3D
}//namespace Assignmens


#endif//___MODEL3D_H___