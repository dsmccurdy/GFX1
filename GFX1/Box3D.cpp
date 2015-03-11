#include "Box3D.h"
#include "Debug.h"

#include <d3dx9.h> 

namespace Assignments{
	namespace Box3D{


		Box3D::Box3D(std::shared_ptr<Graphics::IGraphics>gfx, Math::Vector3f position, Math::Vector3f extents, Graphics::Color4f color){
		
			this->gfx = std::static_pointer_cast<Graphics::DirectX::DirectXGraphics>(gfx);
			
			vb = nullptr;
			size = 24;
			type = D3DPT_TRIANGLESTRIP;

			pos = position;
			ext = extents;
			this->color = color;

			material.cullMode = Graphics::CULLMODE_CCW;
			material.lightingEnable = true;
			material.alphaBlendEnable = true;
			material.alphaSourceBlend = Graphics::BLEND_SRC_ALPHA;
			material.alphaDestinationBlend = Graphics::BLEND_INV_SRC_ALPHA;

		}//Box3D::Box3D(std::shared_ptr<Graphics::IGraphics>gfx, Math::Vector3f position, Math::Vector3f extents, Graphics::Color4f color)

		Box3D::~Box3D(){


			if (vb){
				vb->Release();
				vb = nullptr;
			}

			

		}//Box3D::~Box3D()

		void Box3D::init(void){

			HRESULT result;

			result = gfx->getDevice()->CreateVertexBuffer(
				sizeof(Vertex)* size, D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT,
				&vb, nullptr
				);
			if (FAILED(result)){
				Debug::Print("Error create vertex buffer\n");
			}



			Vertex*v;

			vb->Lock(0, 0, (void**)&v, 0);

			const float a[] = { pos.x - ext.x, pos.y + ext.y, pos.z - ext.z };
			const float b[] = { pos.x + ext.x, pos.y + ext.y, pos.z - ext.z };
			const float c[] = { pos.x - ext.x, pos.y - ext.y, pos.z - ext.z };
			const float d[] = { pos.x + ext.x, pos.y - ext.y, pos.z - ext.z };

			const float e[] = { pos.x - ext.x, pos.y + ext.y, pos.z + ext.z };
			const float f[] = { pos.x + ext.x, pos.y + ext.y, pos.z + ext.z };
			const float g[] = { pos.x - ext.x, pos.y - ext.y, pos.z + ext.z };
			const float h[] = { pos.x + ext.x, pos.y - ext.y, pos.z + ext.z };

			const float nfront[] = { 0.0f, 0.0f, -1.0f, 0.0f };
			const float nback[] = { 0.0f, 0.0f, 1.0f, 0.0f };
			const float nleft[] = { -1.0f, 0.0f, 0.0f, 0.0f };
			const float nright[] = { 1.0f, 0.0f, 0.0f, 0.0f };
			const float ntop[] = { 0.0f, 1.0f, 0.0f, 0.0f };
			const float nbottom[] = { 0.0f, -1.0f, 0.0f, 0.0f };


			// Front
			v[0].x = a[0];
			v[0].y = a[1];
			v[0].z = a[2];
			v[0].color = color.toDirectXColor();

			v[1].x = b[0];
			v[1].y = b[1];
			v[1].z = b[2];
			v[1].color = color.toDirectXColor();

			v[2].x = c[0];
			v[2].y = c[1];
			v[2].z = c[2];
			v[2].color = color.toDirectXColor();

			v[3].x = d[0];
			v[3].y = d[1];
			v[3].z = d[2];
			v[3].color = color.toDirectXColor();


			//Right

			v[4].x = b[0];
			v[4].y = b[1];
			v[4].z = b[2];
			v[4].color = color.toDirectXColor();

			v[5].x = f[0];
			v[5].y = f[1];
			v[5].z = f[2];
			v[5].color = color.toDirectXColor();

			v[6].x = d[0];
			v[6].y = d[1];
			v[6].z = d[2];
			v[6].color = color.toDirectXColor();

			v[7].x = h[0];
			v[7].y = h[1];
			v[7].z = h[2];
			v[7].color = color.toDirectXColor();

			// Top

			v[8].x = e[0];
			v[8].y = e[1];
			v[8].z = e[2];
			v[8].color = color.toDirectXColor();

			v[9].x = f[0];
			v[9].y = f[1];
			v[9].z = f[2];
			v[9].color = color.toDirectXColor();

			v[10].x = a[0];
			v[10].y = a[1];
			v[10].z = a[2];
			v[10].color = color.toDirectXColor();

			v[11].x = b[0];
			v[11].y = b[1];
			v[11].z = b[2];
			v[11].color = color.toDirectXColor();

			//Back

			v[12].x = f[0];
			v[12].y = f[1];
			v[12].z = f[2];
			v[12].color = color.toDirectXColor();

			v[13].x = e[0];
			v[13].y = e[1];
			v[13].z = e[2];
			v[13].color = color.toDirectXColor();

			v[14].x = h[0];
			v[14].y = h[1];
			v[14].z = h[2];
			v[14].color = color.toDirectXColor();

			v[15].x = g[0];
			v[15].y = g[1];
			v[15].z = g[2];
			v[15].color = color.toDirectXColor();

			// left

			v[16].x = e[0];
			v[16].y = e[1];
			v[16].z = e[2];
			v[16].color = color.toDirectXColor();

			v[17].x = a[0];
			v[17].y = a[1];
			v[17].z = a[2];
			v[17].color = color.toDirectXColor();

			v[18].x = g[0];
			v[18].y = g[1];
			v[18].z = g[2];
			v[18].color = color.toDirectXColor();

			v[19].x = c[0];
			v[19].y = c[1];
			v[19].z = c[2];
			v[19].color = color.toDirectXColor();


			// bottom

			v[20].x = c[0];
			v[20].y = c[1];
			v[20].z = c[2];
			v[20].color = color.toDirectXColor();

			v[21].x = d[0];
			v[21].y = d[1];
			v[21].z = d[2];
			v[21].color = color.toDirectXColor();

			v[22].x = g[0];
			v[22].y = g[1];
			v[22].z = g[2];
			v[22].color = color.toDirectXColor();

			v[23].x = h[0];
			v[23].y = h[1];
			v[23].z = h[2];
			v[23].color = color.toDirectXColor();

			//front
			for (int i = 0; i < 4; i++){
				v[i].nx = nfront[0];
				v[i].ny = nfront[1];
				v[i].nz = nfront[2];
			}

			//right
			for (int i = 4; i < 8; i++){
				v[i].nx = nright[0];
				v[i].ny = nright[1];
				v[i].nz = nright[2];
			}

			//top
			for (int i = 8; i < 12; i++){
				v[i].nx = ntop[0];
				v[i].ny = ntop[1];
				v[i].nz = ntop[2];
			}

			//back
			for (int i = 12; i < 16; i++){
				v[i].nx = nback[0];
				v[i].ny = nback[1];
				v[i].nz = nback[2];
			}

			//left
			for (int i = 16; i < 20; i++){
				v[i].nx = nleft[0];
				v[i].ny = nleft[1];
				v[i].nz = nleft[2];
			}

			//bottom
			for (int i = 20; i < 24; i++){
				v[i].nx = nbottom[0];
				v[i].ny = nbottom[1];
				v[i].nz = nbottom[2];
			}

			vb->Unlock();

		}//void Box3D::init(void)

		void Box3D::draw(void){

			gfx->getDevice()->BeginScene();

			gfx->setMaterial(material);
			
			//gfx->getDevice()->SetTexture(0, nullptr);
			gfx->getDevice()->SetVertexDeclaration(nullptr);
			//gfx->getDevice()->SetVertexShader(nullptr);
			//gfx->getDevice()->SetPixelShader(nullptr);
			gfx->getDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));
			gfx->getDevice()->SetFVF(FVF);

			for (int i = 0; i < 6; i++)
				gfx->getDevice()->DrawPrimitive(type, i * 4, 2);

			gfx->getDevice()->EndScene();

		}//void Box3D::draw(void)

	}//namespace Box3D
}//namespace Assignments