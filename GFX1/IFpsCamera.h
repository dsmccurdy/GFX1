#ifndef ___IFPSCAMERA_H___
#define ___IFPSCAMERA_H___

#include "ICamera.h"

namespace Graphics{
	
	class IFpsCamera :
		public ICamera{

		virtual void moveForward(float delta) = 0;
		virtual void moveBackward(float delta) = 0;
		virtual void moveLeft(float delta) = 0;
		virtual void moveRight(float delta) = 0;

		virtual void moveUp(float delta) = 0;
		virtual void moveDown(float delta) = 0;

		virtual void lookUp(float delta) = 0;
		virtual void lookDown(float delta) = 0;
		virtual void lookLeft(float delta) = 0;
		virtual void lookRight(float delta) = 0;

	};

}//namespace Graphics

#endif//___IFPSCAMERA_H___