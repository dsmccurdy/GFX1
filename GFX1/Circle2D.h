#ifndef ___CIRCLE2D_H___
#define ___CIRCLE2D_H___

#include <Windows.h>
#include <d3d9.h>

#include "DirectXGraphics.h"
#include "DirectXFont.h"
#include "IInput.h"
#include "IMouseCallback.h"

namespace Assignments{
	namespace Circle2D{

		struct Vertex{
			FLOAT x, y, z, rhw;
			DWORD color;
		};//struct Vertex

		static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

		class Circle2D : 
			public Graphics::IGfxObject,
			public Input::IMouseCallback,
			public std::enable_shared_from_this<Circle2D>{
		private:

			std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx;
			std::shared_ptr<System::ISystem> system;
			std::shared_ptr<Input::IInput> input;

			LPDIRECT3DVERTEXBUFFER9 vb;
			int divisions;
			float x;
			float y;
			float diameter;
			DWORD color;
			bool visible;

			float tx;
			float ty;
			float velocity = 1000.0f;

			Graphics::Material material;

		public:

			Circle2D(std::shared_ptr<Graphics::IGraphics>, std::shared_ptr<System::ISystem>,std::shared_ptr<Input::IInput>);
			virtual ~Circle2D();

			void init(void);
			virtual void draw(void);

			bool newCircle(FLOAT x, FLOAT y, FLOAT diameter, int divisions, DWORD color,bool visible);
			void deleteCircle(void);

			void move(float x, float y);

			virtual void mouseButtonDown(Input::MouseButton button);
		};//class Circle2D

	}//namespace Circle2D
}//namespace Assignments

#endif//___CIRCLE2D_H___