// /////////////////////////////////////////////////////////////////////////////
/*!	 																	      \n
*			     Application Class - Pathfinding coursework      			  \n
*                          by Jiri Klic, Dec 2014							  \n
*																			  \n
*/ /////////////////////////////////////////////////////////////////////////////



#ifndef APPLICATION_H
#define APPLICATION_H


// INCLUDES ////////////////////////////////////////////////////////////////////
#include <iostream>
#include <windows.h>
#include <time.h>

#include "ui/gui.h"
#include "board/board.h"
#include "astar/astar.h"
#include "lee/lee.h"
#include "gpsa/gpsa.h"


enum State {MAIN_MENU, INSTRUCTIONS_MENU, ABOUT_MENU, HASHING, LEE, ASTAR, END};



// CLASS ///////////////////////////////////////////////////////////////////////

class Application
{

public:
	Application();
	~Application();

	void run();

private:

	Gui gui;
	bool appRunning;
	State state;			// State enum is part of gui.h

	Board* board;
	Astar* astar;
	Lee* lee;
	Gpsa* gpsa;

	void Manage_Input();

};

#endif // APPLICATION_H