#ifndef ___IREADWORKUNIT_H___
#define ___IREADWORKUNIT_H___

namespace System{

	class IWorkUnit{
	public:
		IWorkUnit(){};
		virtual ~IWorkUnit(){};

		virtual void doWork(void)=0;


	};//class IWorkUnit

}//namespace System



#endif//___IREADWORKUNIT_H___