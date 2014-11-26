#include "board.h"



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
	
}

// ------------------------------------------------------------------------------


Board::~Board()
{

}

// ------------------------------------------------------------------------------


void Board::init(Gui* ui_, int xpos_, int ypos_)
{
	ui = ui_;
	xPosition = xpos_;
	yPosition = ypos_;
}

// ------------------------------------------------------------------------------


void Board::loadMap(char* file_)
{
	ifstream inFile;					// input file object

	// read and translate input file	
	inFile.open(file_);


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


void Board::loadMap(MapType type_)
{
	switch(type_)
	{
	case MAP_A:
		for(int y = 0; y < BOARD_Y; y++)
		{
			for(int x = 0; x < BOARD_X; x++)
			{
				if(x == 0 || y == 0 || x == BOARD_X - 1 || y == BOARD_Y - 1)
					nodeMap[x][y].i = B_WALL;
				else
					nodeMap[x][y].i = B_EMPTY;
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

		break;

	case MAP_L:
		for(int y = 0; y < BOARD_Y; y++)
		{
			for(int x = 0; x < BOARD_X; x++)
			{
				if(x == 0 || y == 0 || x == BOARD_X - 1 || y == BOARD_Y - 1)
					nodeMap[x][y].i = B_WALL;
				else
					nodeMap[x][y].i = B_EMPTY;
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

		nodeMap[12][18].i = B_WALL;
		nodeMap[12][17].i = B_WALL;
		nodeMap[12][16].i = B_WALL;
		nodeMap[12][15].i = B_WALL;
		nodeMap[12][14].i = B_WALL;
		nodeMap[12][13].i = B_WALL;
		nodeMap[12][12].i = B_WALL;
		nodeMap[12][11].i = B_WALL;
		nodeMap[12][10].i = B_WALL;
					  
		nodeMap[13][18].i = B_WALL;
		nodeMap[13][17].i = B_WALL;
		nodeMap[13][16].i = B_WALL;
		nodeMap[13][15].i = B_WALL;
		nodeMap[13][14].i = B_WALL;
		nodeMap[13][13].i = B_WALL;
		nodeMap[13][12].i = B_WALL;
		nodeMap[13][11].i = B_WALL;
		nodeMap[13][10].i = B_WALL;

		nodeMap[14][10].i = B_WALL;
		nodeMap[14][11].i = B_WALL;
		nodeMap[15][10].i = B_WALL;
		nodeMap[15][11].i = B_WALL;
		nodeMap[16][10].i = B_WALL;
		nodeMap[16][11].i = B_WALL;
		break;


	default:
		break;
	}

}


// ------------------------------------------------------------------------------


void Board::setI(int x, int y, int i_)
{
	nodeMap[x][y].i = i_;
	
	switch(i_)
	{
	case B_EMPTY:
		//ui->Draw_String(((x*2)+xPosition), (y+yPosition), )
		//cout << "   ";
		break;

	case B_WALL:
		ui->Draw_String( ( (x*3) + xPosition), ( (y*2) + yPosition), "# ");
		//cout << "#  ";
		break;

	case B_START:
		ui->Draw_String( ( (x*3) + xPosition), ( (y*2) + yPosition), "S ");
		break;

	case B_END:
		ui->Draw_String(((x*3) + xPosition), ( (y*2) + yPosition), "T ");
		break;

	default:
		ui->Set_Color( ( (i_%14) + 1), 0);					// set colour to red
		ui->Draw_Integer(((x*3) + xPosition), ( (y*2) + yPosition), 1, i_);
		ui->Set_Color(15,0);								// reset color to white on black
		break;
	}
	
	

}

// ------------------------------------------------------------------------------

void Board::setFGH(int x, int y, int g_, int h_)
{
	nodeMap[x][y].f = g_ + h_;
	nodeMap[x][y].g = g_;
	nodeMap[x][y].h = h_;

	setI(x, y, g_);				// updates the i value and draws output
	//nodeMap[x][y].i = g_;
}

// ------------------------------------------------------------------------------


void Board::drawMap()
{
	ui->Clear_Screen();

	for(int y = 0; y < BOARD_Y; y++)
	{
		for(int x = 0; x < BOARD_X; x++)
		{
			switch(nodeMap[x][y].i)
			{
				case B_EMPTY:
					//ui->Draw_String(((x*2)+xPosition), (y+yPosition), )
					//cout << "   ";
					break;

				case B_WALL:
					ui->Draw_String( ( (x*3) + xPosition), ( (y*2) + yPosition), "#  ");
					//cout << "#  ";
					break;

				case B_START:
					ui->Draw_String( ( (x*3) + xPosition), ( (y*2) + yPosition), "S  ");
					break;

				case B_END:
					ui->Draw_String(((x*3) + xPosition), ( (y*2) + yPosition), "T  ");
					break;

				default:
					/*
					if(nodeMap[x][y].i < 10)
						cout << nodeMap[x][y].i << "  ";
					else
						cout << nodeMap[x][y].i << " ";
						*/
					break;
			}
		}
	}
	/*
	while(true)
	{


	}

	*/
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