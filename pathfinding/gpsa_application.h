#ifndef GPSA_APPLICATION_H
#define GPSA_APPLICATION_H

#include"ui/gui.h"
#include <time.h>

class GPSAapplication
{

public:
	GPSAapplication();
	~GPSAapplication();

	void run();

private:

	Gui gui;

};

#endif GPSA_APPLICATION_H