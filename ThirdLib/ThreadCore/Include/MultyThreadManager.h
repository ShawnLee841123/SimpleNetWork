
#ifndef __MULTY_THREAD_MANAGER_H__
#define __MULTY_THREAD_MANAGER_H__


#ifndef MAX_THREAD_COUNT
#define MAX_THREAD_COUNT 11
#endif

#ifndef LOG_CHARACTER_MAX
#define LOG_CHARACTER_MAX 512
#endif

class MultyThreadBase;
class LogThread;

class MultyThreadManager
{
#pragma region Singlton
public:
	static MultyThreadManager* Get();
	static void Destroy();

private:
	static MultyThreadManager* m_pIns;
	MultyThreadManager();
	~MultyThreadManager();
#pragma endregion

public:
	bool InitialThread(int nThreadCount);
	
	bool StartThread();

	bool DestroyThread();

	void SetConsoleHandle(void* pHandle);

	bool Initial(void* pHandle);

	bool AddNewThread();
#ifdef _WIN_
	void ThreadLog(const char* strLog, int nLevel, int nThreadID, ...);
#else
	void ThreadLog(const char* strLog, int nLevel, int nThreadID, args...);
#endif
protected:

	MultyThreadBase* m_arrThread[MAX_THREAD_COUNT];
	LogThread* m_pLogThread;
	int m_nThreadCount;
};

#ifndef LOG_ECHO
#define LOG_ECHO(fmt, ...) MultyThreadManager::Get()->ThreadLog(fmt, (int)ELLT_ECHO, m_nThreadID, ##__VA_ARGS__);
#endif

#ifndef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) MultyThreadManager::Get()->ThreadLog(fmt, (int)ELLT_DEBUG, m_nThreadID, ##__VA_ARGS__);
#endif

#ifndef LOG_MSG
#define LOG_MSG(fmt, ...) MultyThreadManager::Get()->ThreadLog(fmt, (int)ELLT_MSG, m_nThreadID, ##__VA_ARGS__);
#endif

#ifndef LOG_WARNING
#define LOG_WARNING(fmt, ...) MultyThreadManager::Get()->ThreadLog(fmt, (int)ELLT_WARNING, m_nThreadID, ##__VA_ARGS__);
#endif

#ifndef LOG_ERROR
#define LOG_ERROR(fmt, ...) MultyThreadManager::Get()->ThreadLog(fmt, (int)ELLT_ERROR, m_nThreadID, ##__VA_ARGS__);
#endif


#endif	//	__MULTY_THREAD_MANAGER_H__
