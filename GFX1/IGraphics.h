#ifndef ___IGRAPHICS_H___
#define ___IGRAPHICS_H___

#include <memory>


#include "ISubSystem.h"
#include "IGfxObject.h"
#include "ICamera.h"
#include "Matrix.h"
#include "Material.h"

namespace Graphics{

	class IGraphics :public System::ISubSystem{
	private:
		static std::shared_ptr<IGraphics> s_instance;

	public:

		static std::shared_ptr<IGraphics> getInstance(void);
		static void setInstance(std::shared_ptr<IGraphics> );

		IGraphics();
		virtual ~IGraphics();

		virtual void addObject(std::shared_ptr<IGfxObject> obj) = 0;
		virtual void removeObject(std::shared_ptr<IGfxObject> obj) = 0;


		virtual std::shared_ptr<ICamera> createFpsCamera(void) = 0;
		virtual void setCamera(std::shared_ptr<ICamera> camera) = 0;
		virtual std::shared_ptr<ICamera> getCamera(void) = 0;

		virtual void setWorldMatrix(Math::Matrix&matrix) = 0;
		virtual Math::Matrix getWorldMatrix(void) const = 0;

		virtual void setViewMatrix(Math::Matrix&matrix) = 0;
		virtual Math::Matrix getViewMatrix(void) const = 0;

		virtual void setProjectionMatrix(Math::Matrix&matrix) = 0;
		virtual Math::Matrix getProjectionMatrix(void) const = 0;

		virtual void setMaterial(Material&material) = 0;
		virtual Material getMaterial(void) = 0;

		virtual void setClearColor(float r, float g, float b) = 0;
	};//class IGraphics:public ISubSystem

}//namespace Graphics
#endif//___IGRAPHICS_H___