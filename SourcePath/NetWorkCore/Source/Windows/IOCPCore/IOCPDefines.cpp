#include "../../../Include/Windows/IOCPCore/IOCPDefines.h"

#ifdef WIN32

#pragma region IO context
_WIN_PER_IO_CONTEXT::_WIN_PER_IO_CONTEXT(): link(INVALID_SOCKET), len(0)
{
	ResetDataBuf();
	ResetOverlapBuf();
	opType = ECPOT_NONE;
}

_WIN_PER_IO_CONTEXT::~_WIN_PER_IO_CONTEXT()
{
	ResetDataBuf();
	ResetOverlapBuf();
	opType = ECPOT_NONE;
	link = INVALID_SOCKET;
}

_WIN_PER_IO_CONTEXT& _WIN_PER_IO_CONTEXT::operator=(const _WIN_PER_IO_CONTEXT& rhv)
{
	opType = rhv.opType;
	link = rhv.link;
	memcpy(&overlap, &rhv.overlap, sizeof(OVERLAPPED));
	memcpy(&buffer, &rhv.overlap, sizeof(WSABUF));
	memcpy(databuff, rhv.databuff, sizeof(char) * IO_BUFF_SIZE);
	len = rhv.len;
	return *this;
}

void _WIN_PER_IO_CONTEXT::ResetDataBuf()
{
	ZeroMemory(databuff, sizeof(char) * IO_BUFF_SIZE);
	len = 0;
}

void _WIN_PER_IO_CONTEXT::ResetOverlapBuf()
{
	ZeroMemory(&overlap, sizeof(WSAOVERLAPPED));
}
#pragma endregion

#pragma region Socket context
_WIN_PER_SOCKET_CONTEXT::_WIN_PER_SOCKET_CONTEXT():link(INVALID_SOCKET), revThreadID(0),\
sedThreadID(0)
{
	vIoOperate.clear();
}

_WIN_PER_SOCKET_CONTEXT::~_WIN_PER_SOCKET_CONTEXT()
{
	revThreadID = 0;
	sedThreadID = 0;
	ClearOperate();
}

_WIN_PER_SOCKET_CONTEXT& _WIN_PER_SOCKET_CONTEXT::operator=(const _WIN_PER_SOCKET_CONTEXT& rhv)
{
	memcpy(&addr, &rhv.addr, sizeof(CORE_SOCKETADDR));
	link = rhv.link;
	revThreadID = rhv.revThreadID;
	sedThreadID = rhv.sedThreadID;
	int nIoCount = (int)rhv.vIoOperate.size();
	for (int i = 0; i < nIoCount; i++)
	{
		LPOPERATE_IO_CONTEXT pIo = rhv.vIoOperate[i];
		if (nullptr != pIo)
		{
			LPOPERATE_IO_CONTEXT pIoNew = GetNewIoOperate();
			*pIoNew = *pIo;
		}
	}

	return *this;
}

void _WIN_PER_SOCKET_CONTEXT::ClearOperate()
{
	int nIoCount = (int)vIoOperate.size();
	for (int i = 0; i < nIoCount; i++)
	{
		LPOPERATE_IO_CONTEXT pIo = vIoOperate[i];
		if (nullptr != pIo)
		{
			delete pIo;
		}

		pIo = nullptr;
	}

	vIoOperate.clear();
}

LPWIN_OPERATE_IO_CONTEXT _WIN_PER_SOCKET_CONTEXT::GetNewIoOperate()
{
	LPOPERATE_IO_CONTEXT pIo = new OPERATE_IO_CONTEXT();
	vIoOperate.push_back(pIo);

	return pIo;
}

void _WIN_PER_SOCKET_CONTEXT::RemoveIoOperate(LPWIN_OPERATE_IO_CONTEXT pIoContext)
{
	if (nullptr == pIoContext)
		return;

	int nIoCount = (int)vIoOperate.size();
	if (nIoCount <= 0)
		return;

	std::vector<LPOPERATE_IO_CONTEXT>::iterator iter = vIoOperate.begin();
	for (; iter != vIoOperate.end(); ++iter)
	{
		if ((*iter)->link == pIoContext->link)
		{
			vIoOperate.erase(iter);
			break;
		}
	}

	delete pIoContext;
	pIoContext = nullptr;
}
#pragma endregion

#endif