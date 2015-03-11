#ifndef ___THREAD_H___
#define ___THREAD_H___

#include <memory>
#include <list>
#include <map>
#include <thread>

#include "IWorkUnit.h"

namespace System{

	struct ThreadData;

	class Thread:
		public std::enable_shared_from_this<Thread>{
	public:
		static std::shared_ptr<Thread> current(void);
		static std::list<std::shared_ptr<Thread>> getAllThreads(void);
		static int numThreads(void);
		static int threadsWaiting(void);
		static void pushWorkToLowest(std::shared_ptr<IWorkUnit> work);
		static void initThreadPool(void);
		static void releaseThreadPool(void);

		static void pauseAllThreads(void);
		static void resumeAllThreads(void);
		
		static bool allThreadsWaiting(void);

	public:
		Thread();
		~Thread();

		void pushWork(std::shared_ptr<IWorkUnit> work);
		std::list<std::shared_ptr<IWorkUnit>> stealWork(void);
		int numWorkUnits(void) const;
		bool isWaiting(void) const;
		bool isPaused(void) const;
		void stop(void);
		void pause(void);
		void resume(void);

		void run(void);

	private:
		ThreadData* data;
	};//class Thread


}//namesapce System

#endif//___THREAD_H___