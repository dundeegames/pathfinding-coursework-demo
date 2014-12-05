#include "profiler.h"



Profiler::Profiler()
{

}


Profiler::~Profiler()
{

}


// -----------------------------------------------------------------------------

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


// 80 //////////////////////////////////////////////////////////////////////////