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
    bool Absolute;

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


void Gui::Draw_String(int x,int y, char *string)
{
	// this function draws a string at the given x,y

	COORD cursor_pos; // used to pass coords

	// set printing position
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hconsole,cursor_pos);

	// print the string in current color
	printf("%s",string);
}

// ------------------------------------------------------------------------------


void Gui::Draw_Integer(int x,int y, int n, int value)
{
	// this function draws a integer at the given x,y with width n

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


void Gui::Draw_Character(int x,int y, char c)
{
	// this function draws a character at the given x,y

	COORD cursor_pos; // used to pass coords

	// set printing position
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hconsole,cursor_pos);

	// print the character in current color
	printf("%c\n",c);
}

// ------------------------------------------------------------------------------


void Gui::Draw_Float(int x,int y, int n, float value)
{
	// this function draws a integer at the given x,y with width n

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


void Gui::Press_Key(int x,int y, char *string)
{
	// this function draws a string at the given x,y AND wait for key press to finish

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


void Gui::Draw_Lines(int x, int y_1, int y_2, int limit)
{
	// this function draws a 2 lines Starting at x, at height y_1 and y_2, of length = limit

	for (int i = 0; i < limit; i++) {

		Draw_String(x+i,y_1,"-");
		Draw_String(x+i,y_2,"-");
		//Sleep(5);

	}
}

// ------------------------------------------------------------------------------


void Gui::Draw_Button(int x,int y, int colour, char *string)
{
	// this function draws button with a string at the given x,y and colour c

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


void Gui::Main_Menu()
{
	// this function shows the MAIN MENU

	Clear_Screen();			// clear the screen

	Draw_Banner(9, 1, 10, 60, 12);

	Draw_Logo(13, 4, 15);
	Draw_String(21,11,"Jiri Klic - Coursework, November 2014");


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

void Gui::Draw_Banner(int x, int y, int colour, int width, int height)
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


void Gui::Draw_Logo(int x, int y, int colour)
{
	Set_Color(colour,0);

	Draw_String(x, y," ____       _   _      __ _           _ _             ");
	Draw_String(x, (y+1),"|  _ \\ __ _| |_| |__  / _(_)_ __   __| (_)_ __   __ _ ");
	Draw_String(x, (y+2),"| |_) / _` | __| '_ \\| |_| | '_ \\ / _` | | '_ \\ / _` |");
	Draw_String(x, (y+3),"|  __/ (_| | |_| | | |  _| | | | | (_| | | | | | (_| |");
	Draw_String(x, (y+4),"|_|   \\__,_|\\__|_| |_|_| |_|_| |_|\\__,_|_|_| |_|\\__, |");
	Draw_String(x, (y+5),"                                                |___/ ");

	Set_Color(15,0);		// reset color to white on black
}




/*

void Rules_Screen() {		// this function shows the RULES SCREEN

	Clear_Screen();						// clear the screen

	Set_Color(12,0);					// set colour to red

	Draw_Lines(0,2,9,80);				// draws a 2 lines Starting at 0, at height 1 and 8, of length = 80

	Draw_String(20,3," ____    _   _   _       _____   ____  ");
	Draw_String(20,4,"|  _ \\  | | | | | |     | ____| / ___| ");
	Draw_String(20,5,"| |_) | | | | | | |     |  _|   \\___ \\ ");
	Draw_String(20,6,"|  _ <  | |_| | | |___  | |___   ___) |");
	Draw_String(20,7,"|_| \\_\\  \\___/  |_____| |_____| |____/ ");


	Draw_String(0,15,"Joe and Sid have devised a new game.");
	Draw_String(0,17,"They each start with a score of 301 and aim to reduce this to zero as quickly");
	Draw_String(0,18,"as possible by each throwing one dart per turn. The dart board has a bull");
	Draw_String(0,19,"and twenty segments around the bull only. There are no trebles, doubles or outer");
	Draw_String(0,20,"Games must end from a score of fifty by hitting the bull. Any other score");
	Draw_String(0,21,"that would take the total below fifty is ignored.");
	Draw_String(0,23,"To home in on a final score of fifty you need to be able to throw at any given");
	Draw_String(0,24,"single number in the range one to twenty e.g. from sixty seven you would aim");
	Draw_String(0,25,"for seventeen.");
	Draw_String(0,30,"                Have fun! :-)");

	Press_Key(22,35,"press key to return to main menu...");



} // end Rules_Screen

//---------------------------------------------------------------------------------------------



void About_Screen() {		// this function shows the ABOUT SCREEN

	Clear_Screen();						// clear the screen

	Set_Color(9,0);						// set colour to blue

	Draw_Lines(0,2,9,80);				// draws a 2 lines Starting at 0, at height 1 and 8, of length = 80

	Draw_String(20,3,"    _      ____     ___    _   _   _____ ");
	Draw_String(20,4,"   / \\    | __ )   / _ \\  | | | | |_   _|");
	Draw_String(20,5,"  / _ \\   |  _ \\  | | | | | | | |   | |  ");
	Draw_String(20,6," / ___ \\  | |_) | | |_| | | |_| |   | |  ");
	Draw_String(20,7,"/_/   \\_\\ |____/   \\___/   \\___/    |_|  ");


	Draw_String(0,15,"A game fragment adapted from Andre La Mothe's book");
	Draw_String(0,16,"The Black Art of 3D Games Programming");

	Draw_String(0,18,"I have rewritten \"DARTS\" from scratch. However, I am still using as template");
	Draw_String(0,19,"the coordinate system and some functions. Therefore even when I do not call");
	Draw_String(0,20,"the game \"Based on book - The Black Art of 3D Games Programming\" any more,");
	Draw_String(0,21,"I still do keep the references to it.");

	Draw_String(0,23,"LaMothe, Andre [1995] - Black Art of 3D Game Programming:");
	Draw_String(0,24,"Writing Your Own High-Speed 3D Polygon Video Games in C, Waite Group Press");


	Press_Key(22,35,"press key to return to main menu...");



} // end About_Screen


//--------------------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------------------

void GameOver_Screen() {		// this function shows the GAME OVER SCREEN

	Clear_Screen();			// clear the screen

	Set_Color(15,0);		// set colour to white

	Draw_Lines(15,17,24,53);	// draws a 2 lines Starting at 15, at height 7 and 14, of length = 53

	Draw_String(10,18,"        ____                         ___                 ");
	Draw_String(10,19,"       / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ ");
	Draw_String(10,20,"      | |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|");
	Draw_String(10,21,"      | |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |");
	Draw_String(10,22,"       \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|");


	Press_Key(27,29,"press key to end the game ...");


} // end GameOver_Screen

//--------------------------------------------------------------------------------------------

void Main_Menu() {		
// this function shows the MAIN MENU

	Clear_Screen();			// clear the screen

	Set_Color(15,0);		// set colour to white

	Draw_Lines(0,0,11,80);	// draws a 2 lines Starting at 0, at height 0 and 11, of length = 80

	Draw_String(5,1," _____               _____    _______    _____ ");
	Draw_String(5,2,"|  __ \\      /\\     |  __ \\  |__   __|  / ____|    Jiri Klic, March 2014");
	Draw_String(5,3,"| |  | |    /  \\    | |__) |    | |    | (___  ");
	Draw_String(5,4,"| |  | |   / /\\ \\   |  _  /     | |     \\___ \\        C++ Coursework");
	Draw_String(5,5,"| |__| |  / ____ \\  | | \\ \\     | |     ____) |");
	Draw_String(5,6,"|_____/  /_/    \\_\\ |_|  \\_\\    |_|    |_____/      ____   ");
	Draw_String(5,7,"                            _____...........__     /    '. ");
	Draw_String(5,8,"                     ---===<_____||| || :::|__||>=<=------)");
	Draw_String(5,9,"                                 '''''''''''       \\____.' ");
	//Draw_String(25,10,"by Jiri KLic, C++ Lab - Week 05");
	

	Draw_String(0,15,"CHOOSE FROM THE FOLLOWING OPTIONS: ");

	Draw_Button(32,19, 14, " 1 - JOE PRACTISE   ");

	Draw_Button(32,22, 14, " 2 - JOE GOES FIRST ");

	Draw_Button(32,25, 10, " 3 - SID GOES FIRST ");

	Draw_Button(32,28, 11, " 4 - JOE VS SID     ");

	Draw_Button(32,31, 12, " 5 - RULES          ");

	Draw_Button(32,34, 9, " 6 - ABOUT          ");

	Draw_Button(32,37, 8, " Q - QUIT GAME      ");

	Draw_String(0,0,"");						// reset position of cursor


} // end Main_Menu

//--------------------------------------------------------------------------------------------

void Menu_Options() {

	// SECTION: get player input
	while (true) {

		if (_kbhit()) {					// detect keyboard hit

			key = toupper(_getch());

				// QUIT
				if (key=='Q' || key==27) {
					game_running = false;
					game_start = false;
					break;
				}
	
				// START - Joe Practise
				else if (key=='1' || key==49) {
					option = 1;
					break;
				}

				// START - Joe goes first
				else if (key=='2' || key==50) {
					option = 2;
					break;
				}

				// START - Sid goes first
				else if (key=='3' || key==51) {
					option = 3;
					break;
				}

				// START - Joe vs Sid
				else if (key=='4' || key==52) {
					option = 4;
					break;
				}

		
				// RULES
				else if (key=='5' || key==53) {
					Rules_Screen();			// shows the RULES SCREEN
					Main_Menu();			// shows the MAIN MENU
					continue;
				}

				// ABOUT
				else if (key=='6' || key==54) {
					About_Screen();			// shows the ABOUT SCREEN
					Main_Menu();			// shows the MAIN MENU
					continue;
				}

		}
	}
}
//--------------------------------------------------------------------------------------------


void Draw_Score (int player1, int player2) {					// this function draws the Score

	Set_Color(15,0);						// set colour to white

	//Draw_String(20,0,"Score:             :");
	 
	Set_Color(14,0);							// set colour to blue and print player's Score
	Draw_String(5,3,"JOE: ");			
	Draw_Integer(11,3,3, player1 );	
	 
	Set_Color(10,0);						// set colour to red and print computer's Score
	Draw_String(66,3,"SID: ");		
	Draw_Integer(72,3,3, player2 );

} // end Draw_Score

//--------------------------------------------------------------------------------------------
*/
