/*
*******************************************************************************************
*****																				  *****
*****						 Gui class - by Jiri Klic, Nov 2014						  *****
*****																				  *****
*****				     the code inspired by Andre La Mothe's book					  *****
*****						The Black Art of 3D Games Programming					  *****
*****																				  *****
*****																				  *****
*******************************************************************************************
*/


#ifndef GUI_H
#define GUI_H

#include <windows.h>
#include <iostream>
#include <iomanip>		// std::setw
#include <conio.h>		// _kbhit()

//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h> 
//#include <time.h>



using std::setw;
using std::cout;

class Gui
{

public:
	
	Gui();
	~Gui();

	void init();

	bool loadMap(char* name);

	void Main_Menu();						// shows the MAIN MENU





private:

	CONSOLE_SCREEN_BUFFER_INFO con_info;	// holds screen info
	HANDLE hconsole;						// handle to console
	
	void Draw_String(int x,int y, char *string);				// draws variable at (x,y)
	void Draw_Integer(int x,int y, int n, int value);
	void Draw_Character(int x,int y, char c);
	void Draw_Float(int x,int y, int n, float value);

	void Press_Key(int x,int y, char *string);					// draws message at (x,y) and wait for key press to finish
	void Draw_Lines(int x, int y_1, int y_2, int limit);
	void Draw_Button(int x,int y, int colour, char *string);	// colour 0-15

	// min width = 17, min height = 5 
	void Draw_Banner(int x, int y, int colour, int width, int height);

	void Draw_Logo(int x, int y, int colour);					// "Pathfinding"
	void Draw_VertLine(int x, int y, int height);				// min height = 2

	// this function sets the color of the console output
	inline void Set_Color(int fcolor, int bcolor=0) {SetConsoleTextAttribute(hconsole,(WORD)((bcolor << 4) | fcolor));}

	void Clear_Screen();

};

#endif GUI_H