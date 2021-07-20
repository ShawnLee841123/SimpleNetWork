
#include "../../../Include/Windows/IOCPCore/IOCPCore.h"
#include "MultyThreadManager.h"
#include <WinSock2.h>

#pragma region Singleton
NetWorkIOCPCore* NetWorkIOCPCore::m_pIns = nullptr;

NetWorkIOCPCore::NetWorkIOCPCore() : m_pIOCPHandle(nullptr), m_pIOCPAcceptHandle(nullptr), \
m_pIOCPListenHandle(nullptr), m_pIOCPConnectHandle(nullptr)
{}

NetWorkIOCPCore::~NetWorkIOCPCore()
{

}

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


#pragma region Function
bool NetWorkIOCPCore::Initial()
{
	bool bRet = MultyThreadManager::Get()->InitialThread(3);
	return bRet;
}


bool NetWorkIOCPCore::InitialSocket()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORK(2, 2), &wsaData);
	return true;
}

CORE_SOCKETADDR* NetWorkIOCPCore::CreateSocketAddress(const char* strAddress, int nPort, CORE_SOCKETADDR_IN& outSockAdd)
{
	ZeroMemory(&outSockAdd, sizeof(CORE_SOCKETADDR_IN));
	inet_pton(AF_INET, strAddress, &(outSockAdd.sin_addr));
	outSockAdd.sin_port = htons(nPort);
	outSockAdd.sin_family = AF_INET;
	return (CORE_SOCKETADDR*)(&outSockAdd);
}

bool NetWorkIOCPCore::InitialIOCPHandle(LPWIN_OPERATE_SOCKET_CONTEXT pSockCon, void* pIOCPHandle)
{
	pIOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (nullptr == pIOCPHandle)
	{
		printf("[ERROR] !!!!! Can not create IOCP !!!!!");
		return false;
	}

	pSockCon = new WIN_OPERATE_SOCKET_CONTEXT();
	pSockCon->link = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	int nErrorCode = 0;
	if (INVALID_SOCKET == pSockCon->link)
	{
		nErrorCode = WSAGetLastError();
		printf("[ERROR] Can not create socket. [Error Code: %d]", nErrorCode);
		delete pSockCon;
		pSockCon = nullptr;
		return false;
	}

	if (nullptr == CreateIoCompletionPort((HANDLE)pSockCon->link, pIOCPHandle, (DWORD)pSockCon, 0))
	{
		nErrorCode = WSAGetLastError();
		printf("[ERROR] Can not create IOCP for socket. [Error code: %d]", nErrorCode);
		SAFE_RELEASE_SOCKET(pSockCon->link);
		delete pSockCon;
		pSockCon = nullptr;
		return false;
	}

	return true;
}

bool NetWorkIOCPCore::ListenSocket(CORE_SOCKET& sock, CORE_SOCKETADDR* addr, int nListenCount)
{
	int nErrorCode = 0;
#pragma region bind socket
	if (SOCKET_ERROR == bind(sock, (CORE_SOCKETADDR*)&(addr), sizeof(CORE_SOCKETADDR)))
	{
		nErrorCode = WSAGetLastError();
		printf("[ERROR] Can not bind socket. [Error code: %d]", nErrorCode);
		SAFE_RELEASE_SOCKET(sock);
		return false;
	}
#pragma endregion

#pragma region socket begin listen
	if (SOCKET_ERROR == listen(sock, nListenCount))
	{
		nErrorCode = WSAGetLastError();
		printf("[ERROR] Can not listen socket. [Error code: %d]", nErrorCode);
		SAFE_RELEASE_SOCKET(sock);
		return false;
	}
#pragma endregion

	return true;
}

bool NetWorkIOCPCore::ConnectSocket(CORE_SOCKET& sock, CORE_SOCKETADDR* addr)
{
	//todo
	return true;
}

bool NetWorkIOCPCore::GetIOCPFunction(CORE_SOCKET& sock, GUID guidFunc, void* pFuncHandle)
{
	DWORD dwBytes = 0;
	int nErrorCode = 0;
	if (SOCKET_ERROR == WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidFunc,
		sizeof(guidFunc), &pFuncHandle, sizeof(pFuncHandle), &dwBytes, NULL, NULL))
	{
		nErrorCode = WSAGetLastError();
		printf("[ERROR] Can not get IOCP Function pointer, Error code[%d]", nErrorCode);
		SAFE_RELEASE_SOCKET(sock);
		return false;
	}

	return true;
}

bool NetWorkIOCPCore::CreateListenSocket(const char* strAddress, int nPort)
{
	if (!InitialSocket())
		return false;

	//	Initial IOCP
	if (!InitialIOCPHandle(m_pListenCon, m_pIOCPHandle))
	{
		printf("[ERROR] Initial IOCP handle Failed !!!!!!!");
		return false;
	}


	//	Initial address
	CORE_SOCKETADDR_IN sockAddr;
	if (nullptr == CreateSocketAddress(strAddress, nPort, sockAddr))
	{
		delete m_pListenCon;
		m_pListenCon = nullptr;
		return false;
	}

	//	bind and listen socket
	if (!ListenSocket(m_pListenCon->link, (CORE_SOCKETADDR*)&sockAddr, LISTEN_LINK_MAX))
	{
		delete m_pListenCon;
		m_pListenCon = nullptr;
		return false;
	}

	//	get accept extension function pointer
	if (!GetIOCPFunction(m_pListenCon->link, WSAID_ACCEPTEX, m_pIOCPAcceptHandle))
	{
		printf("[ERROR] Get IOCP accept extension function pointer failed.");
		delete m_pListenCon;
		m_pListenCon = nullptr;
		return false;
	}

	//	get accept socket address extension function pointer
	if (!GetIOCPFunction(m_pListenCon->link, WSAID_GETACCEPTEXSOCKADDRS, m_pIOCPAcceptSockAddrHandle))
	{
		printf("[ERROR] Get IOCP get accept socket address extension function pointer failed.");
		delete m_pListenCon;
		m_pListenCon = nullptr;
		return false;
	}



	return true;
}

bool NetWorkIOCPCore::DestroyIOCP()
{
	if (nullptr != m_pIOCPHandle)
	{
		CloseHandle(m_pIOCPHandle);
	}

	m_pIOCPHandle = nullptr;
}
#pragma endregion
