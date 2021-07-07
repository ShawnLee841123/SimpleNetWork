
#ifndef __MULTY_THREAD_BASE_H__
#define __MULTY_THREAD_BASE_H__

#include <thread>
#include "System/SystemTypeDefines.h"

class MultyThreadBase
{
public:
	MultyThreadBase();
	MultyThreadBase(SI32 nThreadID);
	~MultyThreadBase();

	SI32 GetThreadID();
	bool ThreadEnable();
	void SetThreadEnable(bool bEnable);

#pragma region Childre override function
	virtual bool OnThreadStart();
	virtual bool OnThreadEnd();
	virtual bool OnThreadTick(UI64 ulCurTime);
#pragma endregion

protected:
	
	SI32 m_nThreadID;
	SI32 m_nSleepTime;
	std::thread m_pThread;
	bool m_bEnable;

private:

#pragma region Working Process
	void StartThread(SI32 nThreadID);
	void EndThread();
	void ThreadTick();
#pragma endregion
};

#endif	//	__MULTY_THREAD_BASE_H__
