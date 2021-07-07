
#ifndef __THREAD_CORE_LOG_QUEUE_ELEMENT_H__
#define __THREAD_CORE_LOG_QUEUE_ELEMENT_H__

#include <string>

#define SLC_TIME_STRING_SIZE 512

class LogQueueElement
{
public:
	LogQueueElement();
	LogQueueElement(int nThreadID);
	LogQueueElement(const char* strMsg, int nLogLevel);
	LogQueueElement(const char* strMsg, int nThreadID, int nLogLevel);
	~LogQueueElement();

	const char* GetLogMessage(std::string& strOut);
	void SetLogThreadID(int nThreadID);
	void SetLogMessage(const char* strMsg, int nLogLevel);
	void SetLogLevel(int nLogLevel);
	int GetLogLevel();

protected:

	std::string		m_strLogMsg;
	int				m_nThreadID;
	std::string		m_strTime;
	int				m_nLogLevel;
};

#endif	//	__THREAD_CORE_LOG_QUEUE_ELEMENT_H__
