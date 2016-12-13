#pragma once

#include <Windows.h>

class ProcessManager
{
public:
	static void SetIsSonProcessEvent();
	static bool IsSonProcess();
	static void RemoveIsSonProcessEvent();
private:
	static HANDLE isSonProcessEvent;
};

