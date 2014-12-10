#include"gui.h"


#define WINDOW_WIDTH 80			// width of console window
#define WINDOW_HEIGHT 50		// height of console window



Gui::Gui()
{

}

// ------------------------------------------------------------------------------


Gui::~Gui()
{

}

// ------------------------------------------------------------------------------


void Gui::init()
{
	COORD console_size = {WINDOW_WIDTH,WINDOW_HEIGHT}; // size of console
	SMALL_RECT windowSize = {0, 0, console_size.X-1, console_size.Y-1};
    BOOL Absolute;

    //hconsole = GetStdHandle(STD_OUTPUT_HANDLE);


	// open i/o channel to console screen
	hconsole=CreateFile(TEXT("CONOUT$"),GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);


    Absolute = SetConsoleScreenBufferSize(hconsole, console_size);
	
    SetConsoleWindowInfo(hconsole, Absolute, &windowSize);

	// get details for console screen                       
	GetConsoleScreenBufferInfo(hconsole,&con_info);

}

// ------------------------------------------------------------------------------


bool Gui::loadMap(char* name)
{
	return true;
}

// ------------------------------------------------------------------------------

// this function draws a string at the given x,y
void Gui::Draw_String(int x,int y, char *string)
{
	COORD cursor_pos; // used to pass coords

	// set printing position
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hconsole,cursor_pos);

	// print the string in current color
	printf("%s",string);
}

// ------------------------------------------------------------------------------

// this function draws a integer at the given x,y with width n
void Gui::Draw_Integer(int x,int y, int n, int value)
{
	COORD cursor_pos; // used to pass coords

	// set printing position
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hconsole,cursor_pos);

	// print the integer in current color

	cout << setw(n);	// set width of integer to value n
	cout << value;		// display int value

}

// ------------------------------------------------------------------------------

// this function draws a character at the given x,y
void Gui::Draw_Character(int x,int y, char c)
{
	COORD cursor_pos; // used to pass coords

	// set printing position
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hconsole,cursor_pos);

	// print the character in current color
	printf("%c\n",c);
}

// ------------------------------------------------------------------------------

// this function draws a integer at the given x,y with width n
void Gui::Draw_Float(int x,int y, int n, float value)
{
	COORD cursor_pos; // used to pass coords

	// set printing position
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hconsole,cursor_pos);

	// print the float in current color

	cout << setw(n);	// set width of float to value n
	cout << value;		// display float value
}

// ------------------------------------------------------------------------------

// draws a string at the given x,y AND wait for key press to finish
void Gui::Press_Key(int x,int y, char *string)
{
	int  k = 7;							// lower values give faint colours

	while(!_kbhit()) {					// wait for you

		COORD cursor_pos; 					// used to pass coords

		// set printing position
		cursor_pos.X = x;
		cursor_pos.Y = y;
		SetConsoleCursorPosition(hconsole,cursor_pos);


		Set_Color(9+((k++)%7), 0);	// scroll thru colours 9 - 15 avoiding black
		printf("%s",string);		// print the string in current color
		Sleep(500);					// 500 fits in nicely with cursor blink rate
	}
}

// ------------------------------------------------------------------------------

// draws a 2 lines Starting at x, at height y_1 and y_2, of length = limit
void Gui::Draw_Lines(int x, int y_1, int y_2, int limit)
{
	for (int i = 0; i < limit; i++) {

		Draw_String(x+i,y_1,"-");
		Draw_String(x+i,y_2,"-");
		//Sleep(5);

	}
}

// ------------------------------------------------------------------------------

// draws button with a string at the given x,y and colour c
void Gui::Draw_Button(int x,int y, int colour, char *string)
{
	Set_Color(colour,0);						// colour 0-15

	int length = 0;
	for (int i = 0; string[i] != 0; i++) {		// get length of string
		length++;
	}


	Draw_String(x-2,y-1,".-");					// left side of button
	Draw_String(x-2,y,"| ");
	Draw_String(x-2,y+1,"'-");

	Draw_Lines(x, y-1, y+1, length);			// top and bottom
	Draw_String(x,y,string);					// text

	Draw_String(x+length,y-1,"-.");				// right side of button
	Draw_String(x+length,y," |");
	Draw_String(x+length,y+1,"-'");
}

// ------------------------------------------------------------------------------


void Gui::Clear_Screen()
{
	// this function clears the screen

	// set color to white on black
	Set_Color(15,0);

	// clear the screen
	for (int i=0; i <= WINDOW_HEIGHT; i++){
		Draw_String(0, WINDOW_HEIGHT-1,"\n");
	}
}


// ------------------------------------------------------------------------------


void Gui::Main_Menu()							// shows the MAIN MENU screen
{
	Clear_Screen();

	Draw_Frame(9, 1, 10, 60, 12);

	Draw_Banner(13, 4, 15, PATHFINDING);

	Draw_String(21,11,"Jiri Klic - Coursework, December 2014");


	Draw_String(0,20,"CHOOSE FROM THE FOLLOWING OPTIONS: ");

	Draw_Button(29,24, 14, " 1 - Hashing and GPSA  ");

	Draw_Button(29,27, 11, " 2 - The Lee algorithm ");

	Draw_Button(29,30, 10, " 3 - The A* algorithm  ");

	Draw_Button(29,33, 12, " 4 - Instructions      ");

	Draw_Button(29,36, 9,  " 5 - About the program ");

	Draw_Button(29,42, 8,  "        Q - QUIT       ");

	Draw_String(0,0,"");						// reset position of cursor

}

// ------------------------------------------------------------------------------

void Gui::Draw_Frame(int x, int y, int colour, int width, int height)
{
	Set_Color(colour,0);

	int size = 0;

	if(width < 17)		// error protection
	{
		width = 17;
	}

	if(height < 5)		// error protection
	{
		height = 5;
	}

	if(width > 17)
	{
		if( ( (width - 17) % 2) == 0)
		{
			size = (width - 17) / 2;
		}
		else
		{
			size = (width - 18) / 2;
		}
	}

	Draw_String((x+size+1), y,"      ''~``      ");
	Draw_String((x+size+1), y+1,"     ( o o )     ");
	Draw_String((x+size+1), y+2,".oooO--(_)--Oooo.");

	Draw_String((x+size+1), (y+height),"  .oooO          ");
	Draw_String((x+size+1), (y+height+1),"  (   )   Oooo.  ");
	Draw_String((x+size+1), (y+height+2),"---\\ (----(   )--");
	Draw_String((x+size+1), (y+height+3),"    \\_)    ) /   ");
	Draw_String((x+size+1), (y+height+4),"          (_/    ");

	if(size > 0)
	{
		Draw_Lines((x+1), (y+2), (y+height+2), size);
		Draw_Lines((x+size+18), (y+2), (y+height+2), size);
	}


	Draw_VertLine(x, (y+2), height);
	Draw_VertLine((x+(size*2)+18), (y+2), height);

		
	Set_Color(15,0);		// reset color to white on black
}


// ------------------------------------------------------------------------------


void Gui::Draw_VertLine(int x, int y, int height)
{
	Draw_String(x,y,"+");

	for(int i=1; i<height; i++)
	{
		Draw_String(x, (y+i),"|");
	}

	Draw_String(x, (y+height),"+");

}

// ------------------------------------------------------------------------------


void Gui::Instructions_Sreen()			// shows the INSTRUCTIONS screen
{
	Clear_Screen();

	Draw_Frame(9, 1, 10, 60, 12);
	Draw_Banner(11, 6, 12, INSTRUCTIONS);

	Set_Color(12,0);					// set colour to red

	Draw_String(2,20,
		"The quick brown fox jumps over the lazy dog.\n\
  The quick brown fox jumps over the lazy dog.The quick brown fox jumps\n\
   over the lazy dog. The quick brown fox jumps over the lazy dog.\n\
  The quick brown fox jumps over the lazy dog. The quick brown fox jumps \n\
  over the lazy dog");


	Press_Key(22,45,"press key to return to main menu...");

}

// ------------------------------------------------------------------------------


void Gui::About_Screen()				// shows the ABOUT screen
{
	Clear_Screen();

	Draw_Frame(9, 1, 10, 60, 12);
	Draw_Banner(19, 6, 9, ABOUT);

	Set_Color(9,0);						// set colour to blue

	Draw_String(2,20,
		"The quick brown fox jumps over the lazy dog.\n\
  The quick brown fox jumps over the lazy dog.The quick brown fox jumps\n\
   over the lazy dog. The quick brown fox jumps over the lazy dog.\n\
  The quick brown fox jumps over the lazy dog. The quick brown fox jumps \n\
  over the lazy dog");


	Press_Key(22,45,"press key to return to main menu...");

}

// ------------------------------------------------------------------------------


void Gui::GoodBye_Screen()				// shows the GOOD BYE screen
{
	Clear_Screen();			// clear the screen

	Draw_Lines(15,17,24,53);	// draws a 2 lines Starting at 15, at height 7 and 14, of length = 53
	Draw_Banner(19, 18, 15, GOOD_BYE);

	Press_Key(24,29,"press key to end the application ..");

	Draw_String(0,(WINDOW_HEIGHT-1),"");		// return cursor to bottom right

}

// ------------------------------------------------------------------------------


void Gui::GameOver_Screen()				// shows the GAME OVER screen
{
	Clear_Screen();			// clear the screen

	Draw_Lines(15,17,24,53);	// draws a 2 lines Starting at 15, at height 7 and 14, of length = 53
	Draw_Banner(16, 18, 15, GAME_OVER);

	Press_Key(27,29,"press key to end the game ...");

	Draw_String(0,(WINDOW_HEIGHT-1),"");		// return cursor to bottom right

}

// ------------------------------------------------------------------------------


void Gui::Draw_Banner(int x, int y, int colour, Banner ban_)
{
	Set_Color(colour,0);

	switch(ban_)
	{

	case PATHFINDING:

		Draw_String(x, y," ____       _   _      __ _           _ _             ");
		Draw_String(x, (y+1),"|  _ \\ __ _| |_| |__  / _(_)_ __   __| (_)_ __   __ _ ");
		Draw_String(x, (y+2),"| |_) / _` | __| '_ \\| |_| | '_ \\ / _` | | '_ \\ / _` |");
		Draw_String(x, (y+3),"|  __/ (_| | |_| | | |  _| | | | | (_| | | | | | (_| |");
		Draw_String(x, (y+4),"|_|   \\__,_|\\__|_| |_|_| |_|_| |_|\\__,_|_|_| |_|\\__, |");
		Draw_String(x, (y+5),"                                                |___/ ");
		break;

	case INSTRUCTIONS:

		Draw_String(x, y," ___           _                   _   _                 ");
		Draw_String(x, (y+1),"|_ _|_ __  ___| |_ _ __ _   _  ___| |_(_) ___  _ __  ___ ");
		Draw_String(x, (y+2)," | || '_ \\/ __| __| '__| | | |/ __| __| |/ _ \\| '_ \\/ __|");
		Draw_String(x, (y+3)," | || | | \\__ \\ |_| |  | |_| | (__| |_| | (_) | | | \\__ \\");
		Draw_String(x, (y+4),"|___|_| |_|___/\\__|_|   \\__,_|\\___|\\__|_|\\___/|_| |_|___/");
		break;

	case ABOUT:

		Draw_String(x, y,"    _      ____     ___    _   _   _____ ");
		Draw_String(x, (y+1),"   / \\    | __ )   / _ \\  | | | | |_   _|");
		Draw_String(x, (y+2),"  / _ \\   |  _ \\  | | | | | | | |   | |  ");
		Draw_String(x, (y+3)," / ___ \\  | |_) | | |_| | | |_| |   | |  ");
		Draw_String(x, (y+4),"/_/   \\_\\ |____/   \\___/   \\___/    |_|  ");
		break;

	case GOOD_BYE:

		Draw_String(x, y,"  ____                 _   ____             ");
		Draw_String(x, (y+1)," / ___| ___   ___   __| | | __ ) _   _  ___ ");
		Draw_String(x, (y+2),"| |  _ / _ \\ / _ \\ / _` | |  _ \\| | | |/ _ \\");
		Draw_String(x, (y+3),"| |_| | (_) | (_) | (_| | | |_) | |_| |  __/");
		Draw_String(x, (y+4)," \\____|\\___/ \\___/ \\__,_| |____/ \\__, |\\___|");
		Draw_String(x, (y+5),"                                 |___/      ");
		break;

	case GAME_OVER:

		Draw_String(x, y,"  ____                         ___                 ");
		Draw_String(x, (y+1)," / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ ");
		Draw_String(x, (y+2),"| |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|");
		Draw_String(x, (y+3),"| |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |");
		Draw_String(x, (y+4)," \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|");
		break;

	default:
		break;
	}

	Set_Color(15,0);		// reset color to white on black

}


/*

// ToDo: Figure out procedural tables


void Table1(int x, int y){

	Draw_String(x,y," _______________________________________________________________");
	Draw_String(x,y+1,"|                                                               |");
	Draw_String(x,y+2,"|                  Joe's Game Length Frequencies                |");
	Draw_String(x,y+3,"| ______________________________________________________________|");
	Draw_String(x,y+4,"|   |         |         |         |         |         |         |");
	Draw_String(x,y+5,"|   |    7    |    8    |    9    |    10   |    11   |   >11   |");
	Draw_String(x,y+6,"| __|_________|_________|_________|_________|_________|_________|");
	Draw_String(x,y+7,"|   |         |         |         |         |         |         |");
	Draw_String(x,y+8,"| # |         |         |         |         |         |         |");
	Draw_String(x,y+9,"| __|_________|_________|_________|_________|_________|_________|");
	Draw_String(x,y+10,"|   |         |         |         |         |         |         |");
	Draw_String(x,y+11,"| % |         |         |         |         |         |         |");
	Draw_String(x,y+12,"| __|_________|_________|_________|_________|_________|_________|");
	Draw_String(x,y+13,"|                                 |                             |");
	Draw_String(x,y+14,"| Number of Games:                | Average Length:             |");
	Draw_String(x,y+15,"| ________________________________|_____________________________|");

}

//--------------------------------------------------------------------------------------------

void Table2(int x, int y){

	Draw_String(x,y," __________________________________________________________________");
	Draw_String(x,y+1,"|                                                                  |");
	Draw_String(x,y+2,"|                       Joe's Percentage Success                   |");
	Draw_String(x,y+3,"| _________________________________________________________________|");
	Draw_String(x,y+4,"|      |         |         |         |         |         |         |");
	Draw_String(x,y+5,"| Rule |  Run 1  |  Run 2  |  Run 3  |  Run 4  |  Run 5  |  Mean   |");
	Draw_String(x,y+6,"| _____|_________|_________|_________|_________|_________|_________|");
	Draw_String(x,y+7,"|      |         |         |         |         |         |         |");
	Draw_String(x,y+8,"|   1  |         |         |         |         |         |         |");
	Draw_String(x,y+9,"| _____|_________|_________|_________|_________|_________|_________|");
	Draw_String(x,y+10,"|      |         |         |         |         |         |         |");
	Draw_String(x,y+11,"|   2  |         |         |         |         |         |         |");
	Draw_String(x,y+12,"| _____|_________|_________|_________|_________|_________|_________|");
	Draw_String(x,y+13,"|      |         |         |         |         |         |         |");
	Draw_String(x,y+14,"|   3  |         |         |         |         |         |         |");
	Draw_String(x,y+15,"| _____|_________|_________|_________|_________|_________|_________|");
	Draw_String(x,y+16,"|                                                                  |");
	Draw_String(x,y+17,"| Number of Games:                                                 |");
	Draw_String(x,y+18,"| _________________________________________________________________|");

}

*/
