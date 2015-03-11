#include "Terrain.h"
#include "Debug.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

namespace Assignments{
	namespace Terrain{


		Terrain::Terrain(std::shared_ptr<Graphics::IGraphics> gfx){
			this->gfx = std::static_pointer_cast<Graphics::DirectX::DirectXGraphics>(gfx);

			vb = nullptr;
			size = 0;

			material.cullMode = Graphics::CULLMODE_CCW;
			material.lightingEnable = true;
			material.alphaBlendEnable = true;
			material.alphaSourceBlend = Graphics::BLEND_SRC_ALPHA;
			material.alphaDestinationBlend = Graphics::BLEND_INV_SRC_ALPHA;
		}

		Terrain::~Terrain(){

			if (vb){
				vb->Release();
				vb = nullptr;
			}

			if (texture){
				texture->Release();
				texture = nullptr;
			}

		}

		void Terrain::init(void){

			generateTerrain();


			const float a[] = { -0.5f, 0.5f, -0.5f };
			const float b[] = { 0.5f, 0.5f, -0.5f };
			const float c[] = { -0.5f, -0.5f, -0.5f };
			const float d[] = { 0.5f, -0.5f, -0.5f };

			const float e[] = { -0.5f, 0.5f, 0.5f };
			const float f[] = { 0.5f, 0.5f, 0.5f };
			const float g[] = { -0.5f, -0.5f, 0.5f };
			const float h[] = { 0.5f, -0.5f, 0.5f };

			const float nfront[] = { 0.0f, 0.0f, -1.0f, 0.0f };
			const float nback[] = { 0.0f, 0.0f, 1.0f, 0.0f };
			const float nleft[] = { -1.0f, 0.0f, 0.0f, 0.0f };
			const float nright[] = { 1.0f, 0.0f, 0.0f, 0.0f };
			const float ntop[] = { 0.0f, 1.0f, 0.0f, 0.0f };
			const float nbottom[] = { 0.0f, -1.0f, 0.0f, 0.0f };


			Graphics::Color4f color(1.0f, 1.0f, 1.0f, 1.0f);

			float tu1, tv1;
			float tu2, tv2;
			float su1, sv1;
			float su2, sv2;
			float u1, v1;
			float u2, v2;
			
			Vertex*verts = new Vertex[128 * 128 * 32 * 36];
			size = 0;

			float off_x = -64.0f;
			float off_z = -64.0f;
			float off_y = -16.0f;

			for (int x = 0; x < 128; x++){
				for (int z = 0; z < 128; z++){
					for (int y = 0; y < 32; y++){
						if (voxels[x][z][y]>0){
							switch (voxels[x][z][y]){
							default:
							case 1: //grass
								tu1 = 0.0f;
								tv1 = 0.0f;
								tu2 = 0.5f;
								tv2 = 0.5f;
								su1 = 0.5f;
								sv1 = 0.5f;
								su2 = 1.0f;
								sv2 = 1.0f;
								u1 = 0.5f;
								v1 = 0.0f;
								u2 = 1.0f;
								v2 = 0.5f;
								break;
							case 2: //dirt
								su1 = tu1 = u1 = 0.5f;
								sv1 = tv1 = v1 = 0.0f;
								su2 = tu2 = u2 = 1.0f;
								sv2 = tv2 = v2 = 0.5f;
								break;
							case 3://stone
								su1 = tu1 = u1 = 0.0f;
								sv1 = tv1 = v1 = 0.5f;
								su2 = tu2 = u2 = 0.5f;
								sv2 = tv2 = v2 = 1.0f;
							};//switch (voxels[x][z][y])

							Vertex*v=&verts[size*36];

							// Front
							v[0].x = off_x + a[0];
							v[0].y = off_y + a[1];
							v[0].z = off_z + a[2];
							v[0].color = color.toDirectXColor();
							v[0].u = su1;
							v[0].v = sv1;

							v[1].x = off_x + b[0];
							v[1].y = off_y + b[1];
							v[1].z = off_z + b[2];
							v[1].color = color.toDirectXColor();
							v[1].u = su2;
							v[1].v = sv1;

							v[2].x = off_x + c[0];
							v[2].y = off_y + c[1];
							v[2].z = off_z + c[2];
							v[2].color = color.toDirectXColor();
							v[2].u = su1;
							v[2].v = sv2;

							v[3].x = off_x + b[0];
							v[3].y = off_y + b[1];
							v[3].z = off_z + b[2];
							v[3].color = color.toDirectXColor();
							v[3].u = su2;
							v[3].v = sv1;

							v[4].x = off_x + d[0];
							v[4].y = off_y + d[1];
							v[4].z = off_z + d[2];
							v[4].color = color.toDirectXColor();
							v[4].u = su2;
							v[4].v = sv2;

							v[5].x = off_x + c[0];
							v[5].y = off_y + c[1];
							v[5].z = off_z + c[2];
							v[5].color = color.toDirectXColor();
							v[5].u = su1;
							v[5].v = sv2;

							

							//Right

							v[6].x = off_x + b[0];
							v[6].y = off_y + b[1];
							v[6].z = off_z + b[2];
							v[6].color = color.toDirectXColor();
							v[6].u = su1;
							v[6].v = sv1;

							v[7].x = off_x + f[0];
							v[7].y = off_y + f[1];
							v[7].z = off_z + f[2];
							v[7].color = color.toDirectXColor();
							v[7].u = su2;
							v[7].v = sv1;

							v[8].x = off_x + d[0];
							v[8].y = off_y + d[1];
							v[8].z = off_z + d[2];
							v[8].color = color.toDirectXColor();
							v[8].u = su1;
							v[8].v = sv2;

							v[9].x = off_x + f[0];
							v[9].y = off_y + f[1];
							v[9].z = off_z + f[2];
							v[9].color = color.toDirectXColor();
							v[9].u = su2;
							v[9].v = sv1;

							v[10].x = off_x + h[0];
							v[10].y = off_y + h[1];
							v[10].z = off_z + h[2];
							v[10].color = color.toDirectXColor();
							v[10].u = su2;
							v[10].v = sv2;

							v[11].x = off_x + d[0];
							v[11].y = off_y + d[1];
							v[11].z = off_z + d[2];
							v[11].color = color.toDirectXColor();
							v[11].u = su1;
							v[11].v = sv2;

							
							// Top

							v[12].x = off_x + e[0];
							v[12].y = off_y + e[1];
							v[12].z = off_z + e[2];
							v[12].color = color.toDirectXColor();
							v[12].u = tu1;
							v[12].v = tv1;

							v[13].x = off_x + f[0];
							v[13].y = off_y + f[1];
							v[13].z = off_z + f[2];
							v[13].color = color.toDirectXColor();
							v[13].u = tu2;
							v[13].v = tv1;

							v[14].x = off_x + a[0];
							v[14].y = off_y + a[1];
							v[14].z = off_z + a[2];
							v[14].color = color.toDirectXColor();
							v[14].u = tu1;
							v[14].v = tv2;

							v[15].x = off_x + f[0];
							v[15].y = off_y + f[1];
							v[15].z = off_z + f[2];
							v[15].color = color.toDirectXColor();
							v[15].u = tu2;
							v[15].v = tv1;

							v[16].x = off_x + b[0];
							v[16].y = off_y + b[1];
							v[16].z = off_z + b[2];
							v[16].color = color.toDirectXColor();
							v[16].u = tu2;
							v[16].v = tv2;

							v[17].x = off_x + a[0];
							v[17].y = off_y + a[1];
							v[17].z = off_z + a[2];
							v[17].color = color.toDirectXColor();
							v[17].u = tu1;
							v[17].v = tv2;

							

							//Back

							v[18].x = off_x + f[0];
							v[18].y = off_y + f[1];
							v[18].z = off_z + f[2];
							v[18].color = color.toDirectXColor();
							v[18].u = su1;
							v[18].v = sv1;

							v[19].x = off_x + e[0];
							v[19].y = off_y + e[1];
							v[19].z = off_z + e[2];
							v[19].color = color.toDirectXColor();
							v[19].u = su2;
							v[19].v = sv1;

							v[20].x = off_x + h[0];
							v[20].y = off_y + h[1];
							v[20].z = off_z + h[2];
							v[20].color = color.toDirectXColor();
							v[20].u = su1;
							v[20].v = sv2;

							v[21].x = off_x + e[0];
							v[21].y = off_y + e[1];
							v[21].z = off_z + e[2];
							v[21].color = color.toDirectXColor();
							v[21].u = su2;
							v[21].v = sv1;

							v[22].x = off_x + g[0];
							v[22].y = off_y + g[1];
							v[22].z = off_z + g[2];
							v[22].color = color.toDirectXColor();
							v[22].u = su2;
							v[22].v = sv2;

							v[23].x = off_x + h[0];
							v[23].y = off_y + h[1];
							v[23].z = off_z + h[2];
							v[23].color = color.toDirectXColor();
							v[23].u = su1;
							v[23].v = sv2;

							
							// left

							v[24].x = off_x + e[0];
							v[24].y = off_y + e[1];
							v[24].z = off_z + e[2];
							v[24].color = color.toDirectXColor();
							v[24].u = su1;
							v[24].v = sv1;

							v[25].x = off_x + a[0];
							v[25].y = off_y + a[1];
							v[25].z = off_z + a[2];
							v[25].color = color.toDirectXColor();
							v[25].u = su2;
							v[25].v = sv1;

							v[26].x = off_x + g[0];
							v[26].y = off_y + g[1];
							v[26].z = off_z + g[2];
							v[26].color = color.toDirectXColor();
							v[26].u = su1;
							v[26].v = sv2;

							v[27].x = off_x + a[0];
							v[27].y = off_y + a[1];
							v[27].z = off_z + a[2];
							v[27].color = color.toDirectXColor();
							v[27].u = su2;
							v[27].v = sv1;

							v[28].x = off_x + c[0];
							v[28].y = off_y + c[1];
							v[28].z = off_z + c[2];
							v[28].color = color.toDirectXColor();
							v[28].u = su2;
							v[28].v = sv2;

							v[29].x = off_x + g[0];
							v[29].y = off_y + g[1];
							v[29].z = off_z + g[2];
							v[29].color = color.toDirectXColor();
							v[29].u = su1;
							v[29].v = sv2;

							

							// bottom

							v[30].x = off_x + c[0];
							v[30].y = off_y + c[1];
							v[30].z = off_z + c[2];
							v[30].color = color.toDirectXColor();
							v[30].u = u1;
							v[30].v = v1;

							v[31].x = off_x + d[0];
							v[31].y = off_y + d[1];
							v[31].z = off_z + d[2];
							v[31].color = color.toDirectXColor();
							v[31].u = u2;
							v[31].v = v1;

							v[32].x = off_x + g[0];
							v[32].y = off_y + g[1];
							v[32].z = off_z + g[2];
							v[32].color = color.toDirectXColor();
							v[32].u = u1;
							v[32].v = v2;

							v[33].x = off_x + d[0];
							v[33].y = off_y + d[1];
							v[33].z = off_z + d[2];
							v[33].color = color.toDirectXColor();
							v[33].u = u2;
							v[33].v = v1;

							v[34].x = off_x + h[0];
							v[34].y = off_y + h[1];
							v[34].z = off_z + h[2];
							v[34].color = color.toDirectXColor();
							v[34].u = u2;
							v[34].v = v2;

							v[35].x = off_x + g[0];
							v[35].y = off_y + g[1];
							v[35].z = off_z + g[2];
							v[35].color = color.toDirectXColor();
							v[35].u = u1;
							v[35].v = v2;

							//front
							for (int i = 0; i < 6; i++){
								v[i].nx = nfront[0];
								v[i].ny = nfront[1];
								v[i].nz = nfront[2];
							}

							//right
							for (int i = 6; i < 12; i++){
								v[i].nx = nright[0];
								v[i].ny = nright[1];
								v[i].nz = nright[2];
							}

							//top
							for (int i = 12; i < 18; i++){
								v[i].nx = ntop[0];
								v[i].ny = ntop[1];
								v[i].nz = ntop[2];
							}

							//back
							for (int i = 18; i < 24; i++){
								v[i].nx = nback[0];
								v[i].ny = nback[1];
								v[i].nz = nback[2];
							}

							//left
							for (int i = 24; i < 30; i++){
								v[i].nx = nleft[0];
								v[i].ny = nleft[1];
								v[i].nz = nleft[2];
							}

							//bottom
							for (int i = 30; i < 36; i++){
								v[i].nx = nbottom[0];
								v[i].ny = nbottom[1];
								v[i].nz = nbottom[2];
							}

							size++;
						}
						off_y += 1.0f;
					}
					off_z += 1.0f;
					off_y = -16.0f;
				}
				off_x += 1.0f;
				off_z = -64.0f;
			}



			
			HRESULT result;

			result = gfx->getDevice()->CreateVertexBuffer(
				sizeof(Vertex)* size*36, D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT,
				&vb, nullptr
				);
			if (FAILED(result)){
				Debug::Print("Error create vertex buffer\n");
			}

			Vertex*v;
			result=vb->Lock(0, 0, (void**)&v, 0);
			memcpy(v, verts, sizeof(Vertex)*size*36);
			vb->Unlock();

			
			D3DXIMAGE_INFO info;
			//if (FAILED(D3DXGetImageInfoFromFileA("C:\\Users\\mccur_000\\Documents\\Visual Studio 2013\\Projects\\GFX1\\GFX1\\assets\\stuff.png", &info))){
			if (FAILED(D3DXGetImageInfoFromFileA("assets\\stuff.png", &info))){
				Debug::Print("Error loading image info\n");
				return;
			}

			//if (FAILED(D3DXCreateTextureFromFileA(gfx->getDevice(), "C:\\Users\\mccur_000\\Documents\\Visual Studio 2013\\Projects\\GFX1\\GFX1\\assets\\stuff.png", &texture))){
			if (FAILED(D3DXCreateTextureFromFileA(gfx->getDevice(), "assets\\stuff.png", &texture))){
				Debug::Print("Error loading texture from file\n");
				return;
			}


			delete[]verts;
		}
		
		void Terrain::draw(void){
			gfx->getDevice()->BeginScene();

			gfx->setMaterial(material);

			gfx->getDevice()->SetTexture(0, texture);
			gfx->getDevice()->SetVertexDeclaration(nullptr);
			//gfx->getDevice()->SetVertexShader(nullptr);
			//gfx->getDevice()->SetPixelShader(nullptr);
			gfx->getDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));
			gfx->getDevice()->SetFVF(FVF);
			
			D3DXMATRIX world, t, r, s;
			D3DXMatrixTranslation(&t, 0.0f, 0.0f, 0.0f);
			D3DXMatrixRotationY(&r, ((float)M_PI) / 1.0f * 0.0f);
			D3DXMatrixScaling(&s, 1.0f, 1.0f, 1.0f);

			world = r * t *s;

			gfx->setWorldMatrix(Math::Matrix(&world.m[0][0]));

			gfx->getDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, size*12);

			gfx->getDevice()->SetTexture(0, nullptr);

			gfx->getDevice()->EndScene();
		}

		void Terrain::generateTerrain(void){
			
			for (int x = 0; x < 128; x++){
				


				for (int z = 0; z < 128; z++){
					float h1 = sinf(sqrtf((float)((x - 56)*(x - 56) + (z + 77)*(z + 77))) *((float)M_PI) *0.01f);
					float h2 = sinf(sqrtf((float)((x +199)*(x +199) + (z - 88)*(z - 88))) *((float)M_PI) *.00556f);
					float h3 = cosf( sqrtf((float)((x-331)*(x-331 )+(z-122)*(z-122))) * ((float)M_PI) * 0.0762f);
					
					int h = (int)((h1 * 7.0f) + (h2 * 5.71f) + (h3 * 1.39f) + 15.0f);

					h = (h< 1) ? 1 : h;

					for (int y = 0; y < 32; y++){
						if (y < h){
							voxels[x][z][y] = 2;
						}
						else if (y == h){
							voxels[x][z][y] = 1;
						}
						else{
							voxels[x][z][y] = 0;
						}
					}
				}
			}
		}


	}//namespace Terrain
}//namespace Assignmens