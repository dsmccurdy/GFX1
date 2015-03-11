
#include "Debug.h"
#include "DirectXGraphics.h"
#include "ISystem.h"
#include "Box2d.h"


namespace Assignments{
	namespace Box2D{

		Box2D::Box2D(std::shared_ptr<Graphics::IGraphics> gfx, std::shared_ptr<System::ISystem> sys)
			:vb(nullptr)
		{
			this->gfx = std::static_pointer_cast<Graphics::DirectX::DirectXGraphics>(gfx);
			this->system = sys;

			xv = yv = 0.0f;

			material.cullMode = Graphics::CULLMODE_NONE;
			material.lightingEnable = false;
			material.alphaBlendEnable = true;
			material.alphaSourceBlend = Graphics::BLEND_SRC_ALPHA;
			material.alphaDestinationBlend = Graphics::BLEND_INV_SRC_ALPHA;

			newBox(32.0f, 64.0f, 128.0f, 256.0f, D3DCOLOR_ARGB(0x70, 0xff, 0x00, 0x00));

		}//Box2D::Box2D(Graphics::IGraphics*gfx, System::ISystem*sys)
		
		Box2D::~Box2D(){
			deleteBox();
		}//Box2D::~Box2D()

		void Box2D::init(void){

		}//void Box2D::init(void)

		void Box2D::draw(void){

			moveBox(x + xv, y + yv);
			
			if (x<0 || x > 500) xv *= -1;
			if (y<0 || y > 500) yv *= -1;

			gfx->getDevice()->BeginScene();

			gfx->setMaterial(material);

			gfx->getDevice()->SetTexture(0, nullptr);
			gfx->getDevice()->SetVertexDeclaration(nullptr);
			gfx->getDevice()->SetVertexShader(nullptr);
			gfx->getDevice()->SetPixelShader(nullptr);
			gfx->getDevice()->SetStreamSource(0, vb,0, sizeof(Box2DVertex));
			gfx->getDevice()->SetFVF(FVF);
			gfx->getDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);

			gfx->getDevice()->EndScene();

		}//void Box2D::draw(void)

		void Box2D::moveBox(FLOAT x, FLOAT y){

			this->x = x;
			this->y = y;

			Box2DVertex*v;

			vb->Lock(0, 0, (void**)&v, 0);

			v[0].x = x;
			v[0].y = y;
			v[0].z = 0.0f;
			v[0].rhw = 1.0f;
			v[0].color = color;

			v[1].x = x + width;
			v[1].y = y;
			v[1].z = 0.0f;
			v[1].rhw = 1.0f;
			v[1].color = color;

			v[2].x = x;
			v[2].y = y + height;
			v[2].z = 0.0f;
			v[2].rhw = 1.0f;
			v[2].color = color;

			v[3].x = x + width;
			v[3].y = y + height;
			v[3].z = 0.0f;
			v[3].rhw = 1.0f;
			v[3].color = color;

			vb->Unlock();

		}

		void Box2D::moveBox(FLOAT x, FLOAT y, FLOAT width, FLOAT height, DWORD color){
			this->width = width;
			this->height = height;
			this->color = color;
			moveBox(x, y);
		}

		void Box2D::setVelocity(FLOAT xv, FLOAT yv){
			this->xv = xv;
			this->yv = yv;
		}

		bool Box2D::newBox(FLOAT x, FLOAT y, FLOAT width, FLOAT height, DWORD color){

			this->width=width;
			this->height = height;
			this->color = color;

			deleteBox();

			HRESULT result;

			result = gfx->getDevice()->CreateVertexBuffer(
				sizeof(Box2DVertex)*4, D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT,
				&vb, nullptr
				);
			if (FAILED(result)){
				Debug::Print("Error create vertex buffer\n");
			}

			moveBox(x, y);

			return true;
		}//bool Box2D::newBox(FLOAT x, FLOAT y, FLOAT width, FLOAT height, DWORD color)

		void Box2D::deleteBox(void){
			if (vb){
				vb->Release();
				vb = nullptr;
			}
		}//void Box2D::deleteBox(void)
		
	}//namespace Box2D
}//namespace Assignments