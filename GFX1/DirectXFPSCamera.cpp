#include "DirectXFPSCamera.h"

#include "Debug.h"

namespace Graphics{
	namespace DirectX{

		struct FpsCameraData{

			D3DXVECTOR3 position;
			D3DXVECTOR3 lookAt;

			D3DXVECTOR3 forward;
			D3DXVECTOR3 up;
			D3DXVECTOR3 right;

			D3DXVECTOR3 velocity;
			float pitch;
			float yaw;

			D3DXMATRIX view;

			std::shared_ptr<System::ISystem> system;
			std::shared_ptr<Graphics::DirectX::DirectXGraphics>gfx;

			D3DXMATRIX matView;

		};

		FpsCamera::FpsCamera(std::shared_ptr<System::ISystem>system, std::shared_ptr<Graphics::DirectX::DirectXGraphics>gfx){
			data = new FpsCameraData();
			data->system = system;
			data->gfx = gfx;

			data->lookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			data->position = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
			data->pitch = 0.0f;
			data->yaw = 0.0f;
			data->velocity.x = data->velocity.y = data->velocity.z = 0.0f;

			data->forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			data->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			data->right = D3DXVECTOR3(1.0f, 0.0, 0.0f);



			setViewMatrix();
		}//FpsCamera::FpsCamera(std::shared_ptr<System::ISystem>system, std::shared_ptr<Graphics::DirectX::DirectXGraphics>gfx)

		FpsCamera::~FpsCamera(){

			if (data){
				delete data;
				data = nullptr;
			}

		}//FpsCamera::~FpsCamera()

		Math::Vector3f FpsCamera::position(const Math::Vector3f&v){
			data->position.x = v.x;
			data->position.y = v.y;
			data->position.z = v.z;
			return v;
		}//Math::Vector3f FpsCamera::position(const Math::Vector3f&)

		Math::Vector3f FpsCamera::position(void) const{
			return Math::Vector3f(data->position.x, data->position.y, data->position.z);
		}//Math::Vector3f FpsCamera::position(void) const

		void FpsCamera::moveForward(float delta){
			data->velocity += data->forward * delta;
		}//void FpsCamera::moveForward(float delta)

		void FpsCamera::moveBackward(float delta){
			data->velocity -= data->forward * delta;
		}//void FpsCamera::moveBackward(float delta)

		void FpsCamera::moveLeft(float delta){
			data->velocity -= data->right * delta;
		}//void FpsCamera::moveLeft(float delta)

		void FpsCamera::moveRight(float delta){
			data->velocity += data->right * delta;
		}//void FpsCamera::moveRight(float delta)

		void FpsCamera::moveUp(float delta){
			data->velocity += data->up *delta;
		}//void FpsCamera::moveUp(float delta)

		void FpsCamera::moveDown(float delta){
			data->velocity -= data->up *delta;
		}//void FpsCamera::moveDown(float delta)

		void FpsCamera::lookUp(float delta){
			data->pitch -= delta;
			if (data->pitch > 89.0f){
				delta -= data->pitch - 89.0f;
				data->pitch = 89.0f;
			}

			if (data->pitch < -89.0f){
				delta += -89.0f - data->pitch;
				data->pitch = -89.0f;
			}

			D3DXVECTOR3 v = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

			D3DXMATRIX rot;
			D3DXMatrixRotationAxis(&rot, &data->right, delta);
			//D3DXVec3TransformNormal(&data->up, &data->up, &rot);
			D3DXVec3TransformNormal(&data->forward, &data->forward, &rot);

		}//void FpsCamera::lookUp(float delta)

		void FpsCamera::lookDown(float delta){
			data->pitch -= delta;
			if ( data->pitch > 89.0f){
				delta -= data->pitch - 89.0f;
				data->pitch = 89.0f;
			}

			if (data->pitch < -89.0f){
				delta += -89.0f - data->pitch;
				data->pitch = -89.0f;
			}

			D3DXMATRIX rot;
			D3DXMatrixRotationAxis(&rot, &data->right, -delta);
			//D3DXVec3TransformNormal(&data->up, &data->up, &rot);
			D3DXVec3TransformNormal(&data->forward, &data->forward, &rot);

		}//void FpsCamera::lookDown(float delta)

		void FpsCamera::lookLeft(float delta){
			data->yaw -= delta;
			data->yaw = (data->yaw >= 360.0f) ? data->yaw - 360.0f : data->yaw;
			data->yaw = (data->yaw < 0.0f) ? data->yaw + 360.0f : data->yaw;

			D3DXVECTOR3 v = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			D3DXMATRIX rot;
			D3DXMatrixRotationAxis(&rot, &v, -delta);
			D3DXVec3TransformNormal(&data->right, &data->right, &rot);
			D3DXVec3TransformNormal(&data->forward, &data->forward, &rot);

		}//void FpsCamera::lookLeft(float delta)

		void FpsCamera::lookRight(float delta){
			data->yaw += delta;
			data->yaw = (data->yaw >= 360.0f) ? data->yaw - 360.0f : data->yaw;
			data->yaw = (data->yaw < 0.0f) ? data->yaw + 360.0f : data->yaw;

			D3DXVECTOR3 v = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			D3DXMATRIX rot;
			D3DXMatrixRotationAxis(&rot, &v, delta);
			D3DXVec3TransformNormal(&data->right, &data->right, &rot);
			D3DXVec3TransformNormal(&data->forward, &data->forward, &rot);

		}//void FpsCamera::lookRight(float delta)


		void FpsCamera::setViewMatrix(void) const{

			data->position += data->velocity;
			data->lookAt = data->position + data->forward;
			data->velocity.x = data->velocity.y = data->velocity.z = 0.0f;

			D3DXMatrixLookAtLH(&data->view, &data->position, &data->lookAt, &data->up);
			data->gfx->getDevice()->SetTransform(D3DTS_VIEW, &data->view);
			/*
			data->right.x = data->view._11;
			data->right.y = data->view._21;
			data->right.z = data->view._31;
			
			data->up.x = data->view._12;
			data->up.y = data->view._22;
			data->up.z = data->view._32;

			data->forward.x = data->view._13;
			data->forward.y = data->view._23;
			data->forward.z = data->view._33;

			float len = sqrtf(data->forward.z*data->forward.z + data->forward.x*data->forward.x);
			data->pitch = atan2f(data->forward.y, len);
			data->pitch = atan2f(data->forward.x, data->forward.z);
			*/
		}

	}//namespace DirectX
}//namespace Graphics