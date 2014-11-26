#include"gpsa_application.h"


GPSAapplication::GPSAapplication()
{
	// seed the random number generator with time
	srand((unsigned)time(NULL));

	appRunning = true;
	state = MAIN_MENU;


}


GPSAapplication::~GPSAapplication()
{

}


void GPSAapplication::run()
{
	gui.init();
	

	while(appRunning)
	{
		switch(state)
		{
		case MAIN_MENU:
			gui.Main_Menu();
			Manage_Input();
			break;

		case INSTRUCTIONS_MENU:
			gui.Instructions_Sreen();
			state = MAIN_MENU;
			break;

		case ABOUT_MENU:
			gui.About_Screen();
			state = MAIN_MENU;
			break;

		case HASHING:

			state = MAIN_MENU;
			break;

		case LEE:
			board = new Board();
			board->init(&gui, 11, 5);
			board->loadMap(MAP_L);
			board->drawMap();

			lee = new Lee();

			lee->generatePath(point(2, 5, B_START), point(15, 17, B_END), board);

			Sleep(1000);

			board->loadMap(MAP_L);		// clear pathing
			board->drawMap();

			lee->drawPath();

			gui.Press_Key(22,46,"press any key to return to main menu..");

			delete lee;
			delete board;
			state = MAIN_MENU;
			break;

		case ASTAR:
			board = new Board();
			board->init(&gui, 11, 5);
			board->loadMap(MAP_A);
			board->drawMap();

			astar.generatePath(Vector(2, 16), Vector(15, 10), board);

			gui.Press_Key(22,46,"press any key to return to main menu..");

			delete board;

			state = MAIN_MENU;
			break;

		case END:
			gui.GoodBye_Screen();
			appRunning = false;
			break;


		default:
			break;
		}

	}

}

// ------------------------------------------------------------------------------


void GPSAapplication::Manage_Input()
{
	char key;

	// SECTION: get player input
	while (true)
	{

		if(_kbhit())					// detect keyboard hit
		{
			key = toupper(_getch());

			// QUIT
			if(key=='Q' || key==27)
			{
				state = END;
				break;
			}
	
			// 
			else if(key=='1' || key==49)
			{
				state = HASHING;
				break;
			}

			// 
			else if(key=='2' || key==50)
			{
				state = LEE;
				break;
			}

			// 
			else if(key=='3' || key==51)
			{
				state = ASTAR;
				break;
			}

			// 
			else if(key=='4' || key==52)
			{
				state = INSTRUCTIONS_MENU;
				break;
			}

		
			// 
			else if(key=='5' || key==53)
			{
				state = ABOUT_MENU;
				break;
			}

		}

	}

}

// ------------------------------------------------------------------------------


/*

bool Play_Again() {				// this function asks if you want to play again

	bool x = 0;					//play again? 1=yes, 0=no

	Draw_String(23,14,"DO YOU WANT TO PLAY AGAIN?   es /  o");

	Set_Color(10,0);			// set colour to green
	Draw_String(51,14,"Y");

	Set_Color(12,0);			// set colour to red
	Draw_String(57,14,"N");


	while(true){

		if (_kbhit()) {						// get keyboard data, and filter it
		
		   key = toupper(_getch());
		
			// YES
			if (key=='Y' || key==89) {
				x = !x;
				break;
			}
		
			// NO
			if (key=='N' || key==78) {
				break;
				
			}

				 
	 	}	

		
	}

return x;

}	// end Play_Again

*/