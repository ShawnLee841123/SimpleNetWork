
#include <stdio.h>
#include "WinConsole.h"
#include "../CoreLib/ThreadCore/Include/AutoLock.h"

WinConsole* g_pWinConsole = nullptr;

bool MainDestroy()
{
	if (nullptr != g_pWinConsole)
	{
		delete g_pWinConsole;
	}

	g_pWinConsole = nullptr;
	return true;
}

#ifdef _WIN_
#include <windows.h>
static BOOL WINAPI console_ctrl_handler(DWORD type)
{
	ThreadAutoLock oLock;
	switch (type)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
	case CTRL_LOGOFF_EVENT:
	{
		return MainDestroy();
	}
	break;
	default:
		return FALSE;
	}
	return TRUE;
}
#endif

bool ExeMain()
{
#ifdef _WIN_
	SetConsoleCtrlHandler(console_ctrl_handler, true);
#endif
	void* pHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	g_pWinConsole = new WinConsole(pHandle);

	g_pWinConsole->WorkingProcess();

	MainDestroy();
	pHandle = nullptr;
	return true;
}

void main()
{
	int nError;
	try
	{
		ExeMain();
	}
	catch (...)
	{
		nError = GetLastError();
	}

	if (nError != 0)
	{
		printf("Last Error[%d]", nError);
	}

	getchar();
}