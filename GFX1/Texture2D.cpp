#include "Texture2D.h"
#include "Debug.h"

#include <d3dx9.h>


namespace Assignments{
	namespace Texture2D{

		Texture2D::Texture2D(std::shared_ptr<Graphics::IGraphics>gfx,std::string fileName,float x,float y){
			this->gfx = std::static_pointer_cast<Graphics::DirectX::DirectXGraphics>(gfx);

			texture = nullptr;
			vb = nullptr;
			type = D3DPT_TRIANGLESTRIP;

			this->x = x;
			this->y = y;
			this->fileName = fileName;

			material.cullMode = Graphics::CULLMODE_NONE;
			material.lightingEnable = false;
			material.alphaBlendEnable = true;
			material.alphaSourceBlend = Graphics::BLEND_SRC_ALPHA;
			material.alphaDestinationBlend = Graphics::BLEND_INV_SRC_ALPHA;
		}

		Texture2D::~Texture2D(){
			if (vb){
				vb->Release();
				vb = nullptr;
			}
			if (texture){
				texture->Release();
				texture = nullptr;
			}
		}


		void Texture2D::init(void){

			HRESULT result;

			result = gfx->getDevice()->CreateVertexBuffer( sizeof(Vertex)*4 , D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT,
				&vb, nullptr
				);
			if (FAILED(result)){
				Debug::Print("Error create vertex buffer\n");
			}

			Vertex*v;

			D3DXIMAGE_INFO info;
			if (FAILED(D3DXGetImageInfoFromFileA(fileName.c_str(), &info))){
				Debug::Print("Error loading image info\n");
				return;
			}

			if (FAILED(D3DXCreateTextureFromFileA(gfx->getDevice(), fileName.c_str(), &texture))){
				Debug::Print("Error loading texture from file\n");
				return;
			}

			vb->Lock(0, 0, (void**)&v, 0);


			float height = (float)info.Height;
			float width = (float)info.Width;
			DWORD color = D3DCOLOR_ARGB(255,255,255,255);

			v[0].x = x;
			v[0].y = y;
			v[0].z = 0.0f;
			v[0].w = 0.0f;
			v[0].color = color;
			v[0].u = 0.0f;
			v[0].v = 0.0f;

			v[1].x = x + width;
			v[1].y = y;
			v[1].z = 0.0f;
			v[1].w = 0.0f;
			v[1].color = color;
			v[1].u = 1.0f;
			v[1].v = 0.0f;

			v[2].x = x;
			v[2].y = y + height;
			v[2].z = 0.0f;
			v[2].w = 0.0f;
			v[2].color = color;
			v[2].u = 0.0f;
			v[2].v = 1.0f;

			v[3].x = x + width;
			v[3].y = y + height;
			v[3].z = 0.0f;
			v[3].w = 0.0f;
			v[3].color = color;
			v[3].u = 1.0f;
			v[3].v = 1.0f;

			vb->Unlock();
		}

		void Texture2D::draw(void){
			gfx->getDevice()->BeginScene();

			gfx->setMaterial(material);

			gfx->getDevice()->SetTexture(0, texture);
			gfx->getDevice()->SetVertexDeclaration(nullptr);
			//gfx->getDevice()->SetVertexShader(nullptr);
			//gfx->getDevice()->SetPixelShader(nullptr);
			gfx->getDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));
			gfx->getDevice()->SetFVF(FVF);

			gfx->getDevice()->DrawPrimitive(type, 0, 2);

			gfx->getDevice()->SetTexture(0, nullptr);
			gfx->getDevice()->EndScene();

		}

	}//namespace Texture2D
}//namespace Assignments