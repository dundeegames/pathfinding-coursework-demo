/*
#include <windows.h>	// Sleep()
#include <stdlib.h>		// abs()
#include <iostream>

#include "astar.h"


void Astar::generatePath(Vector start, Vector end)
{
	// generate distances to find route to the end
	generateDistances(start, end);

	// generate the final path stack
	traceBack(start, end);

	Sleep(1000);
	board.clearBoard();
	board.draw();

	// display the final path
	displayPath();	
}

// ------------------------------------------------------------------------------

void Astar::generateDistances(Vector start, Vector end)
{
	Vector curr_point;

	// set start/end to the board
	board.board[start.x][start.y].setI(B_START);
	board.board[end.x][end.y].setI(B_END);

	// update squares adjacent to the start position
	updateAdjSquares(start, end);

	// now start looping through the wset until adjacent to the end point, or until the wset is empty
	while(!wset.empty() && !isAdjIndex(wset.top(), B_END))
	{
		curr_point = wset.top();
		wset.pop();
		
		updateAdjSquares(curr_point, end);
		board.draw();
		Sleep(200);
	}
}

// ------------------------------------------------------------------------------


void Astar::updateAdjSquares(Vector point, Vector goal)
{
	// g = path length so far (the index)
	int g = 0;
	// h = estimated distance to travel to the goal
	int h = 0;
	int f = 0;

	// 1 update the distance number of the West adjacent node
		// (1) Get the West adjacent node from board.board[][] 
		// (2) Check whether the West adjacent node is empty by comparing its index (getI()) with the Macro "B_EMPTY"
		// (3) calculate the tentative g, h, f costs of the West adjacent node, g is the distance of the current node plus one, h is the Manhattan distance from the West adjacent node to target node
		// (4) if the tentative f cost is less than the old f cost of the West adjacent node, then update the g, h, f cost using the function "board.board[][].setFGH()"

				// !!! Error: ^ fixed by if(f < tempNode.getI()) intead of // if(f < tempNode.getF())
		// (5) push the updated West adjacent point "cVector" to the working set using the member function of "wset.push()".
	
	
	Node tempNode = board.board[(point.x - 1)][point.y];
	
	if(tempNode.getI() == B_EMPTY)
	{
		// g is the distance of the current node plus one
		g = board.board[point.x][point.y].getI() + 1;

		// h is the Manhattan distance from the West adjacent node to target node
		h = manhattanDistance(Vector((point.x - 1), point.y), goal);

		f = g + h;

		// if(f < tempNode.getF())

		if(f < tempNode.getI())
		{
			board.board[(point.x - 1)][point.y].setFGH(g, h);
			wset.push(Vector((point.x - 1), point.y, f));
		}
	}


	// 2 update the distance number of the North adjacent node
	tempNode = board.board[point.x][(point.y - 1)];
	
	if(tempNode.getI() == B_EMPTY)
	{
		// g is the distance of the current node plus one
		g = board.board[point.x][point.y].getI() + 1;

		// h is the Manhattan distance from the West adjacent node to target node
		h = manhattanDistance(Vector(point.x, (point.y - 1)), goal);

		f = g + h;

		if(f < tempNode.getI())
		{
			board.board[point.x][(point.y - 1)].setFGH(g, h);
			wset.push(Vector(point.x, (point.y - 1), f));
		}
	}


	// 3 update the distance number of the East adjacent node
	tempNode = board.board[(point.x + 1)][point.y];
	
	if(tempNode.getI() == B_EMPTY)
	{
		// g is the distance of the current node plus one
		g = board.board[point.x][point.y].getI() + 1;

		// h is the Manhattan distance from the West adjacent node to target node
		h = manhattanDistance(Vector((point.x + 1), point.y), goal);

		f = g + h;

		if(f < tempNode.getI())
		{
			board.board[(point.x + 1)][point.y].setFGH(g, h);
			wset.push(Vector((point.x + 1), point.y, f));
		}
	}


	// 4 update the distance number of the South adjacent node
	tempNode = board.board[point.x][(point.y + 1)];
	
	if(tempNode.getI() == B_EMPTY)
	{
		// g is the distance of the current node plus one
		g = board.board[point.x][point.y].getI() + 1;

		// h is the Manhattan distance from the West adjacent node to target node
		h = manhattanDistance(Vector(point.x, (point.y + 1)), goal);

		f = g + h;

		if(f < tempNode.getI())
		{
			board.board[point.x][(point.y + 1)].setFGH(g, h);
			wset.push(Vector(point.x, (point.y + 1), f));
		}
	}


}// end of updateAdjSquares

// ------------------------------------------------------------------------------


bool Astar::isAdjIndex(Vector point, int i)
{
	if(board.board[point.x + 1][point.y].getI() == i)
		return true;
	else
	{
		if(board.board[point.x - 1][point.y].getI() == i)
			return true;
		else
		{
			if(board.board[point.x][point.y + 1].getI() == i)
				return true;
			else
			{
				if(board.board[point.x][point.y - 1].getI() == i)
					return true;
				else
					return false;
			}
		}
	}
}

// ------------------------------------------------------------------------------


void Astar::traceBack(Vector start, Vector end)
{
	Vector currentPoint;
	Node tempNode;
	Node currentNode;

	// push the end point to the path stack using the function "path_final.push()", note that the data type in the path stack is "cVector"
	path_final.push(end);


	// find the node "board.board[][]" with lowest distance around the end node in clockwise orientation of West, North, East and South  


	
	// push the adjacent point with lowest distance to the path stack using the function of "path_final.push(cVector())"



	// work back from lowest to S to populate the stack with the final path from S to T
	// 1. using a do-while loop, starting from the lowest point "cVetor" around the target point, finishing at the start point
	// 2. in each loop, find the lowest node "board.board[][]" from the four adjacent node of the current node in clockwise orientation of West, North, East and South
	// 3. in each loop, push the lowest point "cVetor" to the path stack using the function of "path_final.push()"


	currentPoint = end;

	do
	{
		currentNode = board.board[currentPoint.x][currentPoint.y];


		// WEST -----------------------------------------------------------
		tempNode = board.board[(currentPoint.x - 1)][currentPoint.y];
		

		if((tempNode.getI() < currentNode.getI()) && (tempNode.getI() < B_WALL))
		{
			currentPoint.x--;
			//currentPoint.i = tempSquare;
		}
		else
		{
			// NORTH ----------------------------------------------------------
			tempNode = board.board[currentPoint.x][(currentPoint.y - 1)];
			
			if((tempNode.getI() < currentNode.getI()) && (tempNode.getI() < B_WALL))
			{
				currentPoint.y--;
				//currentPoint.i = tempSquare;
			}
			else
			{
				// EAST -----------------------------------------------------------
				tempNode = board.board[(currentPoint.x + 1)][currentPoint.y];

				if((tempNode.getI() < currentNode.getI()) && (tempNode.getI() < B_WALL))
				{
					currentPoint.x++;
					//currentPoint.i = tempSquare;
				}
				else
				{
					// SOUTH ----------------------------------------------------------
					tempNode = board.board[currentPoint.x][(currentPoint.y + 1)];

					if((tempNode.getI() < currentNode.getI()) && (tempNode.getI() < B_WALL))
					{
						currentPoint.y++;
						//currentPoint.i = tempSquare;
					}

				}

			}

		}

		// push the adjacent point with lowest distance to the path stack using the function of "path_final.push()"
		path_final.push(currentPoint);

	}while(currentNode.getI() > B_START);
	
}

// ------------------------------------------------------------------------------


void Astar::displayPath()
{
	while(!path_final.empty())
	{
		board.board[path_final.top().x][path_final.top().y].setI(path_final.size());
		path_final.pop();

		board.draw();
		Sleep(200);
	}

}

// ------------------------------------------------------------------------------


int Astar::manhattanDistance(Vector point, Vector goal)
{
	int distance = (abs(point.x-goal.x) + abs(point.y-goal.y));
	return distance;
}
*/