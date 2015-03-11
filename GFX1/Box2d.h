#ifndef ___BOX2D_H___
#define ___BOX2D_H___

#include <Windows.h>
#include <d3d9.h>

#include "DirectXGraphics.h"
#include "ISystem.h"

#include "IGfxObject.h"

namespace Assignments{
	namespace Box2D{

		struct Box2DVertex{
			FLOAT x, y, z, rhw;
			DWORD color;
		};//struct Box2DVertex

		static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

		class Box2D : public Graphics::IGfxObject{
		private:
			
			std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx;
			std::shared_ptr<System::ISystem> system;

			LPDIRECT3DVERTEXBUFFER9 vb;

			FLOAT width, height;
			DWORD color;

			FLOAT xv, yv;
			FLOAT x, y;

			Graphics::Material material;

		public:

			Box2D(std::shared_ptr<Graphics::IGraphics>, std::shared_ptr<System::ISystem>);
			virtual ~Box2D();

			void init(void);
			virtual void draw(void);

			bool newBox(FLOAT x, FLOAT y, FLOAT width, FLOAT height, DWORD color);
			void deleteBox(void);

			void moveBox(FLOAT x, FLOAT y);
			void moveBox(FLOAT x, FLOAT y, FLOAT width, FLOAT height, DWORD color);

			void setVelocity(FLOAT xv, FLOAT yv);

		};//class Box2D

	}//namespace Box2D
}//namespace Assignments

#endif//___BOX2D_H___