#include <deque>
#include <thread>
#include <map>



#include "CallbackQueue.h"

namespace System{


	struct CallbackQueueData{
		std::map<std::thread::id,std::deque<std::shared_ptr<ICallbackItem>>> callbackDeque;
	
	};


	CallbackQueue::CallbackQueue(){
		data = new CallbackQueueData();
	}//CallbackQueue::CallbackQueue()

	CallbackQueue::~CallbackQueue(){
		delete data;
	}//CallbackQueue::~CallbackQueue()

	void CallbackQueue::addCallback(std::shared_ptr<ICallbackItem> item){
		data->callbackDeque[std::this_thread::get_id()].push_back(item);
	}//void CallbackQueue::addCallback(std::shared_ptr<ICallbackItem> item)

	std::shared_ptr<ICallbackItem> CallbackQueue::popCallback(void){
		
		for (auto& deque : data->callbackDeque){
			if (!deque.second.empty()){
				std::shared_ptr<ICallbackItem> item = deque.second.front();
				deque.second.pop_front();
				return item;
			}
		}

		return nullptr;
		
	}//std::shared_ptr<ICallbackItem> CallbackQueue::popCallback(void)


}//namespace System