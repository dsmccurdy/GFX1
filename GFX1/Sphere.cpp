#include "Sphere.h"
#include "Debug.h"

#include <d3dx9.h> 
#include <math.h>

namespace Assignments{
	namespace Sphere{

		Sphere::Sphere(std::shared_ptr<Graphics::IGraphics> gfx, Math::Vector3f position, float radius,int hDivision,int vDivisions, Graphics::Color4f color){
			this->gfx = std::static_pointer_cast<Graphics::DirectX::DirectXGraphics>(gfx);

			vb = nullptr;
			type = D3DPT_TRIANGLESTRIP;

			pos = position;
			this->radius = radius;
			this->hDivisions = hDivision;
			this->vDivisions = vDivisions;
			this->color = color;

			material.cullMode = Graphics::CULLMODE_CCW;
			material.lightingEnable = true;
			material.alphaBlendEnable = true;
			material.alphaSourceBlend = Graphics::BLEND_SRC_ALPHA;
			material.alphaDestinationBlend = Graphics::BLEND_INV_SRC_ALPHA;

			
		}//Sphere::Sphere(std::shared_ptr<Graphics::IGraphics>, Math::Vector3f position, float radius,int hDivision,int vDivisions, Graphics::Color4f color)

		Sphere::~Sphere(){
			if (vb){
				vb->Release();
				vb = nullptr;
			}
		}//Sphere::~Sphere()

		void Sphere::init(void){

			HRESULT result;

			result = gfx->getDevice()->CreateVertexBuffer(
				sizeof(Vertex)* (hDivisions*2+2)*vDivisions, D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT,
				&vb, nullptr
				);
			if (FAILED(result)){
				Debug::Print("Error create vertex buffer\n");
			}
			
			Vertex*vertices;

			vb->Lock(0, 0, (void**)&vertices, 0);
			/*
			for (int v = 0; v < vDivisions; v++){
				float r1 = sin( (	((float)v )    / ((float)vDivisions ) )		*D3DX_PI);
				float r2 = sin( (	((float)v + 1) / ((float)vDivisions ) )		*D3DX_PI);
				float y1 = cos( ((float)v) / ((float)vDivisions) * D3DX_PI);
				float y2 = cos(((float)v + 1) / ((float)vDivisions) * D3DX_PI);
				float len = 0;

				for (int h = 0; h < (hDivisions+1); h++){
					float t = ( ((float)h) / ((float)hDivisions) )		* 2.0f * D3DX_PI;
					Vertex*vert = &vertices[ (v*(hDivisions*2 + 2)) + h*2 ];
					vert[0].x = sin(t)*r2*radius;
					vert[0].y = y2*radius;
					vert[0].z = cos(t)*r2*radius;
					len = 1.0f / sqrt((vert[0].x*vert[0].x) + (vert[0].y*vert[0].y) + (vert[0].z*vert[0].z));
					vert[0].nx = vert[0].x * len;
					vert[0].ny = vert[0].y * len;
					vert[0].nz = vert[0].z * len;
					vert[0].color = color.toDirectXColor();
					vert[1].x = sin(t)*r1*radius;
					vert[1].y = y1*radius;
					vert[1].z = cos(t)*r1*radius;
					len = 1.0f / sqrt((vert[1].x*vert[1].x) + (vert[1].y*vert[1].y) + (vert[1].z*vert[1].z));
					vert[1].nx = vert[1].x * len;
					vert[1].ny = vert[1].y * len;
					vert[1].nz = vert[1].z * len;
					vert[1].color = color.toDirectXColor();

				}
			}
			*/
			for (int v = 0; v < vDivisions; v++){
				float r1 = sin((((float)v) / ((float)vDivisions))		*D3DX_PI);
				float r2 = sin((((float)v + 1) / ((float)vDivisions))		*D3DX_PI);
				float y1 = cos(((float)v) / ((float)vDivisions) * D3DX_PI);
				float y2 = cos(((float)v + 1) / ((float)vDivisions) * D3DX_PI);
				float len = 0;

				for (int h = 0; h < (hDivisions + 1); h++){
					float t = (((float)h) / ((float)hDivisions))		* 2.0f * D3DX_PI;
					Vertex*vert = &vertices[(v*(hDivisions * 2 + 2)) + h * 2];
					
					vert[0].x = sin(t)*r1*radius;
					vert[0].y = y1*radius;
					vert[0].z = cos(t)*r1*radius;
					len = 1.0f / sqrt((vert[0].x*vert[0].x) + (vert[0].y*vert[0].y) + (vert[0].z*vert[0].z));
					vert[0].nx = vert[0].x * len;
					vert[0].ny = vert[0].y * len;
					vert[0].nz = vert[0].z * len;
					vert[0].color = color.toDirectXColor();
					
					vert[1].x = sin(t)*r2*radius;
					vert[1].y = y2*radius;
					vert[1].z = cos(t)*r2*radius;
					len = 1.0f / sqrt((vert[1].x*vert[1].x) + (vert[1].y*vert[1].y) + (vert[1].z*vert[1].z));
					vert[1].nx = vert[1].x * len;
					vert[1].ny = vert[1].y * len;
					vert[1].nz = vert[1].z * len;
					vert[1].color = color.toDirectXColor();
					

				}
			}
			vb->Unlock();

		}//void Sphere::init(void)

		void Sphere::draw(void){

			gfx->getDevice()->BeginScene();

			gfx->setMaterial(material);

			D3DXMATRIX world;
			D3DXMatrixTranslation(&world, pos.x,pos.y,pos.z);
			gfx->setWorldMatrix(Math::Matrix(&world.m[0][0]));

			//gfx->getDevice()->SetTexture(0, nullptr);
			gfx->getDevice()->SetVertexDeclaration(nullptr);
			//gfx->getDevice()->SetVertexShader(nullptr);
			//gfx->getDevice()->SetPixelShader(nullptr);
			gfx->getDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));
			gfx->getDevice()->SetFVF(FVF);

			for (int i = 0; i < vDivisions; i++)
				gfx->getDevice()->DrawPrimitive(type, i * (hDivisions*2+2), hDivisions*2);

			gfx->setWorldMatrix(Math::Matrix());

			gfx->getDevice()->EndScene();

		}//void Sphere::draw(void)

	}//namespace Sphere
}//namespace Assignments