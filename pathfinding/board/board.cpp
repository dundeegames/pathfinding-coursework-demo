#include "board.h"

#include <iostream>
#include <fstream>
//#include <string>
using namespace std;

//using std::cout;
//using std::endl;


Node::Node()
{
	i = 0;
	f = 0;
	g = 0;
	h = 0;
}

// ------------------------------------------------------------------------------

Node::Node(int i_)
{
	i = i_;
	f = 0;
	g = 0;
	h = 0;
}

// ------------------------------------------------------------------------------

Node::Node(int f_, int g_, int h_, int i_)
{
	i = i_;
	f = f_;
	g = g_;
	h = h_;
}

// ------------------------------------------------------------------------------


Board::Board()
{
	for(int y = 0; y < BOARD_Y; y++)
	{
		for(int x = 0; x < BOARD_X; x++)
		{
			if(x == 0 || y == 0 || x == BOARD_X - 1 || y == BOARD_Y - 1)
				nodeMap[BOARD_X][BOARD_Y].i = B_WALL;
			else
				nodeMap[BOARD_X][BOARD_Y].i = B_EMPTY;
		}
	}

	nodeMap[5][18].i = B_WALL;
	nodeMap[5][17].i = B_WALL;
	nodeMap[5][16].i = B_WALL;
	nodeMap[5][15].i = B_WALL;
	nodeMap[5][14].i = B_WALL;
	nodeMap[5][13].i = B_WALL;
	nodeMap[5][12].i = B_WALL;
	
	nodeMap[4][18].i = B_WALL;
	nodeMap[4][17].i = B_WALL;
	nodeMap[4][16].i = B_WALL;
	nodeMap[4][15].i = B_WALL;
	nodeMap[4][14].i = B_WALL;
	nodeMap[4][13].i = B_WALL;
	nodeMap[4][12].i = B_WALL;
}

// ------------------------------------------------------------------------------

Board::~Board()
{

}

// ------------------------------------------------------------------------------


void Board::loadMap(char* name_)
{

	ifstream inFile;					// input file object

	// read and translate input file	
	inFile.open(name_);


	if(inFile.is_open())
	{
		// get size of the input file
		inFile.seekg (0,inFile.end);
		long size = (long)inFile.tellg();
		inFile.seekg (0);

	
		char* buffer = new char[size];			// allocate memory for file content

		inFile.read (buffer,size);				// read content of inFile

		// load buffer into nodeMap[][] --------------------
		
		// buffer iterator
		int i = 0;
		// nodeMap iterators
		int rows=0;
		int columns=0;

		while(rows < BOARD_Y)			
		{
			while(true)
			{
				if((buffer[i] != '\n') && (columns < BOARD_X))
				{
					switch(buffer[i])
					{
					case ' ':
						nodeMap[rows][columns].i = B_EMPTY;
						break;

					case '#':
						nodeMap[rows][columns].i = B_WALL;
						break;

					case 'S':
						nodeMap[rows][columns].i = B_START;
						break;

					case 'T':
						nodeMap[rows][columns].i = B_END;
						break;

					default:
						break;
					}
					columns++;
					i++;
				}
				else
				{
					columns = 0;
					i++;
					break;
				}			
			}

			rows++;
		}

		// release dynamically-allocated memory
		delete[] buffer;
	
	}

}

// ------------------------------------------------------------------------------


void Board::setI(int x, int y, int i_)
{
	nodeMap[BOARD_X][BOARD_Y].i = i_;
}

// ------------------------------------------------------------------------------

void Board::setFGH(int x, int y, int g_, int h_)
{
	nodeMap[BOARD_X][BOARD_Y].f = g_ + h_;
	nodeMap[BOARD_X][BOARD_Y].g = g_;
	nodeMap[BOARD_X][BOARD_Y].h = h_;
	nodeMap[BOARD_X][BOARD_Y].i = g_;
}

// ------------------------------------------------------------------------------


void Board::draw()
{
	system("cls");

	for(int y = 0; y < BOARD_Y; y++)
	{
		cout << endl;
		for(int x = 0; x < BOARD_X; x++)
		{
			switch(nodeMap[x][y].i)
			{
				case B_EMPTY:	cout << "   ";	break;
				case B_WALL:	cout << "#  ";	break;
				case B_START:	cout << "S  ";	break;
				case B_END:		cout << "T  ";	break;
				default:
					if(nodeMap[x][y].i < 10)
						cout << nodeMap[x][y].i << "  ";
					else
						cout << nodeMap[x][y].i << " ";
					break;
			}
		}
	}
	cout << endl << endl << endl;

}

// ------------------------------------------------------------------------------


void Board::clearBoard()
{
	for(int y = 0; y < BOARD_Y; y++)
	{
		for(int x = 0; x < BOARD_X; x++)
		{
			if(nodeMap[x][y].i != B_WALL && nodeMap[x][y].i != B_START && nodeMap[x][y].i != B_END)
				nodeMap[x][y].i = B_EMPTY;
		}
	}

}

// ------------------------------------------------------------------------------


Node Board::getNode(int x, int y)
{
	return nodeMap[x][y];
}

// ------------------------------------------------------------------------------


/*
// LEE --------------------------------------

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