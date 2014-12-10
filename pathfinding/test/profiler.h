// /////////////////////////////////////////////////////////////////////////////
/*!	 																	      \n
*               Profiler class - for memory and CPU analysis				  \n
*                          by Jiri Klic, Dec 2014							  \n
*	 	  																      \n
*          Timing functions based on CTimer class, available from			  \n
*          http://xoax.net/cpp/crs/misc/lessons/HighResTimer/				  \n
*          [2009]Xoax. Accessed[02.Dec.2014]								  \n
*	 	  																      \n
*          Memory analysis based on code from David Robert Nadeau,			  \n
*          avalilable from  http://NadeauSoftware.com/						  \n
*          Accessed[05.Dec.2014]											  \n
*																			  \n
*																			  \n
*/ /////////////////////////////////////////////////////////////////////////////



#ifndef PROFILER_H
#define PROFILER_H


// INCLUDES ////////////////////////////////////////////////////////////////////
#include <iostream>
#include <windows.h>
#include <psapi.h>






// CLASS ///////////////////////////////////////////////////////////////////////

class Profiler
{

public:
	Profiler();
	~Profiler();

	// timing
	void Start();
	void End();
	double GetTimeInSeconds();
	double GetTimeInMilliseconds();
	double GetTimeInMicroseconds();
	double GetTimeInNanoseconds();


	// memory analysis

	/**
	 * Returns the size of physical memory (RAM) in bytes.
	 */
	int getMemorySize();

	/**
	 * Returns the peak (maximum so far) resident set size (physical
	 * memory use) measured in bytes, or zero if the value cannot be
	 * determined on this OS.
	 */
	int getPeakRSS();

	/**
	 * Returns the current resident set size (physical memory use) measured
	 * in bytes, or zero if the value cannot be determined on this OS.
	 */
	int getCurrentRSS();




private:
	// timing	
	LARGE_INTEGER mqStart;
	LARGE_INTEGER mqEnd;
	LARGE_INTEGER mqFreq;

	// memory analysis



};

#endif // PROFILER_H




/**
// USE EXAMPLE /////////////////////////////////////////////////////////////////

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

	//Simply call either function to get the current and peak resident set size
	//in bytes, of the current process:
	int currentSize = prof.getCurrentRSS();
	int peakSize    = prof.getPeakRSS();

}
*/




// 80 //////////////////////////////////////////////////////////////////////////