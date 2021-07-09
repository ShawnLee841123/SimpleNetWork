
#ifndef __NET_WORK_CORE_IOCP_CORE_H__
#define __NET_WORK_CORE_IOCP_CORE_H__

#include <mutex>
#include "../../System/NetWorkCoreVariableDefines.h"

class NetWorkIOCPCore
{
#pragma region Singleton
private:
	NetWorkIOCPCore();

	~NetWorkIOCPCore();

	static NetWorkIOCPCore* m_pIns;

public:
	static NetWorkIOCPCore* Get();
#pragma endregion

protected:

#pragma region Variable
	//	单例静态锁
	static std::mutex m_rInstanceLock;



#pragma endregion

};



#endif
