#pragma once

#include <Windows.h>
#include "FileLogger.h"

class InterprocessCriticalSection
{
public:
	InterprocessCriticalSection(bool initSharedData);
	void EnterCriticalSection();
	void LeaveCtiticalSection();
	~InterprocessCriticalSection();
private:
	HANDLE hMapFile;

	struct SharedData
	{
		volatile unsigned long long counter;		
	};

	SharedData *data;


};

