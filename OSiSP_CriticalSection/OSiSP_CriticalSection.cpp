#include "stdafx.h"
#include "ProcessManager.h"
#include "InterprocessCriticalSection.h"

//functions declarations
int CreateChildProcess(STARTUPINFO &si, PROCESS_INFORMATION &pi, TCHAR* commandLine);

int _tmain(int argc, TCHAR *argv[])
{	
	STARTUPINFO si;
	PROCESS_INFORMATION childProc;

	bool isChileProcess = ProcessManager::IsSonProcess();
	
	InterprocessCriticalSection *criticalSection = new InterprocessCriticalSection();

	if (isChileProcess == false)
	{
		ProcessManager::SetIsSonProcessEvent();
		CreateChildProcess(si, childProc, argv[0]);
	}	

	for (int i = 0; i < 50; ++i)
	{
		criticalSection->EnterCriticalSection();

		printf_s("-----------------\nthread  enter: %d i: %d \n", GetCurrentThreadId(), i);
		Sleep(50);
		printf_s("thread  leave: %d i: %d\n", GetCurrentThreadId(), i);

		criticalSection->LeaveCtiticalSection();
	}

	if(isChileProcess == false)
	{
		WaitForSingleObject(childProc.hThread, INFINITE);
		CloseHandle(childProc.hThread);
		WaitForSingleObject(childProc.hProcess, INFINITE);
		CloseHandle(childProc.hProcess);

		//Wait child process finished
		ProcessManager::RemoveIsSonProcessEvent();
		criticalSection->RemoveCriticalSection();
		system("pause");
	}

	delete criticalSection;
    return 0;
}

int CreateChildProcess(STARTUPINFO &si, PROCESS_INFORMATION &pi, TCHAR* commandLine)
{
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	if (!CreateProcess(
		NULL,												// No module name (use command line)
		commandLine,										// Command line
		NULL,												// Process handle not inheritable
		NULL,												// Thread handle not inheritable
		FALSE,												// Set handle inheritance to FALSE
		0,													// No creation flags
		NULL,												// Use parent's environment block
		NULL,												// Use parent's starting directory 
		&si,												// Pointer to STARTUPINFO structure
		&pi)												// Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return -1;
	}

	return 0;
}
