#include "profiler.h"



Profiler::Profiler()
{

}


Profiler::~Profiler()
{

}


// TIMING //////////////////////////////////////////////////////////////////////

void Profiler::Start()
{
	QueryPerformanceCounter(&mqStart);
}


// -----------------------------------------------------------------------------

void Profiler::End()
{
	QueryPerformanceCounter(&mqEnd);
}


// -----------------------------------------------------------------------------

double Profiler::GetTimeInSeconds()
{
	return (mqEnd.QuadPart - mqStart.QuadPart)/(double)mqFreq.QuadPart;
}


// -----------------------------------------------------------------------------

double Profiler::GetTimeInMilliseconds()
{
	return (1.0e3*(mqEnd.QuadPart - mqStart.QuadPart))/mqFreq.QuadPart;
}


// -----------------------------------------------------------------------------

double Profiler::GetTimeInMicroseconds()
{
	return (1.0e6*(mqEnd.QuadPart - mqStart.QuadPart))/mqFreq.QuadPart;
}


// -----------------------------------------------------------------------------

double Profiler::GetTimeInNanoseconds()
{
	return (1.0e9*(mqEnd.QuadPart - mqStart.QuadPart))/mqFreq.QuadPart;
}



// MEMORY ANALYSIS /////////////////////////////////////////////////////////////

int Profiler::getMemorySize()
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx( &status );
	return (int)status.ullTotalPhys;
}


// -----------------------------------------------------------------------------

int Profiler::getPeakRSS()
{
	PROCESS_MEMORY_COUNTERS info;

	//! error LNK2001: unresolved external symbol _GetProcessMemoryInfo@12
	//GetProcessMemoryInfo( GetCurrentProcess(), &info, sizeof(info) );

	return (int)info.PeakWorkingSetSize;
}


// -----------------------------------------------------------------------------

int Profiler::getCurrentRSS()
{
	PROCESS_MEMORY_COUNTERS info;

	//! error LNK2001: unresolved external symbol _GetProcessMemoryInfo@12
	//GetProcessMemoryInfo( GetCurrentProcess(), &info, sizeof(info) );

	return (int)info.WorkingSetSize;
}


// -----------------------------------------------------------------------------




// 80 //////////////////////////////////////////////////////////////////////////