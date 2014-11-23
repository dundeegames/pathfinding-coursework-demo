#include"gpsa_application.h"


GPSAapplication::GPSAapplication()
{
	// seed the random number generator with time
	srand((unsigned)time(NULL));
}


GPSAapplication::~GPSAapplication()
{

}


void GPSAapplication::run()
{
	gui.init();

	gui.Main_Menu();

	while(true)
	{


	}

}