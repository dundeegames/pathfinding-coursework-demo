#include "lee.h"


Lee::Lee()
{

}

// ------------------------------------------------------------------------------


void Lee::generatePath(point start_, point end_,  Board* board_)
{
	start = start_;
	end = end_;
	map = board_;

	map->setI(start.x, start.y, start.i);
	map->setI(end.x, end.y, end.i);

	//map->draw();
	Sleep(1000);

	// generate distances
	generateDistances();

	// work back from T, populate pathing stack to generate path S -> T
	traceBack();
}

// ------------------------------------------------------------------------------


void Lee::generateDistances()
{
	// add start to the working set
	wset.push_front(point(start.x, start.y, start.i));

	int temp = 0; // for the simulation board draw to look nicer

	// loop until current node is adjacent to the end
	while(!wset.empty() && !checkAdjIndex(wset.front(), B_END))
	{

		updateAdjSquares(wset.front());

		if(wset.front().i > temp)
		{
			Sleep(100);
			//map->draw();
			temp++;
		}

		wset.pop_front();
	}

}

// ------------------------------------------------------------------------------


bool Lee::checkAdjIndex(point tester, int i_)
{
	
	if(map->getNode((tester.x + 1), tester.y).i == i_)
		return true;
	else
	{
		if(map->getNode((tester.x - 1), tester.y).i == i_)
			return true;
		else
		{
			if(map->getNode(tester.x, (tester.y + 1)).i == i_)
				return true;
			else
			{
				if(map->getNode(tester.x, (tester.y + 1)).i == i_)
					return true;
				else
					return false;
			}
		}
	}
}

// ------------------------------------------------------------------------------


void Lee::updateAdjSquares(point current)
{
	int tempIndex = 0;

	// update the distance number of the West adjacent square
	// 1. get the x, y coordiantes of the West adjacnet square using the member funtion of
	// 2. and cheke whether it is empty by comparing the distance with the Macro "B_EMPTY"
	// 3. if it is empty, update the distance number using the current distance plus 1 using the member function of "board.setSquare()"
	// 4. push the updated West adjacnet square to the working set using the member function of "wset.push_back()".
	tempIndex = map->getNode((current.x-1), current.y).i;

	if(tempIndex == B_EMPTY)
	{
		map->setI((current.x-1), current.y, (current.i + 1));
		wset.push_back(point((current.x-1), current.y, (current.i + 1)));
	}


	// update the distance number of the North adjacent square
	tempIndex = map->getNode(current.x, (current.y-1)).i;

	if(tempIndex == B_EMPTY)
	{
		map->setI(current.x, (current.y-1), (current.i + 1));
		wset.push_back(point(current.x, (current.y-1), (current.i + 1)));
	}


	// update the distance number of the East adjacent square
	tempIndex = map->getNode((current.x+1), current.y).i;

	if(tempIndex == B_EMPTY)
	{
		map->setI((current.x+1), current.y, (current.i + 1));
		wset.push_back(point((current.x+1), current.y, (current.i + 1)));
	}

			
	// update the distance number of the South adjacent square
	tempIndex = map->getNode(current.x, (current.y+1)).i;

	if(tempIndex == B_EMPTY)
	{
		map->setI(current.x, (current.y+1), (current.i + 1));
		wset.push_back(point(current.x, (current.y+1), (current.i + 1)));
	}

}

// ------------------------------------------------------------------------------


void Lee::traceBack()
{
	int tempIndex = 0;

	point currentPoint = end;


	// push the end point to the path stack using the function "path_final.push()"
	path_final.push(currentPoint);


	// find the lowest distance around the end point in the order of West, North, East and South, using the function of "board.getSquare()"
	// work back from lowest to S to populate the stack with the final path from S to T
	// 1. using a do-while loop, starting from the lowest point of the end point, ending at the start point
	// 2. in each loop, find the first point (with distance i-1, i is the distance of the current point) from the four adjacent points of the current point in the order of West, North, East and South, using fucntion of "board.getSquare()". 
	// 3. in each loop, push the frist i-1 point to the path stack using the function of "path_final.push()"


	do
	{
		// WEST -----------------------------------------------------------
		tempIndex = map->getNode((currentPoint.x-1), currentPoint.y).i;

		if((tempIndex < currentPoint.i) && (tempIndex < B_WALL))
		{
			currentPoint.x--;
			currentPoint.i = tempIndex;
		}
		else
		{
			// NORTH ----------------------------------------------------------
			tempIndex = map->getNode(currentPoint.x, (currentPoint.y - 1)).i;

			if((tempIndex < currentPoint.i) && (tempIndex < B_WALL))
			{
				currentPoint.y--;
				currentPoint.i = tempIndex;
			}
			else
			{
				// EAST -----------------------------------------------------------
				tempIndex = map->getNode((currentPoint.x + 1), currentPoint.y).i;

				if((tempIndex < currentPoint.i) && (tempIndex < B_WALL))
				{
					currentPoint.x++;
					currentPoint.i = tempIndex;
				}
				else
				{
					// SOUTH ----------------------------------------------------------
					tempIndex = map->getNode(currentPoint.x, (currentPoint.y + 1)).i;

					if((tempIndex < currentPoint.i) && (tempIndex < B_WALL))
					{
						currentPoint.y++;
						currentPoint.i = tempIndex;
					}

				}

			}

		}

		// push the adjacent point with lowest distance to the path stack using the function of "path_final.push()"
		path_final.push(currentPoint);

	}while(currentPoint.i != 0);

}

// ------------------------------------------------------------------------------


void Lee::drawPath()
{
	while(!path_final.empty())
	{
		map->setI(path_final.top().x, path_final.top().y, path_final.top().i);
		path_final.pop();
		//map->draw();
		Sleep(100);
	}
}

