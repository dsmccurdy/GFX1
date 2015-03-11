#include "DirectXGraphics.h"
#include "WindowsSystem.h"
#include "Debug.h"
#include "DirectXFPSCamera.h"

#include <vector>
#include <list>

#include <d3d9.h>

namespace Graphics{
	namespace DirectX{

		struct DirectXGraphicsData{
			std::shared_ptr<System::WindowsSystem::WindowsSystem> system;

			LPDIRECT3D9 directx = nullptr;
			LPDIRECT3DDEVICE9 device = nullptr;

			std::list<std::shared_ptr<IGfxObject>>*objects = nullptr;

			std::shared_ptr<FpsCamera> camera = nullptr;

			float clearColor[3];

			Graphics::Material material;

		};//struct DirectXGraphicsData

		DirectXGraphics::DirectXGraphics(std::shared_ptr<System::WindowsSystem::WindowsSystem> ws){

			data = new DirectXGraphicsData();
			data->system = ws;
			data->objects = new std::list<std::shared_ptr<IGfxObject>>();

			data->clearColor[0] = 0.0f;
			data->clearColor[1] = 1.0f;
			data->clearColor[2] = 0.0f;

		}//DirectXGraphics::DirectXGraphics(std::shared_ptr<System::WindowsSystem::WindowsSystem> ws)

		DirectXGraphics::~DirectXGraphics(){
			releaseStage1();
			releaseStage2();
		}//DirectXGraphics::~DirectXGraphics()

		void DirectXGraphics::initalizeStage1(void){

			setInstance(shared_from_this());

			data->directx = Direct3DCreate9(D3D_SDK_VERSION);
			if (data->directx == nullptr){
				Debug::Print("DirectX create failed");
				return;
			}

			D3DPRESENT_PARAMETERS d3dpp;
			ZeroMemory(&d3dpp, sizeof(d3dpp));
			d3dpp.Windowed = true;
			d3dpp.hDeviceWindow = data->system->getWindow();
			d3dpp.BackBufferHeight = data->system->getWindowHeight();
			d3dpp.BackBufferWidth = data->system->getWindowWidth();
			d3dpp.BackBufferCount = 1;
			d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
			d3dpp.EnableAutoDepthStencil = TRUE;
			d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
			d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;

			HRESULT result = data->directx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, data->system->getWindow(),
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &data->device
				);
			if (FAILED(result)){
				Debug::Print("Attemped Software Emulation");
				result = data->directx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, data->system->getWindow(),
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &data->device
					);
				if (FAILED(result)){
					Debug::Print("Software Emulation failed");
					return;
				}
			}

			setMaterial(data->material);


		}//void DirectXGraphics::initalizeStage1(void)

		void DirectXGraphics::endWritePhase(void){

			data->device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB((DWORD)(255.0f*data->clearColor[0]), (DWORD)(255.0f*data->clearColor[1]), (DWORD)(255.0f*data->clearColor[2])), 1.0f, 0L);

			data->camera->setViewMatrix();

			for (std::shared_ptr<IGfxObject> obj : *data->objects){
				obj->draw();
			}

			data->device->Present(nullptr, nullptr, nullptr, nullptr);

		}//void DirectXGraphics::endWritePhase(void)

		void DirectXGraphics::releaseStage2(void){

			if (data){
				if (data->objects){
					delete data->objects;
					data->objects = nullptr;
				}

				if (data->device){
					data->device->Release();
					data->device = nullptr;
				}

				if (data->directx){
					data->directx->Release();
					data->directx = nullptr;
				}

				delete data;
				data = nullptr;
			}//if (data)

		}//void DirectXGraphics::releaseStage2(void)

		void DirectXGraphics::addObject(std::shared_ptr<IGfxObject> obj){
			data->objects->remove(obj);
			data->objects->push_back(obj);
		}//void DirectXGraphics::addObject(IGfxObject*obj)

		void DirectXGraphics::removeObject(std::shared_ptr<IGfxObject> obj){
			data->objects->remove(obj);
		}//void DirectXGraphics::removeObject(IGfxObject*obj)

		std::shared_ptr<ICamera> DirectXGraphics::createFpsCamera(void){
			return std::shared_ptr<ICamera>(new FpsCamera(data->system,shared_from_this()));
		}//std::shared_ptr<ICamera> DirectXGraphics::createCamera(void)

		void DirectXGraphics::setCamera(std::shared_ptr<ICamera> camera){
			data->camera = std::static_pointer_cast<FpsCamera>(camera);
		}//void DirectXGraphics::setCamera(std::shared_ptr<ICamera> camera)

		std::shared_ptr<ICamera> DirectXGraphics::getCamera(void){
			return data->camera;
		}//std::shared_ptr<ICamera> DirectXGraphics::getCamera(void)


		void DirectXGraphics::setWorldMatrix(Math::Matrix&matrix){
			D3DXMATRIX world = D3DXMATRIX(&matrix.m[0][0]);
			data->device->SetTransform(D3DTS_WORLD, &world);
		}//void DirectXGraphics::setWorldMatrix(Math::Matrix&matrix)

		Math::Matrix DirectXGraphics::getWorldMatrix(void) const{
			D3DMATRIX world;
			data->device->GetTransform(D3DTS_WORLD, &world);
			return Math::Matrix(&world.m[0][0]);
		}//Math::Matrix DirectXGraphics::getWorldMatrix(void) const

		void DirectXGraphics::setViewMatrix(Math::Matrix&matrix){
			D3DXMATRIX view = D3DXMATRIX(&matrix.m[0][0]);
			data->device->SetTransform(D3DTS_VIEW, &view);
		}//void DirectXGraphics::setViewMatrix(Math::Matrix&matrix)

		Math::Matrix DirectXGraphics::getViewMatrix(void) const{
			D3DMATRIX view;
			data->device->GetTransform(D3DTS_VIEW, &view);
			return Math::Matrix(&view.m[0][0]);
		}//Math::Matrix DirectXGraphics::getViewMatrix(void) const

		void DirectXGraphics::setProjectionMatrix(Math::Matrix&matrix){
			D3DXMATRIX projection = D3DXMATRIX(&matrix.m[0][0]);
			data->device->SetTransform(D3DTS_PROJECTION, &projection);
		}//void DirectXGraphics::setProjectionMatrix(Math::Matrix&matrix)

		Math::Matrix DirectXGraphics::getProjectionMatrix(void) const{
			D3DMATRIX projection;
			data->device->GetTransform(D3DTS_PROJECTION, &projection);
			return Math::Matrix(&projection.m[0][0]);
		}//Math::Matrix DirectXGraphics::getProjectionMatrix(void) const


		void DirectXGraphics::setMaterial(Material&material){
			data->material = material;

			/*
			data->device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			data->device->SetRenderState(D3DRS_LIGHTING, FALSE);
			//data->device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			*/

			if (data->material.alphaBlendEnable){
				data->device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			}
			else{
				data->device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			}

			switch (data->material.alphaDestinationBlend){
			default:
			case BLEND_ZERO:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
				break;
			case BLEND_ONE:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			case BLEND_SRC_COLOR:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
				break;
			case BLEND_INV_SRC_COLOR:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
				break;
			case BLEND_SRC_ALPHA:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
				break;
			case BLEND_INV_SRC_ALPHA:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			case BLEND_DEST_ALPHA:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
				break;
			case BLEND_INV_DEST_ALPHA:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);
				break;
			case BLEND_DEST_COLOR:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
				break;
			case BLEND_INV_DEST_COLOR:
				data->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTCOLOR);
				break;
			}

			switch (data->material.alphaSourceBlend){
			default:
			case BLEND_ZERO:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
				break;
			case BLEND_ONE:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
				break;
			case BLEND_SRC_COLOR:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
				break;
			case BLEND_INV_SRC_COLOR:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR);
				break;
			case BLEND_SRC_ALPHA:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				break;
			case BLEND_INV_SRC_ALPHA:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA);
				break;
			case BLEND_DEST_ALPHA:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
				break;
			case BLEND_INV_DEST_ALPHA:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTALPHA);
				break;
			case BLEND_DEST_COLOR:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
				break;
			case BLEND_INV_DEST_COLOR:
				data->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
				break;
			}

			if (data->material.lightingEnable){
				data->device->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
			else{
				data->device->SetRenderState(D3DRS_LIGHTING, FALSE);
			}

			switch (data->material.cullMode){
			case CULLMODE_NONE:
				data->device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
				break;
			default:
			case CULLMODE_CCW:
				data->device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
				break;
			case CULLMODE_CW:
				data->device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
				break;
			}

		}//void DirectXGraphics::setMaterial(Material&material)

		Graphics::Material DirectXGraphics::getMaterial(void){
			return data->material;
		}

		void DirectXGraphics::setClearColor(float r, float g, float b){
			data->clearColor[0] = r;
			data->clearColor[1] = g;
			data->clearColor[2] = b;
		}//void DirectXGraphics::setClearColor(float r, float g, float b)

		LPDIRECT3DDEVICE9 DirectXGraphics::getDevice(void){
			return data->device;
		}//LPDIRECT3DDEVICE9 DirectXGraphics::getDevice(void)

	}//namespace DrectX
}//namespace Graphics