
#ifndef __LOG_THREAD_H__
#define __LOG_THREAD_H__

#include "MultyThreadBase.h"
#include <string>
#include <vector>
#include <mutex>

class LogQueueElement;

enum ELogStringProcessStatus
{
	ELSPS_STANDBY = 0,	//	Log string input
	ELSPS_WRITING,		//	Log string print
	ELSPS_RELEASE,		//	Log string erase

	ELSPS_MAX
};

typedef std::vector<LogQueueElement*> LogQueue;

class LogThread : public MultyThreadBase
{
public:
	LogThread();
	LogThread(SI32 nThreadID);
	~LogThread();

#pragma region Thread base function override
	virtual bool OnThreadStart() override;
	virtual bool OnThreadTick(UI64 ulCurTime) override;
	virtual bool OnThreadEnd() override;
#pragma endregion

	void SetLogLevel(SI32 nPrintLevel, SI32 nLogLevel);
#ifdef _WIN_
	bool SetConsoleHandle(void* pHandle);
#endif

#pragma region Log message Operate
	void AddLogMessage(std::string strLog, SI32 nThreadID, SI32 nLogLevel);
	void OutputLog();
	void ReleseLog();
	void SwitchLogSlot();
#pragma endregion

protected:

	FILE* m_pLogFile;
	std::string m_strLogFileName;

	LogQueue m_arrLogQueue[ELSPS_MAX];
	SI32 m_nPrintLevel;
	SI32 m_nLogLevel;
	std::mutex m_rLock;
#ifdef _WIN_
	void* m_pConsoleHandle;
#endif
};


#endif	//	__LOG_THREAD_H__
