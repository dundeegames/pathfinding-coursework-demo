// /////////////////////////////////////////////////////////////////////////////
/*!	 																	      \n
*						GPSA - Pathfinding coursework	         			  \n
*                          by Jiri Klic, Dec 2014							  \n
*																			  \n
*/ /////////////////////////////////////////////////////////////////////////////



#ifndef GPSA_APPLICATION_H
#define GPSA_APPLICATION_H


// INCLUDES ////////////////////////////////////////////////////////////////////
#include <iostream>
#include <windows.h>
#include <time.h>

#include "ui/gui.h"
#include "board/board.h"
#include "astar/astar.h"
#include "lee/lee.h"
#include "hashing/hashing.h"


enum State {MAIN_MENU, INSTRUCTIONS_MENU, ABOUT_MENU, HASHING, LEE, ASTAR, END};



// CLASS ///////////////////////////////////////////////////////////////////////

class GPSAapplication
{

public:
	GPSAapplication();
	~GPSAapplication();

	void run();

private:

	Gui gui;
	bool appRunning;
	State state;			// State enum is part of gui.h

	Board* board;
	Astar* astar;
	Lee* lee;
	Hashing* hash;

	void Manage_Input();

};

#endif GPSA_APPLICATION_H