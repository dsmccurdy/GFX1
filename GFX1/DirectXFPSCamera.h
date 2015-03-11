#include <d3d9.h>
#include <d3dx9.h> 

#include "DirectXGraphics.h"
#include "ISystem.h"
#include "ICamera.h"

namespace Graphics{
	namespace DirectX{

		struct FpsCameraData;

		class FpsCamera:
			public Graphics::ICamera{
		private:

			FpsCameraData*data;

		public:

			FpsCamera(std::shared_ptr<System::ISystem>system,std::shared_ptr<Graphics::DirectX::DirectXGraphics>gfx);
			virtual ~FpsCamera();

			virtual Math::Vector3f position(const Math::Vector3f&);
			virtual Math::Vector3f position(void) const;


			virtual void moveForward(float delta);
			virtual void moveBackward(float delta);
			virtual void moveLeft(float delta);
			virtual void moveRight(float delta);

			virtual void moveUp(float delta);
			virtual void moveDown(float delta);

			virtual void lookUp(float delta);
			virtual void lookDown(float delta);
			virtual void lookLeft(float delta);
			virtual void lookRight(float delta);


			void setViewMatrix(void) const;
		};
	}
}