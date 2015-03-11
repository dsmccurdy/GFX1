#ifndef ___JUNK_H___
#define ___JUNK_H___

#include <Windows.h>
#include <d3d9.h>

#include "DirectXGraphics.h"
#include "DirectXFont.h"
#include "IInput.h"
#include "IMouseCallback.h"
#include "DirectXFPSCamera.h"

#include "Model3D.h"

namespace Assignments{
	namespace Junk{

		struct Vertex{
			FLOAT x, y, z;
			FLOAT nx, ny, nz;
			DWORD color;
		};//struct Vertex

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

		class Junk :
			public Graphics::IGfxObject,
			public Input::IMouseCallback,
			public Input::IKeyCallback,
			public std::enable_shared_from_this<Junk>{
		private:

			std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx;
			std::shared_ptr<System::ISystem> system;
			std::shared_ptr<Input::IInput> input;

			std::shared_ptr<Graphics::DirectX::FpsCamera> camera;

			LPDIRECT3DVERTEXBUFFER9 vb;
			int size;
			D3DPRIMITIVETYPE type;

			float theta;

			Graphics::Material material;

			LPD3DXMESH mesh;

			//Graphics::DirectX::Font font;


			float hSpeed;
			float vSpeed;
			float rSpeed;
			float freeFloat;

			float mouse_x;
			float mouse_y;
			

		public:

			Junk(std::shared_ptr<Graphics::IGraphics>, std::shared_ptr<System::ISystem>, std::shared_ptr<Input::IInput>);
			virtual ~Junk();

			void setupLighting(void);

			void init(void);
			virtual void draw(void);

			virtual void keyDownCallback(Input::VKEY::VKEY key);
			virtual void mouseMove(float x, float y);

		};//class Junk

	}//namespace Junk
}//namespace Assignments

#endif//___JUNK_H___