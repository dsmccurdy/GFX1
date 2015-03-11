#define _USE_MATH_DEFINES
#include <math.h>

#include "Debug.h"
#include "DirectXGraphics.h"
#include "ISystem.h"
#include "Circle2d.h"
#include "IInput.h"


namespace Assignments{
	namespace Circle2D{

		Circle2D::Circle2D(std::shared_ptr<Graphics::IGraphics> gfx, std::shared_ptr<System::ISystem> sys, std::shared_ptr<Input::IInput> input)
			:vb(nullptr)
		{
			this->gfx = std::static_pointer_cast<Graphics::DirectX::DirectXGraphics>(gfx);
			this->system = sys;
			this->input = input;

			
			material.cullMode = Graphics::CULLMODE_NONE;
			material.lightingEnable = false;
			material.alphaBlendEnable = true;
			material.alphaSourceBlend = Graphics::BLEND_SRC_ALPHA;
			material.alphaDestinationBlend = Graphics::BLEND_INV_SRC_ALPHA;

		}//Circle2D::Circle2D(Graphics::IGraphics*gfx, System::ISystem*sys)

		Circle2D::~Circle2D(){
			deleteCircle();

		}//Circle2D::~Circle2D()

		void Circle2D::init(void){

			
			
		}//void Circle2D::init(void)

		void Circle2D::draw(void){

			if (visible){
				if (abs(tx - x) > 0.1f || abs(ty - y) > 0.1f){

					float d = sqrt((tx - x)*(tx - x) + (ty - y)*(ty - y));
					float dx = tx;
					float dy = ty;

					if (d > (velocity / 60)){
						dx = abs(tx - x) / d * (velocity / 60);
						dy = abs(ty - y) / d * (velocity / 60);

						dx = ((tx - x) > 0) ? x + dx : x - dx;
						dy = ((ty - y) > 0) ? y + dy : y - dy;
					}

					move(dx, dy);
				}// if (abs(tx - x) > 0.1f || abs(ty - y) > 0.1f)


				gfx->getDevice()->BeginScene();

				gfx->setMaterial(material);

				gfx->getDevice()->SetTexture(0, nullptr);
				gfx->getDevice()->SetVertexDeclaration(nullptr);
				gfx->getDevice()->SetVertexShader(nullptr);
				gfx->getDevice()->SetPixelShader(nullptr);
				gfx->getDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));
				gfx->getDevice()->SetFVF(FVF);
				gfx->getDevice()->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, divisions);

				gfx->getDevice()->EndScene();
			}//if (visible)

		}//void Circle2D::draw(void)


		bool Circle2D::newCircle(FLOAT x, FLOAT y, FLOAT diameter, int divisions, DWORD color,bool visible){

			deleteCircle();

			this->divisions = divisions;
			this->tx=this->x=x;
			this->ty=this->y=y;
			this->diameter=diameter;
			this->color=color;
			this->visible = visible;

			HRESULT result;

			result = gfx->getDevice()->CreateVertexBuffer(
				sizeof(Vertex)* divisions+2, D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT,
				&vb, nullptr
				);
			if (FAILED(result)){
				Debug::Print("Error create vertex buffer\n");
			}

			
			move(x, y);

			if (input != nullptr){
				input->registerMouseCallback(shared_from_this());
			}

			return true;
		}//bool Circle2D::newCircle(FLOAT x, FLOAT y, FLOAT diameter, int divisions, DWORD color)

		void Circle2D::deleteCircle(void){
			if (vb){
				vb->Release();
				vb = nullptr;
			}
		}//void Circle2D::deleteCircle(void)

		void Circle2D::mouseButtonDown(Input::MouseButton button){
			if (button == Input::MouseButton::LEFT){
				tx = input->mouseX()*((float)system->getWindowWidth());
				ty = input->mouseY()*((float)system->getWindowHeight());

				if (!visible){
					visible = true;
					move(tx, ty);
				}
				
			}
		}//void Circle2D::mouseButtonDown(Input::MouseButton button)

		void Circle2D::move(float x, float y){
			this->x=x;
			this->y=y;

			Vertex*v;

			vb->Lock(0, 0, (void**)&v, 0);

			v[0].x = x;
			v[0].y = y;
			v[0].z = 0.0f;
			v[0].rhw = 1.0f;
			v[0].color = color;



			for (int i = 0; i <= divisions; i++){
				FLOAT t = (((FLOAT)i) / ((FLOAT)divisions))*2.0f*((FLOAT)M_PI);
				v[i + 1].x = x + (diameter/2 * sin(t));
				v[i + 1].y = y - (diameter/2 * cos(t));
				v[i + 1].z = 0.0f;
				v[i + 1].rhw = 1.0f;
				v[i + 1].color = color;
			}

			vb->Unlock();
		}//void Circle2D::move(float x, float y)

	}//namespace Circle2D
}//namespace Assignments