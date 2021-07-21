
#ifndef __NET_WORK_CORE_IOCP_CORE_H__
#define __NET_WORK_CORE_IOCP_CORE_H__

#include <mutex>
#include <map>
#include "../../System/NetWorkCoreVariableDefines.h"
#include "IOCPDefines.h"

enum VipSock
{
	EVST_NONE = 0,

	EVST_MAX
};

class NetWorkIOCPCore
{
#pragma region Singleton
private:
	NetWorkIOCPCore();

	~NetWorkIOCPCore();

	static NetWorkIOCPCore* m_pIns;

public:
	static NetWorkIOCPCore* Get();

protected:

#pragma region Singleton thread lock
	static std::mutex m_rInstanceLock;
#pragma endregion

#pragma endregion


#pragma region Function

	bool Initial();

#pragma region Create IOCP about

	bool InitialSocket();

	CORE_SOCKETADDR* CreateSocketAddress(const char* strAddress, int nPort, CORE_SOCKETADDR_IN& outSockAdd);

	bool InitialIOCPHandle(LPWIN_OPERATE_SOCKET_CONTEXT pSockCon, void* pIOCPHandle);

	bool ListenSocket(CORE_SOCKET& sock, CORE_SOCKETADDR* addr, int nListenCount);

	bool ConnectSocket(CORE_SOCKET& sock, CORE_SOCKETADDR* addr);

	bool GetIOCPFunction(CORE_SOCKET& sock, GUID guidFunc, void* pFuncHandle);
	
	bool CreateListenSocket(const char* strAddress, int nPort);

	bool CreateConnectSocket(const char* strAddress, int nPort);

#pragma endregion
	bool DestroyIOCP();
	
#pragma endregion

protected:
#pragma region Variable
	//	address and port
	Core_SockStoreKey*		m_pSockAddress;

	Core_SockStoreKey		m_arrVipSock[EVST_MAX];

	void*					m_pIOCPHandle;
	void*					m_pIOCPAcceptHandle;
	void*					m_pIOCPAcceptSockAddrHandle;
	void*					m_pIOCPListenHandle;
	void*					m_pIOCPConnectHandle;

	LPWIN_OPERATE_SOCKET_CONTEXT m_pListenCon;
	std::map<Core_SockStoreKey, IOCPParams*>	m_dicConnect;

#pragma endregion


};



#endif
