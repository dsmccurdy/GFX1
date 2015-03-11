#define _USE_MATH_DEFINES
#include <math.h>

#include "Debug.h"
#include "DirectXGraphics.h"
#include "ISystem.h"
#include "Junk.h"
#include "IInput.h"

#include "Box3D.h"
#include "Box3D3.h"
#include "Sphere.h"
#include "Terrain.h"

#include "IWorkUnit.h"


const float GROUND_HSPEED = 25.0f / 60.0f;
const float GROUND_VSPEED = 15.0f / 60.0f;
const float GROUND_RSPEED = 15.0f;

const float AIR_HSPEED = 50.0f / 60.0f;
const float AIR_VSPEED = 35.0f / 60.0f;
const float AIR_RSPEED = GROUND_RSPEED;

namespace Assignments{
	namespace Junk{

		Junk::Junk(std::shared_ptr<Graphics::IGraphics> gfx, std::shared_ptr<System::ISystem> sys, std::shared_ptr<Input::IInput> input)
			:vb(nullptr),
			mesh(nullptr)
		{
			this->gfx = std::static_pointer_cast<Graphics::DirectX::DirectXGraphics>(gfx);
			this->system = sys;
			this->input = input;

			hSpeed = GROUND_HSPEED;
			vSpeed = GROUND_VSPEED;
			rSpeed = GROUND_RSPEED;
			freeFloat = true;

			theta = 0.0f;

			material.cullMode = Graphics::CULLMODE_NONE;
			material.lightingEnable = true;
			material.alphaBlendEnable = true;
			material.alphaSourceBlend = Graphics::BLEND_SRC_ALPHA;
			material.alphaDestinationBlend = Graphics::BLEND_INV_SRC_ALPHA;

		}//Junk::Junk(Graphics::IGraphics*gfx, System::ISystem*sys)

		Junk::~Junk(){
			
			//font.release();

			if (vb){
				vb->Release();
				vb = nullptr;
			}

			if (mesh){
				mesh->Release();
				mesh = nullptr;
			}

		}//Junk::~Junk()

		void Junk::init(void){



			input->registerKeyboardCallback(std::static_pointer_cast<Input::IKeyCallback>(shared_from_this()));
			input->registerMouseCallback(std::static_pointer_cast<Input::IMouseCallback>(shared_from_this()));

			camera = std::static_pointer_cast<Graphics::DirectX::FpsCamera>(gfx->createFpsCamera());
			gfx->setCamera(camera);
			camera->position(Math::Vector3f(0.0f, 6.0f, -50.0f));
			/*
			std::shared_ptr<Assignments::Sphere::Sphere> sphere = std::shared_ptr<Assignments::Sphere::Sphere>(new Assignments::Sphere::Sphere(
				gfx,
				Math::Vector3f(20, 10, -50),
				10.0f,
				100,
				100,
				Graphics::Color4f(1.0f, 1.0f, 0.0f, 0.0f)
				));
			sphere->init();
			gfx->addObject(sphere);
			
			std::shared_ptr<Assignments::Box3D::Box3D> box = std::shared_ptr<Assignments::Box3D::Box3D>(new Assignments::Box3D::Box3D(gfx,
				Math::Vector3f(0.0f, -1.0f, 0.0f),
				Math::Vector3f(10000.0f, 1.0f, 10000.0f),
				Graphics::Color4f(1.0f, 0.0f, 0.8f, 0.0f)
				));
			box->init();
			gfx->addObject(box);
			*/
			std::shared_ptr<Assignments::Model3D::Model3D> model = std::shared_ptr<Assignments::Model3D::Model3D>(
				//new Assignments::Model3D::Model3D(gfx, "C:\\Users\\mccur_000\\Documents\\Visual Studio 2013\\Projects\\GFX1\\GFX1\\assets\\airplane 2.x"));
				new Assignments::Model3D::Model3D(gfx, "assets\\airplane 2.x"));
			model->init();
			gfx->addObject(model);

			std::shared_ptr<Assignments::Terrain::Terrain> terrain = std::shared_ptr<Assignments::Terrain::Terrain>(new Assignments::Terrain::Terrain(gfx));
			terrain->init();
			gfx->addObject(terrain);

			/*box = std::shared_ptr<Assignments::Box3D::Box3D>(new Assignments::Box3D::Box3D(gfx, 
							Math::Vector3f(0, 10, 0), 
							Math::Vector3f(10, 10, 10), 
							Graphics::Color4f(1.0f, 0.0f, 1.0f, 1.0f)
						));
			box->init();
			gfx->addObject(box);*/
			/*
			std::shared_ptr<Assignments::Box3D3::Box3D3> box3 = std::shared_ptr<Assignments::Box3D3::Box3D3>(new Assignments::Box3D3::Box3D3(gfx,
				Math::Vector3f(0, 10, 0),
				Math::Vector3f(10, 10, 10),
				0));
			box3->init();
			gfx->addObject(box3);
			*/
			
			/*
			float rad = 5;
			short sli = 10;
			short sta = 10;

			LPD3DXMESH temp;
			D3DXCreateSphere(gfx->getDevice(),rad,sli,sta,&temp,nullptr);
			temp->CloneMeshFVF(D3DXMESH_SYSTEMMEM,FVF,gfx->getDevice(),&mesh);
			temp->Release();
			if (SUCCEEDED(mesh->GetVertexBuffer(&vb))){
				Vertex*v;
				vb->Lock(0, 0, (void**)&v, 0);

				for (DWORD i = 0; i < mesh->GetNumVertices(); i++)
					v[i].color = 0xFFFFFFFF;
				vb->Unlock();
				vb = nullptr;
			}
			*/
			
			gfx->setClearColor(0.0f, 0.0f, 0.25f);
			setupLighting();

			mouse_x = input->mouseX();
			mouse_y = input->mouseY();
			

		}//void Junk::init(void)

		void Junk::setupLighting(void){
			gfx->getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
			gfx->getDevice()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(64, 64, 64));

			D3DMATERIAL9 mat;
			ZeroMemory(&mat, sizeof(mat));
			mat.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			mat.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			gfx->getDevice()->SetMaterial(&mat);

			D3DXVECTOR3 dir = D3DXVECTOR3(1.0f, -1.0f, 0.1f);
			D3DXVec3Normalize(&dir, &dir);

			D3DLIGHT9 light;
			ZeroMemory(&light, sizeof(light));
			light.Type = D3DLIGHT_DIRECTIONAL;
			light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			light.Direction = dir;
			
			gfx->getDevice()->SetLight(0, &light);
			gfx->getDevice()->LightEnable(0, TRUE);
			gfx->getDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

		}

		void Junk::draw(void){

			
			Math::Matrix world;
			gfx->setWorldMatrix(world);


			Math::Matrix projection;
			D3DXMATRIX proj;
			D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI/3.0f, 1.3f, 1.0f, 5000.0f);
			projection = Math::Matrix(&proj.m[0][0]);
			gfx->setProjectionMatrix(projection);

			if(mesh){
				gfx->getDevice()->BeginScene();

				gfx->setMaterial(material);

				//gfx->getDevice()->SetTexture(0, nullptr);
				gfx->getDevice()->SetVertexDeclaration(nullptr);
				//gfx->getDevice()->SetVertexShader(nullptr);
				//gfx->getDevice()->SetPixelShader(nullptr);
				gfx->getDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));
				gfx->getDevice()->SetFVF(FVF);

				mesh->DrawSubset(0);

				//for (int i = 0; i < 6; i++)
				//	gfx->getDevice()->DrawPrimitive(type, i * 4, 2);

				gfx->getDevice()->EndScene();
			}

			if (input->keyIsDown(Input::VKEY::VKEY_UARROW) || input->keyIsDown(Input::VKEY::VKEY_W))
				camera->moveForward(hSpeed);
			if (input->keyIsDown(Input::VKEY::VKEY_DARROW) || input->keyIsDown(Input::VKEY::VKEY_S))
				camera->moveBackward(hSpeed);
			if (input->keyIsDown(Input::VKEY::VKEY_LARROW) || input->keyIsDown(Input::VKEY::VKEY_A))
				camera->moveLeft(hSpeed);
			if (input->keyIsDown(Input::VKEY::VKEY_RARROW) || input->keyIsDown(Input::VKEY::VKEY_D))
				camera->moveRight(hSpeed);

			/*if (input->keyIsDown(Input::VKEY::VKEY_LARROW))
				camera->lookLeft(rSpeed);
			if (input->keyIsDown(Input::VKEY::VKEY_RARROW))
				camera->lookRight(rSpeed);
				*/


			if (!freeFloat){
				static float v = 0.0f;
				static float g = -32.174f / 60.0f;
				v += g;
				v = (v < -250.0f) ? -250.0f : v;
				if ((v + camera->position().y) < 6.0f){
					v = 0.0f;
					camera->moveUp(6.0f - camera->position().y);
				}
				if (input->keyIsDown(Input::VKEY::VKEY_SPACE) && camera->position().y < 10.0f)
					v += (g*-1.1f);
				camera->moveUp(v);
			}
			else{
				if (input->keyIsDown(Input::VKEY::VKEY_SPACE)){
					camera->moveUp(vSpeed);
				}
				if (input->keyIsDown(Input::VKEY::VKEY_LCTRL)){
					camera->moveDown(vSpeed);
				}
			}
			

		}//void Junk::draw(void)

		void Junk::keyDownCallback(Input::VKEY::VKEY key){

			if (key == Input::VKEY::VKEY_LSHIFT){
				freeFloat = !freeFloat;
				if (freeFloat){
					hSpeed = AIR_HSPEED;
					vSpeed = AIR_VSPEED;
					rSpeed = AIR_RSPEED;
				}
				else{
					hSpeed = GROUND_HSPEED;
					vSpeed = GROUND_VSPEED;
					rSpeed = GROUND_RSPEED;
				}
			}

		}//void Junk::keyDownCallback(Input::VKEY::VKEY key)

		void Junk::mouseMove(float x, float y){
			
			Debug::Print("mX %f   mY %f\n", mouse_x, mouse_y);
			Debug::Print("X %f    Y %f\n", x, y);
			Debug::Print("dX %f    dY %f\n\n", (mouse_x - x), (mouse_y - y));

			if (abs(mouse_x - x) < 0.1f && abs(mouse_y - y) < 0.1f){
				camera->lookLeft(rSpeed * (mouse_x - x));
				camera->lookDown(rSpeed * (mouse_y - y));
			}

			mouse_x = x;
			mouse_y = y;

		}//void Junk::mouseMove(float x, float y)

	}//namespace Junk
}//namespace Assignments
