#include "astar.h"



void Astar::generatePath(Vector start, Vector end, Board* board_, int timer_)
{
	map = board_;
	delay = timer_;

	// generate distances to find route to the end
	generateDistances(start, end);

	// generate the final path stack
	traceBack(start, end);

	Sleep(10*delay);
	map->clearBoard();

	// display the final path
	displayPath();

	map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());
}

// ------------------------------------------------------------------------------

void Astar::generateDistances(Vector start, Vector end)
{
	Vector curr_point;

	// set start/end to the board
	map->setI(start.x, start.y, B_START);
	map->setI(end.x, end.y, B_END);
	map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());

	// update squares adjacent to the start position
	updateAdjSquares(start, end);

	// now start looping through the wset until adjacent to the end point, or until the wset is empty
	while(!wset.empty() && !isAdjIndex(wset.top(), B_END))
	{
		curr_point = wset.top();
		wset.pop();
		
		updateAdjSquares(curr_point, end);
		Sleep(delay);

		map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());

	}
}

// ------------------------------------------------------------------------------


void Astar::updateAdjSquares(Vector point, Vector goal)
{
	Node tempNode;

	// g = path length so far (the index)
	int g = 0;
	// h = estimated distance to travel to the goal
	int h = 0;
	int f = 0;

	/*! 1 update the distance number of the West adjacent node
	*		(1) Get the West adjacent node from board.board[][] 
	*		(2) Check whether the West adjacent node is empty by comparing its index (getI()) with the Macro "B_EMPTY"
	*		(3) calculate the tentative g, h, f costs of the West adjacent node, g is the distance of the current node plus one, h is the Manhattan distance from the West adjacent node to target node
	*		(4) if the tentative f cost is less than the old f cost of the West adjacent node, then update the g, h, f cost using the function "board.board[][].setFGH()"
	*
	*			!!! Error: if(f < tempNode.getF()), fixed by initializing f to same start value as i (using macros WALL, EMPTY)
	*		(5) push the updated West adjacent point "cVector" to the working set using the member function of "wset.push()".
	*/
	
	tempNode = map->getNode((point.x - 1), point.y);

	if(tempNode.getI() == B_EMPTY)
	{
		// g is the distance of the current node plus one
		g = map->getI(point.x, point.y) + 1;

		// h is the Manhattan distance from the West adjacent node to target node
		h = manhattanDistance(Vector((point.x - 1), point.y), goal);

		f = g + h;

		if(f < tempNode.getF())
		{
			map->setFGH((point.x - 1), point.y, g, h);
			wset.push(Vector((point.x - 1), point.y, f));
		}
	}


	// 2 update the distance number of the North adjacent node
	tempNode = map->getNode(point.x, (point.y - 1));

	if(tempNode.getI() == B_EMPTY)
	{
		// g is the distance of the current node plus one
		g= map->getI(point.x, point.y) + 1;

		// h is the Manhattan distance from the West adjacent node to target node
		h = manhattanDistance(Vector(point.x, (point.y - 1)), goal);

		f = g + h;

		if(f < tempNode.getF())
		{
			map->setFGH(point.x, (point.y - 1), g, h);
			wset.push(Vector(point.x, (point.y - 1), f));
		}
	}	

	// 3 update the distance number of the East adjacent node
	tempNode = map->getNode((point.x + 1), point.y);
	
	if(tempNode.getI() == B_EMPTY)
	{
		// g is the distance of the current node plus one
		g= map->getI(point.x, point.y) + 1;

		// h is the Manhattan distance from the West adjacent node to target node
		h = manhattanDistance(Vector((point.x + 1), point.y), goal);

		f = g + h;

		if(f < tempNode.getF())
		{
			map->setFGH((point.x + 1), point.y, g, h);
			wset.push(Vector((point.x + 1), point.y, f));
		}
	}
	

	// 4 update the distance number of the South adjacent node
	tempNode = map->getNode(point.x, (point.y + 1));

	if(tempNode.getI() == B_EMPTY)
	{
		// g is the distance of the current node plus one
		g= map->getI(point.x, point.y) + 1;

		// h is the Manhattan distance from the West adjacent node to target node
		h = manhattanDistance(Vector(point.x, (point.y + 1)), goal);

		f = g + h;

		if(f < tempNode.getF())
		{
			map->setFGH(point.x, (point.y + 1), g, h);
			wset.push(Vector(point.x, (point.y + 1), f));
		}
	}	


}// end of updateAdjSquares

// ------------------------------------------------------------------------------


bool Astar::isAdjIndex(Vector point, int i_)
{
	


	if(map->getI((point.x + 1), point.y) == i_)
		return true;
	else
	{
		if(map->getI((point.x - 1), point.y) == i_)
			return true;
		else
		{
			if(map->getI(point.x, (point.y + 1)) == i_)
				return true;
			else
			{
				if(map->getI(point.x, (point.y - 1)) == i_)
					return true;
				else
				{
					return false;
				}
			}
		}
	}
}

// ------------------------------------------------------------------------------


void Astar::traceBack(Vector start, Vector end)
{
	Vector currentPoint;
	int tempIndex;
	int currentIndex;

	// push the end point to the path stack using the function "path_final.push()", note that the data type in the path stack is "cVector"
	path_final.push(end);


	/*! find the node "board.board[][]" with lowest distance around the end node in clockwise orientation of West, North, East and South  
	*
	*	push the adjacent point with lowest distance to the path stack using the function of "path_final.push(cVector())"
	*
	*	work back from lowest to S to populate the stack with the final path from S to T
	*	1. using a do-while loop, starting from the lowest point "cVetor" around the target point, finishing at the start point
	*	2. in each loop, find the lowest node "board.board[][]" from the four adjacent node of the current node in clockwise orientation of West, North, East and South
	*	3. in each loop, push the lowest point "cVetor" to the path stack using the function of "path_final.push()"
	*/
	
	currentPoint = end;

	do
	{
		currentIndex = map->getI(currentPoint.x, currentPoint.y);


		// WEST -----------------------------------------------------------
		tempIndex = map->getI((currentPoint.x - 1), currentPoint.y);
		

		if((tempIndex < currentIndex) && (tempIndex < B_WALL))
		{
			currentPoint.x--;
			//currentPoint.i = tempSquare;
		}
		else
		{
			// NORTH ----------------------------------------------------------
			tempIndex = map->getI(currentPoint.x, (currentPoint.y - 1));
			
			if((tempIndex < currentIndex) && (tempIndex < B_WALL))
			{
				currentPoint.y--;
				//currentPoint.i = tempSquare;
			}
			else
			{
				// EAST -----------------------------------------------------------
				tempIndex = map->getI((currentPoint.x + 1), currentPoint.y);

				if((tempIndex < currentIndex) && (tempIndex < B_WALL))
				{
					currentPoint.x++;
					//currentPoint.i = tempSquare;
				}
				else
				{
					// SOUTH ----------------------------------------------------------
					tempIndex = map->getI(currentPoint.x, (currentPoint.y + 1));

					if((tempIndex < currentIndex) && (tempIndex < B_WALL))
					{
						currentPoint.y++;
						//currentPoint.i = tempSquare;
					}

				}

			}

		}

		// push the adjacent point with lowest distance to the path stack using the function of "path_final.push()"
		path_final.push(currentPoint);

		map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());

	}while(currentIndex > B_START);
	
}

// ------------------------------------------------------------------------------


void Astar::displayPath()
{
	while(!path_final.empty())
	{
		map->setI(path_final.top().x, path_final.top().y, path_final.size());
		path_final.pop();

		map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());

		Sleep(delay);
	}

}

// ------------------------------------------------------------------------------


int Astar::manhattanDistance(Vector point, Vector goal)
{
	int distance = (abs(point.x-goal.x) + abs(point.y-goal.y));
	return distance;
}
