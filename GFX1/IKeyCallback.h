#ifndef ___IKEYCALLBACK_H___
#define ___IKEYCALLBACK_H___

#include "KeyCodes.h"

namespace Input{

	class IKeyCallback{
	public:

		IKeyCallback(){};
		virtual ~IKeyCallback(){};

		virtual void keyDownCallback(VKEY::VKEY key){};
		virtual void keyUpCallback(VKEY::VKEY key){};

	};//class IKeyCallback

}//namespace System


#endif//___IKEYCALLBACK_H___