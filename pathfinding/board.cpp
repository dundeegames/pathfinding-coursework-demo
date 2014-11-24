#include"board.h"

#include <iostream>

using std::cout;
using std::endl;

Board::Board()
{
	for(int y = 0; y < BOARD_Y; y++)
	{
		for(int x = 0; x < BOARD_X; x++)
		{
			if(x == 0 || y == 0 || x == BOARD_X - 1 || y == BOARD_Y - 1)
				board[x][y].setI(B_WALL);
			else
				board[x][y].setI(B_EMPTY);
		}
	}

	board[5][18].setI(B_WALL);
	board[5][17].setI(B_WALL);
	board[5][16].setI(B_WALL);
	board[5][15].setI(B_WALL);
	board[5][14].setI(B_WALL);
	board[5][13].setI(B_WALL);
	board[5][12].setI(B_WALL);

	board[4][18].setI(B_WALL);
	board[4][17].setI(B_WALL);
	board[4][16].setI(B_WALL);
	board[4][15].setI(B_WALL);
	board[4][14].setI(B_WALL);
	board[4][13].setI(B_WALL);
	board[4][12].setI(B_WALL);
}


Board::~Board()
{

}


void Board::draw()
{
	system("cls");

	for(int y = 0; y < BOARD_Y; y++)
	{
		cout << endl;
		for(int x = 0; x < BOARD_X; x++)
		{
			switch(board[x][y].getI())
			{
				case B_EMPTY:	cout << "   ";	break;
				case B_WALL:	cout << "#  ";	break;
				case B_START:	cout << "S  ";	break;
				case B_END:		cout << "T  ";	break;
				default:
					if(board[x][y].getI() < 10)
						cout << board[x][y].getI() << "  ";
					else
						cout << board[x][y].getI() << " ";
					break;
			}
		}
	}
	cout << endl << endl << endl;

}


void Board::clearBoard()
{
	for(int y = 0; y < BOARD_Y; y++)
	{
		for(int x = 0; x < BOARD_X; x++)
		{
			if(board[x][y].getI() != B_WALL && board[x][y].getI() != B_START && board[x][y].getI() != B_END)
				board[x][y].setI(B_EMPTY);
		}
	}

}


// LEE --------------------------------------

// type is either wall, empty or disctance #
void Board::setSquare(int x, int y, int type)
{
	intBoard[x][y] = type;
}

int Board::getSquare(int x, int y)
{
	return intBoard[x][y];
}

// ------------------------------------------





/*
// Lee

cBoard::cBoard()
{
	for(int y = 0; y < BOARD_Y; y++)
	{
		for(int x = 0; x < BOARD_X; x++)
		{
			if(x == 0 || y == 0 || x == BOARD_X - 1 || y == BOARD_Y - 1)
				board[x][y] = B_WALL;
			else
				board[x][y] = B_EMPTY;
		}
	}

	board[5][18] = B_WALL;
	board[5][17] = B_WALL;
	board[5][16] = B_WALL;
	board[5][15] = B_WALL;
	board[5][14] = B_WALL;
	board[5][13] = B_WALL;
	board[5][12] = B_WALL;

	board[4][18] = B_WALL;
	board[4][17] = B_WALL;
	board[4][16] = B_WALL;
	board[4][15] = B_WALL;
	board[4][14] = B_WALL;
	board[4][13] = B_WALL;
	board[4][12] = B_WALL;

	board[12][18] = B_WALL;
	board[12][17] = B_WALL;
	board[12][16] = B_WALL;
	board[12][15] = B_WALL;
	board[12][14] = B_WALL;
	board[12][13] = B_WALL;
	board[12][12] = B_WALL;
	board[12][11] = B_WALL;
	board[12][10] = B_WALL;

	board[13][18] = B_WALL;
	board[13][17] = B_WALL;
	board[13][16] = B_WALL;
	board[13][15] = B_WALL;
	board[13][14] = B_WALL;
	board[13][13] = B_WALL;
	board[13][12] = B_WALL;
	board[13][11] = B_WALL;
	board[13][10] = B_WALL;

	board[14][10] = B_WALL;
	board[14][11] = B_WALL;
	board[15][10] = B_WALL;
	board[15][11] = B_WALL;
	board[16][10] = B_WALL;
	board[16][11] = B_WALL;
}

void cBoard::draw()
{
	system("cls");

	// --------------------------------------

	for(int y = 0; y < BOARD_Y; y++)
	{
		cout << endl;
		for(int x = 0; x < BOARD_X; x++)
		{
			switch(board[x][y])
			{
				case B_EMPTY:	cout << "   ";	break;
				case B_WALL:	cout << "#  ";	break;
				case B_START:	cout << "S  ";	break;
				case B_END:		cout << "T  ";	break;
				default:
					if(board[x][y] < 10)
						cout << board[x][y] << "  ";
					else
						cout << board[x][y] << " ";
					break;
			}
		}
	}
	cout << endl << endl << endl;
}

// type is either wall, empty or disctance #
void cBoard::setSquare(int x, int y, int type)
{
	board[x][y] = type;
}

int cBoard::getSquare(int x, int y)
{
	return board[x][y];
}

void cBoard::clearPathing()
{
	for(int y = 0; y < BOARD_Y; y++)
	{
		for(int x = 0; x < BOARD_X; x++)
		{
			if(board[x][y] != B_WALL && board[x][y] != B_START && board[x][y] != B_END)
				board[x][y] = B_EMPTY;
		}
	}
}






*/