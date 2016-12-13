#include "stdafx.h"
#include "ProcessManager.h"

HANDLE ProcessManager::isSonProcessEvent = CreateEvent(NULL, TRUE, FALSE, _T("IsSonProcessEvent"));

void ProcessManager::SetIsSonProcessEvent()
{
	SetEvent(isSonProcessEvent);
}

bool ProcessManager::IsSonProcess()
{
	if (WaitForSingleObject(isSonProcessEvent, 0) == WAIT_TIMEOUT)
	{
		return false;
	}
	return true;
}

void ProcessManager::RemoveIsSonProcessEvent()
{
	CloseHandle(isSonProcessEvent);
}
