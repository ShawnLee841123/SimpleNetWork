#include "WinConsole.h"
#include "MultyThreadManager.h"


WinConsole::WinConsole(void* pHandle): m_bEnable(false), m_pConsoleHandle(pHandle)
{}

WinConsole::~WinConsole()
{
	m_pConsoleHandle = nullptr;
}

void WinConsole::WorkingProcess()
{
	if (nullptr == m_pConsoleHandle)
	{
		return;
	}

	m_bEnable = MultyThreadManager::Get()->Initial(m_pConsoleHandle);
	MultyThreadManager::Get()->InitialThread(5);
	MultyThreadManager::Get()->StartThread();
	while (m_bEnable)
	{

	}
	MultyThreadManager::Get()->DestroyThread();
}

void WinConsole::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

bool WinConsole::GetEnable()
{
	return m_bEnable;
}
