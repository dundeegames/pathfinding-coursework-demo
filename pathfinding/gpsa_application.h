#ifndef GPSA_APPLICATION_H
#define GPSA_APPLICATION_H

#include"ui/gui.h"
#include <time.h>


enum State {MAIN_MENU, INSTRUCTIONS_MENU, ABOUT_MENU, HASHING, LEE, ASTAR, END};


class GPSAapplication
{

public:
	GPSAapplication();
	~GPSAapplication();

	void run();

private:

	Gui gui;
	State state;	// State enum is part of gui.h

	bool appRunning;

	void Manage_Input();

};

#endif GPSA_APPLICATION_H