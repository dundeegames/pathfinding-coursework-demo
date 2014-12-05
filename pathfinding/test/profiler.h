///*****************************************************************************
///*****************************************************************************
///*****                                                                   *****
///*****           Profiler class - for memory and CPU analysis            *****
///*****                      by Jiri Klic, Dec 2014                       *****
///*****                                                                   *****
///*****   Timing functions based on CTimer class, available from          *****
///*****   http://xoax.net/cpp/crs/misc/lessons/HighResTimer/              *****
///*****   [2009]Xoax.Accessed[02.Dec.2014]                                *****
///*****                                                                   *****
///*****************************************************************************
///*****************************************************************************



#ifndef PROFILER_H
#define PROFILER_H


/// INCLUDES ///////////////////////////////////////////////////////////////////
#include <iostream>
#include <windows.h>






/// CLASS //////////////////////////////////////////////////////////////////////

class Profiler
{

public:
	Profiler();
	~Profiler();

	// timer
	void Start();
	void End();
	double GetTimeInSeconds();
	double GetTimeInMilliseconds();
	double GetTimeInMicroseconds();
	double GetTimeInNanoseconds();


	// memory


private:
	// timer	
	LARGE_INTEGER mqStart;
	LARGE_INTEGER mqEnd;
	LARGE_INTEGER mqFreq;

	// memory



};

#endif // PROFILER_H





/// USE EXAMPLE ////////////////////////////////////////////////////////////////
/**
void Bubblesort(int iaArray[], int iLength)
{
	for (int iIndex1 = 0; iIndex1 < iLength; ++iIndex1) {
		for (int iIndex2 = 0; iIndex2 < iLength - iIndex1 - 1; ++iIndex2) {
			if (iaArray[iIndex2] > iaArray[iIndex2 + 1]) {
				int iTemp = iaArray[iIndex2];
				iaArray[iIndex2] = iaArray[iIndex2 + 1];
				iaArray[iIndex2 + 1] = iTemp;
			}
		}
	}
}

int main() {

	using namespace std;
	
	// Fill an array with random integer values for sorting
	const int kiLength = 10000;
	int iaArray[kiLength];
	for (int iIndex = 0; iIndex < kiLength; ++iIndex) {
		iaArray[iIndex] = rand();
	}

	// Time the sort
	Profiler prof;
	prof.Start();
	Bubblesort(iaArray, kiLength);
	prof.End();

	cout << prof.GetTimeInSeconds() << " seconds" << endl;
	cout << prof.GetTimeInMilliseconds() << " milliseconds" << endl;
	cout << prof.GetTimeInMicroseconds() << " microseconds" << endl;
	cout << prof.GetTimeInNanoseconds() << " nanoseconds" << endl;
}
*/




// 80 //////////////////////////////////////////////////////////////////////////