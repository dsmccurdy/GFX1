#ifndef ___ISUBSYSTEM_H___
#define ___ISUBSYSTEM_H___

#include "CallbackQueue.h"

namespace System{

	class ISubSystem:
		public CallbackQueue{
	public:

		ISubSystem(){};
		virtual ~ISubSystem(){};

		virtual void initalizeStage1(void){};
		virtual void initalizeStage2(void){};

		virtual void startReadPhase(void){};
		virtual void readPhase(void){};
		virtual void endReadPhase(void){};

		virtual void startWritePhase(void){};
		virtual void writePhase(void){};
		virtual void endWritePhase(void){};

		virtual void releaseStage1(void){};
		virtual void releaseStage2(void){};
	};//class ISubSystem

}//namepsace System
#endif//___ISUBSYSTEMH___
