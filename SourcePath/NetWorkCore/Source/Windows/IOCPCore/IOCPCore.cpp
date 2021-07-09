
#include "../../../Include/Windows/IOCPCore/IOCPCore.h"

#pragma region Singleton
NetWorkIOCPCore* NetWorkIOCPCore::m_pIns = nullptr;

NetWorkIOCPCore::NetWorkIOCPCore()
{}

NetWorkIOCPCore::~NetWorkIOCPCore()
{}

NetWorkIOCPCore* NetWorkIOCPCore::Get()
{
	if (nullptr == m_pIns)
	{
		//	确定一定能拿到锁
		while (!m_rInstanceLock.try_lock()) {}

		if (nullptr == m_pIns)
		{
			m_pIns = new NetWorkIOCPCore();
		}

		m_rInstanceLock.unlock();
	}

	return m_pIns;
}
#pragma endregion
