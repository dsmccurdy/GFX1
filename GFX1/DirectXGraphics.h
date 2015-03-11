#ifndef ___DIRECTXGRAPHICS_H___
#define ___DIRECTXGRAPHICS_H___
#include <d3d9.h>

#include "IGraphics.h"
#include "ISystem.h"
#include "WindowsSystem.h"

namespace Graphics{
	namespace DirectX{

		struct DirectXGraphicsData;
		
		class DirectXGraphics : 
			public Graphics::IGraphics,
			public std::enable_shared_from_this<DirectXGraphics>{
		private:

			DirectXGraphicsData*data;

		public:

			DirectXGraphics(std::shared_ptr<System::WindowsSystem::WindowsSystem> ws);
			virtual ~DirectXGraphics();

			virtual void initalizeStage1(void);

			virtual void endWritePhase(void);

			virtual void releaseStage2(void);

			virtual void addObject(std::shared_ptr<IGfxObject> obj);
			virtual void removeObject(std::shared_ptr<IGfxObject> obj);

			virtual std::shared_ptr<ICamera> createFpsCamera(void);
			virtual void setCamera(std::shared_ptr<ICamera> camera);
			virtual std::shared_ptr<ICamera> getCamera(void);

			virtual void setWorldMatrix(Math::Matrix&matrix);
			virtual Math::Matrix getWorldMatrix(void) const;

			virtual void setViewMatrix(Math::Matrix&matrix);
			virtual Math::Matrix getViewMatrix(void) const;

			virtual void setProjectionMatrix(Math::Matrix&matrix);
			virtual Math::Matrix getProjectionMatrix(void) const;

			virtual void setMaterial(Graphics::Material&material);
			virtual Graphics::Material getMaterial(void);

			virtual void setClearColor(float r, float g, float b);

			LPDIRECT3DDEVICE9 getDevice(void);

		};//class DirectXGraphics

	}//namespace DirectX
}//namepsace Graphics

#endif//___DIRECTXGRAPHICS_H___