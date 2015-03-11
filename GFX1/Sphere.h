#ifndef ___SPHERE_H___
#define ___SPHERE_H___

#include <Windows.h>
#include <d3d9.h>

#include "Vector3f.h"
#include "DirectXGraphics.h"
#include "Color4f.h"

namespace Assignments{

	namespace Sphere{

		struct Vertex{
			FLOAT x, y, z;
			FLOAT nx, ny, nz;
			DWORD color;
		};//struct Vertex

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

		class Sphere:
			public Graphics::IGfxObject,
			public std::enable_shared_from_this<Sphere>{

		private:
			std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx;

			LPDIRECT3DVERTEXBUFFER9 vb;
			D3DPRIMITIVETYPE type;

			Math::Vector3f pos;
			float radius;
			int hDivisions;
			int vDivisions;
			Graphics::Color4f color;

			Graphics::Material material;

		public:

			Sphere(std::shared_ptr<Graphics::IGraphics>, Math::Vector3f position, float radius, int hDivisions, int vDivisions, Graphics::Color4f color);
			virtual ~Sphere();

			void init(void);
			virtual void draw(void);

		};

	}//namespace Sphere

}//namespace Assignments

#endif//___SPHERE_H___