#include <deque>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>


#include "Thread.h"
#include "Debug.h"

namespace System{

	struct ThreadData{
		std::deque < std::shared_ptr<IWorkUnit>> workQueue;
		std::mutex workQueueMutex;

		std::atomic<bool> exit = false;
		std::atomic<bool> waiting = false;
		std::atomic<bool> pause = false;

	};//struct ThreadData

	static std::list<std::thread> s_cthreads;
	static std::map<std::thread::id, std::shared_ptr<Thread>> s_threads;
	static std::mutex s_threadsMutex;
	static std::atomic<int> s_numThreads=0;
	
	std::shared_ptr<Thread> Thread::current(void){
		std::lock_guard<std::mutex> lock(s_threadsMutex);
		if (s_threads.find(std::this_thread::get_id()) != s_threads.end())
			return s_threads[std::this_thread::get_id()];
		return nullptr;
	}//std::shared_ptr<Thread> Thread::current(void)

	std::list<std::shared_ptr<Thread>> Thread::getAllThreads(void){
		std::list<std::shared_ptr<Thread>> list;
		std::lock_guard<std::mutex> lock(s_threadsMutex);
		for (auto& t : s_threads){
			list.push_back(t.second);
		}
		return list;
	}//std::list<std::shared_ptr<Thread>> Thread::getAllThreads(void)

	int Thread::numThreads(void){
		return s_numThreads;
	}//int Thread::numThreads(void)

	int Thread::threadsWaiting(void){
		int count=0;

		std::lock_guard<std::mutex> lock(s_threadsMutex);
		for (auto& t : s_threads){
			if (t.second->isWaiting())
				count++;
		}

		return count;
	}//int Thread::threadsWaiting(void)

	void Thread::pushWorkToLowest(std::shared_ptr<IWorkUnit> work){
		std::lock_guard<std::mutex> lock(s_threadsMutex);

		std::shared_ptr<Thread> thread = nullptr;
		int num = 0;

		for (auto& t : s_threads){
			if (t.second->isWaiting()){
				t.second->pushWork(work);
				return;
			}else if (t.second->numWorkUnits() < num || thread == nullptr){
				thread = t.second;
				num = thread->numWorkUnits();
			}
		}
		thread->pushWork(work);

	}//void Thread::pushWorkToLowest(std::shared_ptr<IWorkUnit> work)


	void startThread(void){
		std::shared_ptr<System::Thread> t(new System::Thread());
		t->run();
	}

	void Thread::initThreadPool(void){
		unsigned int numThreads = std::thread::hardware_concurrency();
		if (numThreads < 2)
			numThreads = 2;
		
		for (unsigned int i = 0; i < numThreads; i++){
			std::lock_guard<std::mutex> lock(s_threadsMutex);
			s_cthreads.push_back(std::thread(startThread));
		}

	}//void Thread::initThreadPool(void)

	void Thread::releaseThreadPool(void){

		

		for (auto t : getAllThreads()){
			t->stop();
		}

		std::lock_guard<std::mutex> lock(s_threadsMutex);
		while (!s_cthreads.empty()){
			s_cthreads.back().join();
			s_cthreads.pop_back();
		}

	}//void Thread::releaseThreadPool(void)


	void Thread::pauseAllThreads(void){
		std::lock_guard<std::mutex> lock(s_threadsMutex);
		for (auto t : s_threads){
			t.second->pause();
		}
	}//void Thread::pauseAllThreads(void)

	void Thread::resumeAllThreads(void){
		std::lock_guard<std::mutex> lock(s_threadsMutex);
		for (auto t : s_threads){
			t.second->resume();
		}
	}//void Thread::resumeAllThreads(void)

	bool Thread::allThreadsWaiting(void){
		int count = 0;
		std::lock_guard<std::mutex> lock(s_threadsMutex);

		//pauseAllThreads();

		for (auto& t : s_threads){
			if (t.second->isWaiting())
				count++;
		}

		//resumeAllThreads();
	
		return count == numThreads();
	}//bool Thread::allThreadsWaiting(void)






	Thread::Thread(){
		data = new ThreadData();
	}//Thread::Thread()

	Thread::~Thread(){
		s_threads.erase(std::this_thread::get_id());
		delete data;
	}//Thread::~Thread()

	void Thread::pushWork(std::shared_ptr<IWorkUnit> work){
		std::lock_guard<std::mutex> lock(data->workQueueMutex);
		data->workQueue.push_front(work);
	}//void Thread::pushWork(std::shared_ptr<IWorkUnit> work)

	std::list<std::shared_ptr<IWorkUnit>> Thread::stealWork(void){
		std::lock_guard<std::mutex> lock(data->workQueueMutex);

		std::list<std::shared_ptr<IWorkUnit>> list;
		
		while (data->workQueue.size() > list.size()){
			list.push_back(data->workQueue.back());
			data->workQueue.pop_back();
		}

		return list;

	}//std::list<std::shared_ptr<IWorkUnit>> Thread::stealWork(void)

	int Thread::numWorkUnits(void) const{
		std::lock_guard<std::mutex> lock(data->workQueueMutex);
		return data->workQueue.size();
	}//int Thread::numWorkUnits(void) const

	bool Thread::isWaiting(void) const{
		std::lock_guard<std::mutex> lock(data->workQueueMutex);
		return data->workQueue.size() == 0 && data->waiting;
	}//bool Thread::isWaiting(void) const

	bool Thread::isPaused(void) const{
		return data->pause;
	}

	void Thread::run(void){
		{
			std::lock_guard<std::mutex> lock(s_threadsMutex);
			s_threads[std::this_thread::get_id()] = shared_from_this();
			s_numThreads++;
		}
		

		while (!data->exit){
			


			std::shared_ptr<IWorkUnit> unit=nullptr;
			{
				std::lock_guard<std::mutex> lock(data->workQueueMutex);
				if (!data->workQueue.empty()){
					unit = data->workQueue.front();
					data->workQueue.pop_front();
				}
			}

			if (unit){
				data->waiting = false;
				unit->doWork();
			}
			else{
				std::shared_ptr<Thread> thread = nullptr;
				int num = 0;
				{
					std::lock_guard<std::mutex> lock(s_threadsMutex);
					for (auto& t : s_threads){
						if (t.second->numWorkUnits() > num){
							num = t.second->numWorkUnits();
							thread = t.second;
						}
					}//for (auto& t : s_threads)
					
				}

				if (thread){
					std::list<std::shared_ptr<IWorkUnit>> list = thread->stealWork();

					std::lock_guard<std::mutex> lock(data->workQueueMutex);
					while (list.size() > 0){
						data->workQueue.push_back(list.front());
						list.pop_front();
					}
				}
				else{
					data->waiting = true;
					std::this_thread::sleep_for(std::chrono::nanoseconds(1));
				}//if (thread) else

			}//if (unit) else

			while (data->pause){
				std::this_thread::sleep_for(std::chrono::microseconds(1));
				if (data->exit)
					break;
			}

		}//while (!data->exit)
		
		s_numThreads--;
	}//void Thread::run(void)

	void Thread::stop(void){
		data->exit = true;
	}//void Thread::stop(void)

	void Thread::pause(void){
		data->pause = true;
	}//void Thread::pause(void)

	void Thread::resume(void){
		data->pause = false;
	}//void Thread::resume(void)

}//namespace System