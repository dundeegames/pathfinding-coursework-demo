#include "gpsa.h"


Gpsa::Gpsa(Gui* ui_)
{
	ui = ui_;
	head = 0;
	rear = 0;
	dlist1 = 0;

	for(int i = 0; i < COUNTER; i++)	// init funcCounter[]
	{
		funcCounter[i] = 0;
	}

	for(int i = 0; i < 5; i++)			// init resultCounter[]
	{
		resultCounter[i] = 0;
	}

}


Gpsa::~Gpsa()
{

}



// SYSTEM FUNCTIONS ////////////////////////////////////////////////////////////

void Gpsa::run()
{
	profiler.Start();	// start timing


	ui->Clear_Screen();

	drawTables(TABLE_X, TABLE_Y);

	Position temp;		// used to initialise data structures

	//  Set up initial Position 
	for(int i=0; i < BD_SIZE; i++)
	{
		for(int j=0; j < BD_SIZE; j++)
		{
			temp.bd[i][j] = 0;
		}
	}

	for(int i=0; i < HASH_MAX; i++)
	{
		hashtable[i]= false;
	}

	temp.game = UNDECIDED;
	temp.npieces = 0;

	//and initialise wset and dlist
	add_to_wset(temp);
	add_to_dlist(temp);

	while(wset_not_empty())
	{
		single_step();
	}

	profiler.End();		// end timing

	print_status();

	//Sleep(2000);
	//check_wset();


}


// -----------------------------------------------------------------------------

void Gpsa::check_wset()
{
	funcCounter[0]++;								// count function calls

	pointer head, tail;								// constant Piece*s to dummy Pieces
	
	head = new Piece();								// dummy head Piece
	tail = new Piece();								// dummy tail Piece	
	head->left = NULL;
	head->right = tail;
	tail->left = head;
	tail->right = NULL;								//  empty list

	head->Piece_number = 0;							// min value		
	tail->Piece_number = (1<<30) - 1 + (1<<30);		// max value		



	int i=0;										// loop counter

	while (i < 765)
	{
		insert( i+1, min_boardval(wset[i]), head);

		if (i%20 == 19) 
		{
			Sleep (500);
		}

		i++;

	}

}


// -----------------------------------------------------------------------------

void Gpsa::insert(int v, int num, Piece* h)
{
	funcCounter[1]++;			// count function calls

	static int ncount = 0;		// Piece counter

	//	insert immediately to the left of Piece_number num
	pointer   temp, runner = h->right;
	temp = (pointer) malloc ( sizeof ( Piece ) );	// works same as new Piece();


	// Could guard against memory failure here, trap temp == NULL
	temp->dat = v;				// initialise new Piece
	temp->Piece_number = num;	// key on board value


	//  Now search to find new right hand neighbour Piece
	while (runner->Piece_number < num)
	{
		runner = runner->right;
	}


	// Now insert Piece "temp" to the left of Piece "runner"
	if(runner->Piece_number==num)
	{
		ui->Draw_String(5,5, "insert clash  ");
		ui->Draw_Integer(19,5, 1, num);
		//cout<<"insert   clash  "<< num<<endl;
	}

	temp->right = runner;
	temp->left = runner->left;
	temp->left->right = temp;
	temp->right->left = temp;

	ui->Draw_String(5,6, "insert ");
	ui->Draw_Integer(12,6, 1, ++ncount);
	ui->Draw_Integer(19,6, 1, num);
	//cout << "insert   " << ++ncount << "\t" << num << endl;

}


// -----------------------------------------------------------------------------

int Gpsa::boardval(int b[BD_SIZE][BD_SIZE])
{
	funcCounter[2]++;								// count function calls

	int total = 0;					// accumulate ternary number

	for(int i=0; i < BD_SIZE; i++)
	{
		for(int j=0; j < BD_SIZE; j++)
		{
			total = 3*total + b[i][j];
		}
	}

	return total;

}


// -----------------------------------------------------------------------------

int Gpsa::min_boardval(Position p)
{
	funcCounter[3]++;								// count function calls

	int min = HASH_MAX;				// minimum so far, initialised high
	int temp;						// temporary store

	// First the four rotations
	for(int k=0; k < 4; k++)
	{
		rotation(p.bd);
		
		temp = boardval(p.bd);

		if (temp < min)
		{
			min = temp;
		}
	}

	// Now the mirror images
	reflection(p.bd);

	for(int k=0; k < 4; k++)
	{
		rotation(p.bd);
		temp = boardval(p.bd);

		if (temp < min)
		{
			min = temp;
		}

	}

	return min;

}


// -----------------------------------------------------------------------------

void Gpsa::single_step()
{
	funcCounter[4]++;								// count function calls

	Position temp, possible;  

	//	take Position from wset
	temp = get_from_wset();

	if(temp.game != UNDECIDED)		//  Game over already
	{
		return;						//  skip the rest
	}

	/**	generate nine new Positions.  
	*	Could do this in one step (setting some to ILLEGAL).
	*	I plan to process them in full one after the other.
	*/
	temp.npieces++;
	int xo = ((temp.npieces%2)==1)? 1 : 2;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			possible = temp;
			
			//	skip ILLEGALs
			if(possible.bd[i][j] == 0)				// move legal
			{
				possible.bd[i][j] = xo;

				//	check for duplicates
				if (search_dlist(possible) == 0)		// not found
				{
					//	add survivors to wset
					// first set g field
					possible.game = is_win_or_draw(possible, xo);	
					add_to_wset(possible);

					//	add all 8 equivalents to dlist. Yes. "if not already present" - No


					/**	This is really crude, some Positions will be added multiple times
					*	Could either create "add_if_new()" rather than use add_to_dlist()	
					*	or could modify is_duplicate() to spot symmetry copies.	
					*	For now I'll just leave this - it is simple at least!
					*/

					// First the four rotations
					for(int k=0; k < 4; k++)
					{
						rotation(possible.bd);
						add_to_dlist(possible);
					}

					// Now the mirror images
					reflection(possible.bd);

					for(int k=0; k < 4; k++)
					{
						rotation(possible.bd);
						add_to_dlist(possible);
					}

				} // if ... not duplicate

			} // if ...  move legal

		} // for j ...

	} // for i ..

}


// -----------------------------------------------------------------------------

int Gpsa::search_dlist(Position p)
{
	funcCounter[5]++;								// count function calls

	/*int i=0;

	int is_duplicate(int p[3][3], int q[3][3]);

	dlist[dlist1] = p;	// terminator.  In the array but not the list
	while(!is_duplicate(dlist[i].bd, p.bd))
		i++;

	if(i<dlist1)	// found it!
		return 1;
	else			// i = dlist1, terminator
		return 0;
	*/	

	
	int hashvalue = min_boardval(p);

	if(hashtable[hashvalue] == true)
	{
		return 1;
	}

	return 0;

}


// -----------------------------------------------------------------------------

GameStatus Gpsa::is_win_or_draw(Position p, int xo)
{
	funcCounter[6]++;								// count function calls

	/**	Checking after a move can only lead to 
	*	a win, return win if xo == 1, LOSS if xo == 2
	*	a DRAW (if the board is now full, or (still) UNDECIDED).
	*	There are 8 columns / rows / diagonals patterns leading to
	*	a decisive result:
	*/
	if( (xo==p.bd[0][0]) && (xo==p.bd[0][1]) && (xo==p.bd[0][2]) ||
		(xo==p.bd[1][0]) && (xo==p.bd[1][1]) && (xo==p.bd[1][2]) ||
		(xo==p.bd[2][0]) && (xo==p.bd[2][1]) && (xo==p.bd[2][2]) ||
		(xo==p.bd[0][0]) && (xo==p.bd[1][0]) && (xo==p.bd[2][0]) ||
		(xo==p.bd[0][1]) && (xo==p.bd[1][1]) && (xo==p.bd[2][1]) ||
		(xo==p.bd[0][2]) && (xo==p.bd[1][2]) && (xo==p.bd[2][2]) ||
		(xo==p.bd[0][0]) && (xo==p.bd[1][1]) && (xo==p.bd[2][2]) ||
		(xo==p.bd[0][2]) && (xo==p.bd[1][1]) && (xo==p.bd[2][0]) ) 
	{
		if (xo==1)
		{
				return WIN;
		}
		else
		{
			return LOSS;
		}
	}
	else if (p.npieces == 9)
	{
		return DRAW;
	}
	else
	{
		return UNDECIDED;
	}

}


// -----------------------------------------------------------------------------

int Gpsa::is_duplicate(int p[3][3], int q[3][3])
{
	funcCounter[7]++;								// count function calls

	int same = 1;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(p[i][j] != q[i][j]) same = 0;
		}
	}
	return same;

}


// -----------------------------------------------------------------------------

void Gpsa::swap(int &a, int &b)
{
	funcCounter[8]++;								// count function calls

    int  temp = b;
    b = a;
    a = temp;

}


// -----------------------------------------------------------------------------

void Gpsa::rotation(int b[3][3])
{
	funcCounter[9]++;								// count function calls
	//!< Rotate 90 degrees clockwise

	int temp = b[0][0];

	b[0][0] = b[2][0];
	b[2][0] = b[2][2];
	b[2][2] = b[0][2];
	b[0][2] = temp;
	temp = b[1][0];
	b[1][0] = b[2][1];
	b[2][1] = b[1][2];
	b[1][2] = b[0][1]; 
	b[0][1] = temp;

}


// -----------------------------------------------------------------------------

void Gpsa::reflection(int b[3][3])
{
	funcCounter[10]++;								// count function calls

	//!< Reflect through vertical, middle column

	for(int i=0; i<3; i++)
	{
		swap(b[0][i], b[2][i]);
	}

}


// -----------------------------------------------------------------------------

void Gpsa::print_status()
{
	funcCounter[11]++;								// count function calls

	ui->Draw_String(14,3, "Working set size = ");
	ui->Draw_Integer(33,3, 1, rear);

	ui->Draw_String(41,3, "Duplicates list size = ");
	ui->Draw_Integer(64,3, 1, dlist1);

	for(int j = 0; j < 3; j++)
	{
		for(int i = 0; i < 6; i++)
		{
			int c = ((j*6)+i);
			ui->Draw_String((11 + (j* (DIST_X + 3))),(7 + i), "func  : ");
			ui->Draw_Integer((15 + (j* (DIST_X + 3))),(7 + i), 2, (c+1));
			ui->Draw_Integer((20 + (j* (DIST_X + 3))), (7 + i), 1, funcCounter[c]);
		}
	}

	ui->Draw_String(18,15, "WIN:");
	ui->Draw_Integer(24,15, 1, resultCounter[0]);

	ui->Draw_String(18,16, "LOSS:");
	ui->Draw_Integer(24,16, 1, resultCounter[1]);

	ui->Draw_String(34,15, "DRAW:");
	ui->Draw_Integer(40,15, 1, resultCounter[2]);

	ui->Draw_String(49,15, "UNDECIDED:");
	ui->Draw_Integer(60,15, 1, resultCounter[3]);

	ui->Draw_String(49,16, "ILLEGAL:");
	ui->Draw_Integer(60,16, 1, resultCounter[4]);


	ui->Draw_String(30,18, "Time:          ms");
	ui->Draw_Float(36,18, 1, (float)profiler.GetTimeInMilliseconds());

}


// -----------------------------------------------------------------------------

void Gpsa::add_to_wset(Position p)
{
	funcCounter[12]++;								// count function calls

	printp(p);
	wset[rear++] = p;
}


// -----------------------------------------------------------------------------

int Gpsa::wset_not_empty()
{
	funcCounter[13]++;								// count function calls

	return head < rear;
}


// -----------------------------------------------------------------------------

Position Gpsa::get_from_wset()
{
	funcCounter[14]++;								// count function calls

	return wset[head++];
}


// -----------------------------------------------------------------------------

void Gpsa::add_to_dlist(Position p)
{
	funcCounter[15]++;								// count function calls

	//!< dlist[dlist1++] = p;
	int hashvalue = min_boardval(p);
	hashtable[hashvalue] = true;
}


// -----------------------------------------------------------------------------

void Gpsa::printp(Position p)
{
	funcCounter[16]++;										// count function calls

	xoffset = (funcCounter[16] % 3) *  DIST_X;				// choosing which table to draw

	if((funcCounter[16] % 6) > 2)
	{
		yoffset = DIST_Y;
	}
	else
	{
		yoffset = 0;
	}


    for (int i = 2; i >= 0; i--)
	{
        for (int j = 0; j < 3; j++)
		{
            //cout <<  p.bd[j][i];
			int x = (i*4) + (TABLE_X + 2) + xoffset;
			int y = (j*2) + (TABLE_Y + 1) + yoffset;


			switch(p.bd[j][i])
			{
			case 1:
				ui->Set_Color(10, 0);
				ui->Draw_Character(x, y, 'X');
				break;

			case 2:
				ui->Set_Color(12, 0);
				ui->Draw_Character(x, y, 'O');
				break;

			default:
				ui->Draw_Character(x, y, ' ');
				break;
			}
			
		}
        
    }

	ui->Set_Color(15, 0);			// reset colour to white

	printg(p.game);

}


// -----------------------------------------------------------------------------

void Gpsa::printg(GameStatus gg)
{
	// count function calls (should be same as funcCounter[16])
	funcCounter[17]++;

	int x = (TABLE_X + 2) + xoffset;
	int y = (TABLE_Y + 8) + yoffset;


	ui->Draw_String(x, y,"         ");				// clear the previous statement
	switch (gg)
	{
	case WIN:
		resultCounter[0]++;
		ui->Set_Color(10, 0);
		ui->Draw_String(x, y,"WIN");
		break;

	case LOSS:
		resultCounter[1]++;
		ui->Set_Color(12, 0);
		ui->Draw_String(x, y,"LOSS");
		break;

	case DRAW:
		resultCounter[2]++;
		ui->Draw_String(x, y,"DRAW");
		break;

	case UNDECIDED:
		resultCounter[3]++;
		ui->Draw_String(x, y,"UNDECIDED");
		break;

	case ILLEGAL:
		resultCounter[4]++;
		ui->Draw_String(x, y,"ILLEGAL");
		break;

	}

	ui->Set_Color(15, 0);			// reset colour to white

}


// GUI FUNCTIONS ///////////////////////////////////////////////////////////////

void Gpsa::drawTables(int x, int y)
{
	for(int j=0; j < 2; j++)
	{
		for(int i = 0; i < 3; i++)
		{
			ui->Draw_Grid( (x + (i*DIST_X)), (y + (j*DIST_Y)) );
		}

	}

}


// -----------------------------------------------------------------------------





// -----------------------------------------------------------------------------




// -----------------------------------------------------------------------------




// -----------------------------------------------------------------------------




// 80 //////////////////////////////////////////////////////////////////////////