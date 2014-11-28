#include "board.h"


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
						nodeMap[rows][columns].init(B_EMPTY);
						break;

					case '#':
						nodeMap[rows][columns].init(B_WALL);
						break;

					case 'S':
						nodeMap[rows][columns].init(B_START);
						break;

					case 'T':
						nodeMap[rows][columns].init(B_END);
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
					nodeMap[x][y].init(B_WALL);
				else
					nodeMap[x][y].init(B_EMPTY);
			}
		}

		nodeMap[5][18].init(B_WALL);
		nodeMap[5][17].init(B_WALL);
		nodeMap[5][16].init(B_WALL);
		nodeMap[5][15].init(B_WALL);
		nodeMap[5][14].init(B_WALL);
		nodeMap[5][13].init(B_WALL);
		nodeMap[5][12].init(B_WALL);
					  
		nodeMap[4][18].init(B_WALL);
		nodeMap[4][17].init(B_WALL);
		nodeMap[4][16].init(B_WALL);
		nodeMap[4][15].init(B_WALL);
		nodeMap[4][14].init(B_WALL);
		nodeMap[4][13].init(B_WALL);
		nodeMap[4][12].init(B_WALL);

		break;

	case MAP_L:
		for(int y = 0; y < BOARD_Y; y++)
		{
			for(int x = 0; x < BOARD_X; x++)
			{
				if(x == 0 || y == 0 || x == BOARD_X - 1 || y == BOARD_Y - 1)
					nodeMap[x][y].init(B_WALL);
				else
					nodeMap[x][y].init(B_EMPTY);
			}
		}

		nodeMap[5][18].init(B_WALL);
		nodeMap[5][17].init(B_WALL);
		nodeMap[5][16].init(B_WALL);
		nodeMap[5][15].init(B_WALL);
		nodeMap[5][14].init(B_WALL);
		nodeMap[5][13].init(B_WALL);
		nodeMap[5][12].init(B_WALL);
					 
		nodeMap[4][18].init(B_WALL);
		nodeMap[4][17].init(B_WALL);
		nodeMap[4][16].init(B_WALL);
		nodeMap[4][15].init(B_WALL);
		nodeMap[4][14].init(B_WALL);
		nodeMap[4][13].init(B_WALL);
		nodeMap[4][12].init(B_WALL);

		nodeMap[12][18].init(B_WALL);
		nodeMap[12][17].init(B_WALL);
		nodeMap[12][16].init(B_WALL);
		nodeMap[12][15].init(B_WALL);
		nodeMap[12][14].init(B_WALL);
		nodeMap[12][13].init(B_WALL);
		nodeMap[12][12].init(B_WALL);
		nodeMap[12][11].init(B_WALL);
		nodeMap[12][10].init(B_WALL);
					  
		nodeMap[13][18].init(B_WALL);
		nodeMap[13][17].init(B_WALL);
		nodeMap[13][16].init(B_WALL);
		nodeMap[13][15].init(B_WALL);
		nodeMap[13][14].init(B_WALL);
		nodeMap[13][13].init(B_WALL);
		nodeMap[13][12].init(B_WALL);
		nodeMap[13][11].init(B_WALL);
		nodeMap[13][10].init(B_WALL);
					  
		nodeMap[14][10].init(B_WALL);
		nodeMap[14][11].init(B_WALL);
		nodeMap[15][10].init(B_WALL);
		nodeMap[15][11].init(B_WALL);
		nodeMap[16][10].init(B_WALL);
		nodeMap[16][11].init(B_WALL);
		break;


	default:
		break;
	}

}


// ------------------------------------------------------------------------------


void Board::setI(int x, int y, int i_)
{
	nodeMap[x][y].setI(i_);
	
	drawIndex(x, y, i_);				// draws output
}

// ------------------------------------------------------------------------------

void Board::setFGH(int x, int y, int g_, int h_)
{
	nodeMap[x][y].setFGH(g_, h_);

	drawIndex(x, y, g_);				// draws output
}

// ------------------------------------------------------------------------------


void Board::drawMap()
{
	ui->Clear_Screen();

	for(int y = 0; y < BOARD_Y; y++)
	{
		for(int x = 0; x < BOARD_X; x++)
		{
			switch(nodeMap[x][y].getI())
			{
				case B_EMPTY:
					//ui->Draw_String(((x*2)+xPosition), (y+yPosition), "   ");
					break;

				case B_WALL:
					ui->Draw_String( ( (x*3) + xPosition), ( (y*2) + yPosition), "#  ");
					break;

				case B_START:
					ui->Draw_String( ( (x*3) + xPosition), ( (y*2) + yPosition), "S  ");
					break;

				case B_END:
					ui->Draw_String(((x*3) + xPosition), ( (y*2) + yPosition), "T  ");
					break;

				default:
					break;
			}
		}
	}

}

// ------------------------------------------------------------------------------


void Board::clearBoard()
{
	for(int y = 0; y < BOARD_Y; y++)
	{
		for(int x = 0; x < BOARD_X; x++)
		{
			if(nodeMap[x][y].getI() != B_WALL && nodeMap[x][y].getI() != B_START && nodeMap[x][y].getI() != B_END)
				nodeMap[x][y].setI(B_EMPTY);
		}
	}


	drawMap();

}

// ------------------------------------------------------------------------------


Node Board::getNode(int x, int y)
{
	return nodeMap[x][y];
}

// ------------------------------------------------------------------------------


int Board::getI(int x, int y)
{
	return nodeMap[x][y].getI();
}

// ------------------------------------------------------------------------------


int Board::getF(int x, int y)
{
	return nodeMap[x][y].getF();
}

// ------------------------------------------------------------------------------


int Board::getH(int x, int y)
{
	return nodeMap[x][y].getH();
}

// ------------------------------------------------------------------------------


void Board::drawIndex(int x, int y, int i_)
{
	switch(i_)
	{
	case B_EMPTY:
		//ui->Draw_String(((x*2)+xPosition), (y+yPosition), "   ");
		break;

	case B_WALL:
		ui->Draw_String( ( (x*3) + xPosition), ( (y*2) + yPosition), "# ");
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