#include "Box3D2.h"
#include "Debug.h"

#include <d3dx9.h> 

namespace Assignments{
	namespace Box3D2{


		Box3D2::Box3D2(std::shared_ptr<Graphics::IGraphics>gfx, Math::Vector3f position, Math::Vector3f extents, Graphics::Color4f color){

			this->gfx = std::static_pointer_cast<Graphics::DirectX::DirectXGraphics>(gfx);

			ib = nullptr;
			vb = nullptr;
			size = 8;
			type = D3DPT_TRIANGLESTRIP;

			pos = position;
			ext = extents;
			this->color = color;

			material.cullMode = Graphics::CULLMODE_CCW;
			material.lightingEnable = true;
			material.alphaBlendEnable = true;
			material.alphaSourceBlend = Graphics::BLEND_SRC_ALPHA;
			material.alphaDestinationBlend = Graphics::BLEND_INV_SRC_ALPHA;

		}//Box3D2::Box3D2(std::shared_ptr<Graphics::IGraphics>gfx, Math::Vector3f position, Math::Vector3f extents, Graphics::Color4f color)

		Box3D2::~Box3D2(){


			if (ib){
				ib->Release();
				ib = nullptr;
			}

			if (vb){
				vb->Release();
				vb = nullptr;
			}



		}//Box3D2::~Box3D2()

		void Box3D2::init(void){

			HRESULT result;

			result = gfx->getDevice()->CreateVertexBuffer(
				sizeof(Vertex)* size, D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT,
				&vb, nullptr
				);
			if (FAILED(result)){
				Debug::Print("Error create vertex buffer\n");
			}

			result = gfx->getDevice()->CreateIndexBuffer(
				sizeof(short)* 24, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, nullptr
				);
			if (FAILED(result)){
				Debug::Print("Error create index buffer\n");
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


			//Back

			v[4].x = e[0];
			v[4].y = e[1];
			v[4].z = e[2];
			v[4].color = color.toDirectXColor();

			v[5].x = f[0];
			v[5].y = f[1];
			v[5].z = f[2];
			v[5].color = color.toDirectXColor();

			v[6].x = g[0];
			v[6].y = g[1];
			v[6].z = g[2];
			v[6].color = color.toDirectXColor();

			v[7].x = h[0];
			v[7].y = h[1];
			v[7].z = h[2];
			v[7].color = color.toDirectXColor();

			//front
			for (int i = 0; i < 4; i++){
				v[i].nx = nfront[0];
				v[i].ny = nfront[1];
				v[i].nz = nfront[2];
			}

			//back
			for (int i = 4; i < 8; i++){
				v[i].nx = nback[0];
				v[i].ny = nback[1];
				v[i].nz = nback[2];
			}


			vb->Unlock();

			short*ind;
			ib->Lock(0, 0, (void**)&ind, 0);

			ind[0] = 0;
			ind[1] = 1;
			ind[2] = 2;
			ind[3] = 3;

			ind[4] = 1;
			ind[5] = 5;
			ind[6] = 3;
			ind[7] = 7;

			ind[8] = 4;
			ind[9] = 5;
			ind[10] = 0;
			ind[11] = 1;

			ind[12] = 5;
			ind[13] = 4;
			ind[14] = 7;
			ind[15] = 6;

			ind[16] = 4;
			ind[17] = 0;
			ind[18] = 6;
			ind[19] = 2;

			ind[20] = 2;
			ind[21] = 3;
			ind[22] = 6;
			ind[23] = 7;

			ib->Unlock();

		}//void Box3D2::init(void)

		void Box3D2::draw(void){

			gfx->getDevice()->BeginScene();

			gfx->setMaterial(material);

			//gfx->getDevice()->SetTexture(0, nullptr);
			gfx->getDevice()->SetVertexDeclaration(nullptr);
			//gfx->getDevice()->SetVertexShader(nullptr);
			//gfx->getDevice()->SetPixelShader(nullptr);
			gfx->getDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));
			gfx->getDevice()->SetFVF(FVF);

			gfx->getDevice()->SetIndices(ib);

			for (int i = 0; i < 6; i++)
				gfx->getDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 8, i * 4, 2);

			gfx->getDevice()->EndScene();

		}//void Box3D2::draw(void)

	}//namespace Box3D2
}//namespace Assignments