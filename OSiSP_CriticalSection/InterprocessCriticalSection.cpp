#include "stdafx.h"
#include "InterprocessCriticalSection.h"

TCHAR szName[] = TEXT("Global\\MyFileMappingObject");


InterprocessCriticalSection::InterprocessCriticalSection(bool initSharedData)
{
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,					// use paging file
		NULL,									// default security
		PAGE_READWRITE,							// read/write access
		0,										// maximum object size (high-order DWORD)
		sizeof(SharedData),						// maximum object size (low-order DWORD)
		szName);

	if (hMapFile == NULL)
	{
		FileLogger::Log("Could not create file mapping object");		
		return;
	}

	data = (SharedData*)MapViewOfFile(
		hMapFile,								// handle to map object
		FILE_MAP_ALL_ACCESS,					// read/write permission
		0,
		0,
		sizeof(SharedData));

	if (data == NULL)
	{
		FileLogger::Log("Could not map view of file");			
		CloseHandle(hMapFile);
		return;
	}

	if (initSharedData)
	{
		memset(data, 0, sizeof(SharedData));
	}
}

void InterprocessCriticalSection::EnterCriticalSection()
{
	while (InterlockedCompareExchange(&(data->counter), 1, 0) != 0);
}

void InterprocessCriticalSection::LeaveCtiticalSection()
{
	InterlockedDecrement(&(data->counter));
}


InterprocessCriticalSection::~InterprocessCriticalSection()
{
	UnmapViewOfFile(data);
	CloseHandle(hMapFile);
}
