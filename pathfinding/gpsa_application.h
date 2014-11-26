#ifndef GPSA_APPLICATION_H
#define GPSA_APPLICATION_H

#include <iostream>
#include <windows.h>
#include <time.h>

#include "ui/gui.h"
#include "board/board.h"
#include "astar/astar.h"
#include "lee/lee.h"


enum State {MAIN_MENU, INSTRUCTIONS_MENU, ABOUT_MENU, HASHING, LEE, ASTAR, END};


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
	Astar astar;
	Lee* lee;

	void Manage_Input();

};

#endif GPSA_APPLICATION_H