#pragma once

#include <Windows.h>
#include "FileLogger.h"

class InterprocessCriticalSection
{
public:
	InterprocessCriticalSection();
	void EnterCriticalSection();
	void LeaveCtiticalSection();
	void RemoveCriticalSection();
	~InterprocessCriticalSection();
private:
	HANDLE hMapFile;

	struct SharedData
	{
		volatile unsigned long long counter;	
		volatile unsigned long long isInit;				
	};

	SharedData *data;


};

