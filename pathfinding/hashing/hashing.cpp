#include "hashing.h"


Hashing::Hashing()
{
	head = 0;
	rear = 0;
	dlist1 = 0;
}


Hashing::~Hashing()
{

}


// -----------------------------------------------------------------------------

void Hashing::run()
{
	position temp;		// used to initialise data structures

	//  Set up initial position 
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){
			temp.bd[i][j] = 0;
		}
	}

	for(int i=0; i < 20000; i++)
	{
		hashtable[i]= false;
	}

	temp.game = undecided;
	temp.npieces = 0;

	//and initialise wset and dlist
	add_to_wset(temp);
	add_to_dlist(temp);

	while(wset_not_empty()) {
		single_step();
	}
	print_status();
	Sleep(2000);
	// check_wset();


}


// -----------------------------------------------------------------------------

void Hashing::check_wset()
{
	pointer head, tail;								// constant pointers to dummy Nodes

	head = (pointer) malloc(sizeof(Node));			// dummy head Node
	tail = (pointer) malloc(sizeof(Node));			// dummy tail Node	
	head->left = NULL;
	head->right = tail;
	tail->left = head;
	tail->right = NULL;								//  empty list

	head->Node_number = 0;							// min value		
	tail->Node_number = (1<<30) - 1 + (1<<30);		// max value		



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

void Hashing::insert(int v, int num, Node* h)
{
	static int ncount = 0;		// Node counter

	//	insert immediately to the left of Node_number num
	pointer   temp, runner = h->right;
	temp = (pointer) malloc ( sizeof ( Node ) );


	// Could guard against memory failure here, trap temp == NULL
	temp->dat = v;				// initialise new Node
	temp->Node_number = num;		// key on board value


	//  Now search to find new right hand neighbour Node
	while (runner->Node_number < num)
	{
		runner = runner->right;
	}


	// Now insert Node "temp" to the left of Node "runner"
	if(runner->Node_number==num)
	{
		cout<<"insert   clash  "<< num<<endl;
	}

	temp->right = runner;
	temp->left = runner->left;
	temp->left->right = temp;
	temp->right->left = temp;

	cout << "insert   " << ++ncount << "\t" << num << endl;

}


// -----------------------------------------------------------------------------

int Hashing::boardval(int b[3][3])
{
	int total = 0;					// accumulate ternary number

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			total = 3*total + b[i][j];
		}
	}

	return total;

}


// -----------------------------------------------------------------------------

int Hashing::min_boardval(position p)
{
	int min = 20000;					// minimum so far, initialised high
	int temp;						// temporary store

	//int boardval(int b[3][3]);
	//void rotation(int b[3][3]);
	//void reflection(int b[3][3]);

	// First the four rotations
	for(int k=0; k<4; k++)
	{
		rotation(p.bd);
		
		temp = boardval(p.bd);

		if (temp<min)
		{
			min = temp;
		}
	}

	// Now the mirror images
	reflection(p.bd);

	for(int k=0; k<4; k++)
	{
		rotation(p.bd);
		temp = boardval(p.bd);

		if (temp<min)
		{
			min = temp;
		}

	}

	return min;

}


// -----------------------------------------------------------------------------

void Hashing::single_step()
{
	position temp, possible;  

	//	take position from wset
	temp = get_from_wset();

	if(temp.game != undecided)		//  Game over already
	{
		return;					//  skip the rest
	}

	//	generate nine new positions.  
	//	Could do this in one step (setting some to illegal).
	//	I plan to process them in full one after the other.

	temp.npieces++;
	int xo = ((temp.npieces%2)==1)? 1 : 2;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			possible = temp;
			
			//	skip illegals
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


					/*	This is really crude, some positions will be added multiple times
					Could either create "add_if_new()" rather than use add_to_dlist()	
					or could modify is_duplicate() to spot symmetry copies.	
					For now I'll just leave this - it is simple at least!			*/

					// First the four rotations
					for(int k=0; k < 4; k++)
					{
						rotation(possible.bd);
						add_to_dlist(possible);
					}

					// Now the mirror images
					reflection(possible.bd);

					for(int k=0; k<4; k++)
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

int Hashing::search_dlist(position p)
{
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

GameStatus Hashing::is_win_or_draw(position p, int xo)
{
	//	Checking after a move can only lead to 
	//		a win, return win if xo == 1, loss if xo == 2
	//		a draw (if the board is now full, or
	//		(still) undecided).

	//	There are 8 columns / rows / diagonals patterns leading to
	//	a decisive result:

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
			return loss;
		}
	}
	else if (p.npieces == 9)
	{
		return draw;
	}
	else
	{
		return undecided;
	}

}


// -----------------------------------------------------------------------------

int Hashing::is_duplicate(int p[3][3], int q[3][3])
{
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

void Hashing::swap(int &a, int &b)
{
    int  temp = b;
    b = a;
    a = temp;

}


// -----------------------------------------------------------------------------

void Hashing::rotation(int b[3][3])
{
	//	Rotate 90 degrees clockwise

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

void Hashing::reflection(int b[3][3])
{
	//	Reflect through vertical, middle column

	for(int i=0; i<3; i++)
	{
		swap(b[0][i], b[2][i]);
	}

}


// -----------------------------------------------------------------------------

void Hashing::print_status()
{
	cout << endl << "Working set size     = " << rear;
	cout << "\tDuplicates list size = " << dlist1 << endl << endl;
}


// -----------------------------------------------------------------------------

void Hashing::add_to_wset(position p)
{
	printp(p);
	wset[rear++] = p;
}


// -----------------------------------------------------------------------------

int Hashing::wset_not_empty()
{
	return head < rear;
}


// -----------------------------------------------------------------------------

position Hashing::get_from_wset()
{
	return wset[head++];
}


// -----------------------------------------------------------------------------

void Hashing::add_to_dlist(position p)
{
	//dlist[dlist1++] = p;
	int hashvalue = min_boardval(p);
	hashtable[hashvalue] = true;
}


// -----------------------------------------------------------------------------

void Hashing::printp(position p)
{
    for (int i = 2; i >= 0; i--)
	{
        for (int j = 0; j < 3; j++)
		{
            cout <<  p.bd[j][i];
		}
        cout << endl;
    }

	printg(p.game);
	cout << endl;

}


// -----------------------------------------------------------------------------

void Hashing::printg(GameStatus gg)
{
	switch (gg)
	{
	case WIN:       cout<<"WIN"      <<endl; break;
	case loss:      cout<<"loss"     <<endl; break;
	case draw:      cout<<"draw"     <<endl; break;
	case undecided: cout<<"undecided"<<endl; break;
	case illegal:   cout<<"illegal"  <<endl; break;
	}

	cout << endl;

}




// 80 //////////////////////////////////////////////////////////////////////////