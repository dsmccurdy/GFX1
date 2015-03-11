#ifndef ___ISYSTEM_H___
#define ___ISYSTEM_H___

#include <memory>

#include "ISubSystem.h"
#include "IKeyCallback.h"


namespace System{

	class ISystem{
	private:

		static std::shared_ptr<ISystem> _inst;

	public:

		static std::shared_ptr<ISystem> getInstance(void);
		static void setInstance(std::shared_ptr<ISystem>);

		ISystem();
		virtual ~ISystem();

		virtual int getWindowWidth(void)=0;
		virtual int getWindowHeight(void)=0;

		virtual void registerSubSystem(std::shared_ptr<ISubSystem>) = 0;
		virtual void unregisterSubSystem(std::shared_ptr<ISubSystem>) = 0;

		virtual void initalizeStage1(void) = 0;
		virtual void initalizeStage2(void) = 0;

		virtual void releaseStage1(void) = 0;
		virtual void releaseStage2(void) = 0;

	};//class ISystem

}//namespace System

#endif //#ifndef ____ISYSTEM_H___