
#ifndef __NET_WORK_CORE_IOCP_DEFINES_H__
#define __NET_WORK_CORE_IOCP_DEFINES_H__

#include "../../System/NetWorkCoreVariableDefines.h"
#include <vector>
#include <string>
#ifdef WIN32

#include <WS2tcpip.h>
#include <MSWSock.h>

#define SAFE_RELEASE_SOCKET(a) {if(INVALID_SOCKET != a){closesocket(a); a = INVALID_SOCKET;}}

#pragma region IOCP needed

//	完成端口操作类型
enum ECompletionPortOperateType
{
	ECPOT_NONE = 0,			//	不可用
	ECPOT_ACCEPT,			//	链接操作			
	ECPOT_WAIT,				//	等待操作
	ECPOT_RECIVE,			//	接受操作
	ECPOT_SEND,				//	发送操作

	ECPOT_MAX
};

typedef struct _WIN_PER_IO_CONTEXT
{
	OVERLAPPED		overlap;
	WSABUF			buffer;
	char			databuff[IO_BUFF_SIZE];
	int				len;
	CORE_SOCKET		link;
	ECompletionPortOperateType opType;

	_WIN_PER_IO_CONTEXT();
	virtual ~_WIN_PER_IO_CONTEXT();
	_WIN_PER_IO_CONTEXT& operator=(const _WIN_PER_IO_CONTEXT& rhv);

	void ResetDataBuf();
	void ResetOverlapBuf();

}WIN_OPERATE_IO_CONTEXT, *LPWIN_OPERATE_IO_CONTEXT;

typedef struct _WIN_PER_SOCKET_CONTEXT
{
	CORE_SOCKET		link;
	CORE_SOCKETADDR addr;
	int				revThreadID;
	int				sedThreadID;
	std::vector<LPWIN_OPERATE_IO_CONTEXT>	vIoOperate;

	_WIN_PER_SOCKET_CONTEXT();
	virtual ~_WIN_PER_SOCKET_CONTEXT();
	_WIN_PER_SOCKET_CONTEXT& operator=(const _WIN_PER_SOCKET_CONTEXT& rhv);

	void ClearOperate();
	LPWIN_OPERATE_IO_CONTEXT GetNewIoOperate();
	void RemoveIoOperate(LPWIN_OPERATE_IO_CONTEXT pIoContext);

}WIN_OPERATE_SOCKET_CONTEXT, *LPWIN_OPERATE_SOCKET_CONTEXT;
#pragma endregion

#define OPERATE_IO_CONTEXT WIN_OPERATE_IO_CONTEXT
#define LPOPERATE_IO_CONTEXT LPWIN_OPERATE_IO_CONTEXT
#define OPERATE_SOCKET_CONTEXT WIN_OPERATE_SOCKET_CONTEXT
#define LPOPERATE_SOCKET_CONTEXT LPWIN_OPERATE_SOCKET_CONTEXT

struct IOCPParams
{
	void* pIOCPHandle;
	void* pFuncExHandle;
	void* pGetFuncExSockAddrHandle;
	LPOPERATE_SOCKET_CONTEXT pFuncSockCon;
	Core_SockStoreKey	rAddressKey;

	IOCPParams();
	virtual ~IOCPParams();
	IOCPParams& operator=(const IOCPParams& rhv);

};

#endif	//	WIN32

#endif	//	__NET_WORK_CORE_IOCP_DEFINES_H__
