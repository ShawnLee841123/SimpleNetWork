
#ifndef __THREAD_CORE_AUTO_LOCK_H__
#define __THREAD_CORE_AUTO_LOCK_H__

#include <mutex>

class ThreadAutoLock
{
protected:
	std::mutex m_lock;
public:
	ThreadAutoLock()
	{
		m_lock.lock();
	}

	~ThreadAutoLock()
	{
		m_lock.unlock();
	}
};

#endif	//	__THREAD_CORE_AUTO_LOCK_H__
