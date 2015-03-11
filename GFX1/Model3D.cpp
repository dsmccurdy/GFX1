#include "Model3D.h"
#include "Debug.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

namespace Assignments{
	namespace Model3D{


		Model3D::Model3D(std::shared_ptr<Graphics::IGraphics> gfx, const std::string str){
			this->gfx = std::static_pointer_cast<Graphics::DirectX::DirectXGraphics>(gfx);

		
			fileName = str;

			material.cullMode = Graphics::CULLMODE_CCW;
			material.lightingEnable = true;
			material.alphaBlendEnable = true;
			material.alphaSourceBlend = Graphics::BLEND_SRC_ALPHA;
			material.alphaDestinationBlend = Graphics::BLEND_INV_SRC_ALPHA;
		}

		Model3D::~Model3D(){

			if (mesh){
				mesh->Release();
				mesh = nullptr;
			}

			for (unsigned int i = 0; i < textures.size(); i++){
				if (textures.at(i)){
					textures.at(i)->Release();
					textures.at(i) = nullptr;
				}
			}

		}

		void Model3D::init(void){

			LPD3DXBUFFER buffer;

			if (FAILED(D3DXLoadMeshFromXA(fileName.c_str(), D3DXMESH_SYSTEMMEM, gfx->getDevice(), nullptr, &buffer, nullptr, &numParts, &mesh))){
				Debug::Print("Error loading mesh");
				return;
			}

			if (buffer == nullptr || buffer->GetBufferPointer() == nullptr || numParts <= 0){
				Debug::Print("Error loading mesh2");
				buffer->Release();
				return;
			}

			
			for (unsigned int i = 0; i<numParts; i++){
				D3DXMATERIAL* xmat = (D3DXMATERIAL*)buffer->GetBufferPointer();
				D3DMATERIAL9 mat;
				mat = xmat[i].MatD3D;
				mat.Ambient = mat.Diffuse;

				LPDIRECT3DTEXTURE9 texture=nullptr;
				if (xmat[i].pTextureFilename && strlen(xmat[i].pTextureFilename)>0){
					

					char str[1024 * 8];
					str[0] = 0;
					//strcat(str, "C:\\Users\\mccur_000\\Documents\\Visual Studio 2013\\Projects\\GFX1\\GFX1\\assets\\");
					strcat(str, "assets\\");
					strcat(str, xmat[i].pTextureFilename);
					if (FAILED(D3DXCreateTextureFromFileA(gfx->getDevice(), str, &texture))){
						Debug::Print("Error loading texture from file\n");
						buffer->Release();
						return;
					}
				}
				textures.push_back(texture);

				mats.push_back(mat);
			}


			
			buffer->Release();

		}

		void Model3D::draw(void){

			D3DMATERIAL9 mat2;

			gfx->getDevice()->BeginScene();

			gfx->setMaterial(material);
			gfx->getDevice()->GetMaterial(&mat2);
			
			
			D3DXMATRIX world,t,r,s;
			D3DXMatrixTranslation(&t, 0.0f, 10.0f, 0.0f);
			D3DXMatrixRotationY(&r, ((float)M_PI)/1.0f);
			D3DXMatrixScaling(&s, 3.25f, 3.25f, 3.25f);

			world = r * t *s;

			gfx->setWorldMatrix(Math::Matrix(&world.m[0][0]));

			for (unsigned int i = 0; i < numParts; i++){
				gfx->getDevice()->SetMaterial(&mats.at(i));
				gfx->getDevice()->SetTexture(0, textures.at(i));
				mesh->DrawSubset(i);
			}
			

			gfx->getDevice()->SetTexture(0, nullptr);
			gfx->getDevice()->SetMaterial(&mat2);

			gfx->getDevice()->EndScene();
		}

	}//namespace Model3D
}//namespace Assignmens