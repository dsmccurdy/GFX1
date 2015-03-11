#ifndef ___ICAMERA_H___
#define ___ICAMERA_H___

#include "Vector3f.h"

namespace Graphics{

	class ICamera {
	public:
		ICamera(){};
		virtual ~ICamera(){};

		virtual Math::Vector3f position(const Math::Vector3f&) = 0;
		virtual Math::Vector3f position(void) const = 0;

	};

}//namespace Graphics

#endif//___ICAMERA_H___