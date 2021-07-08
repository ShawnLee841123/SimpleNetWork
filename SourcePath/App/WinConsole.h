

#ifndef __WINDOWS_CONSOLE_H__
#define __WINDOWS_CONSOLE_H__

class WinConsole
{
public:
	WinConsole(void* pHandle);
	~WinConsole();

	void WorkingProcess();

	void SetEnable(bool bEnable);
	bool GetEnable();

protected:

	bool m_bEnable;

	void* m_pConsoleHandle;
};


#endif	//__WINDOWS_CONSOLE_H__
