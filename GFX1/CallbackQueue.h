#ifndef ___CALLBACKQUEUE_H___
#define ___CALLBACKQUEUE_H___

#include <memory>


namespace System{


	class ICallbackItem{
	public:

		ICallbackItem(){};
		virtual ~ICallbackItem(){};

		virtual void callback(void)=0;
	};//class ICallbackItem


	struct CallbackQueueData;

	class CallbackQueue{
	public:

		CallbackQueue();
		virtual ~CallbackQueue();

		virtual void addCallback(std::shared_ptr<ICallbackItem> item);
	protected:

		virtual std::shared_ptr<ICallbackItem> popCallback(void);

	private:

		CallbackQueueData*data;
		
	};//class CallbackQueue


}//namespace System


#endif//___CALLBACKQUEUE_H___