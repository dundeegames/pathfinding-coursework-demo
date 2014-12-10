#include "lee.h"

#include <iostream>

Lee::Lee()
{

}

// ------------------------------------------------------------------------------


void Lee::generatePath(point start_, point end_,  Board* board_, int timer_)
{
	start = start_;
	end = end_;
	map = board_;
	delay = timer_;

	map->setI(start.x, start.y, start.i);
	map->setI(end.x, end.y, end.i);

	Sleep(10*delay);

	// generate distances
	generateDistances();

	// work back from T, populate pathing stack to generate path S -> T
	traceBack();

	map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());
}

// ------------------------------------------------------------------------------


void Lee::generateDistances()
{
	map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());
	
	// add start to the working set
	wset.push_front(point(start.x, start.y, start.i));


	int temp = 0; // for the simulation board draw to look nicer

	// loop until current node is adjacent to the end
	while(!wset.empty() && !checkAdjIndex(wset.front(), B_END))
	{
		
		updateAdjSquares(wset.front());

		if(wset.front().i > temp)
		{
			Sleep(delay);
			//map->draw();
			temp++;
		}

		wset.pop_front();

		map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());

	}

}

// ------------------------------------------------------------------------------


bool Lee::checkAdjIndex(point tester, int i_)
{
	
	if(map->getI((tester.x + 1), tester.y) == i_)
		return true;
	else
	{
		if(map->getI((tester.x - 1), tester.y) == i_)
			return true;
		else
		{
			if(map->getI(tester.x, (tester.y + 1)) == i_)
				return true;
			else
			{
				if(map->getI(tester.x, (tester.y + 1)) == i_)
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

	/*!	update the distance number of the West adjacent square
	*	1. get the x, y coordiantes of the West adjacnet square using the member funtion of
	*	2. and cheke whether it is empty by comparing the distance with the Macro "B_EMPTY"
	*	3. if it is empty, update the distance number using the current distance plus 1 using the member function of "board.setSquare()"
	*	4. push the updated West adjacnet square to the working set using the member function of "wset.push_back()".
	*/
	for(int j = -1; j < 2; j++)
	{
		for(int i = -1; i < 2; i++)
		{
			if(std::abs(j) != std::abs(i))		// Von Neumann neighbourhood (Manhattan)
			{
				tempIndex = map->getI((current.x + i), (current.y + j));

				if(tempIndex == B_EMPTY)
				{
					map->setI((current.x + i), (current.y + j), (current.i + 1));
					//map->setParent((current.x + i), (current.y + j), current.x, current.y);
					wset.push_back(point((current.x + i), (current.y + j), (current.i + 1)));
				}
			}

			/*if((i == 0) && (j == 0))			// Moore / Conway neighbourhood (+Diagonal)
			{
				continue;
			}
			else
			{
				tempIndex = map->getI((current.x + i), (current.y + j));

				if(tempIndex == B_EMPTY)
				{
					map->setI((current.x + i), (current.y + j), (current.i + 1));
					wset.push_back(point((current.x + i), (current.y + j), (current.i + 1)));
				}
			}
			*/
		}
	}

}

// ------------------------------------------------------------------------------


void Lee::traceBack()
{
	int tempIndex = 0;

	point currentPoint = end;


	// push the end point to the path stack using the function "path_final.push()"
	path_final.push(currentPoint);


	/*!	find the lowest distance around the end point in the order of West, North,
	*	East and South, using the function of "board.getSquare()". Work back from
	*	lowest to S to populate the stack with the final path from S to T \n
	*
	*	1. using a do-while loop, starting from the lowest point of the end point,
	*		ending at the start point \n
	*
	*	2. in each loop, find the first point (with distance i-1, i is the distance
	*		of the current point) from the four adjacent points of the current point
	*		in the order of West, North, East and South, using fucntion of
	*		"board.getSquare()". \n
	*
	*	3. in each loop, push the frist i-1 point to the path stack using
	*		the function of "path_final.push()"
	*/

	do
	{
		// WEST -----------------------------------------------------------
		tempIndex = map->getI((currentPoint.x-1), currentPoint.y);

		if((tempIndex < currentPoint.i) && (tempIndex < B_WALL))
		{
			currentPoint.x--;
			currentPoint.i = tempIndex;
		}
		else
		{
			// NORTH ----------------------------------------------------------
			tempIndex = map->getI(currentPoint.x, (currentPoint.y - 1));

			if((tempIndex < currentPoint.i) && (tempIndex < B_WALL))
			{
				currentPoint.y--;
				currentPoint.i = tempIndex;
			}
			else
			{
				// EAST -----------------------------------------------------------
				tempIndex = map->getI((currentPoint.x + 1), currentPoint.y);

				if((tempIndex < currentPoint.i) && (tempIndex < B_WALL))
				{
					currentPoint.x++;
					currentPoint.i = tempIndex;
				}
				else
				{
					// SOUTH ----------------------------------------------------------
					tempIndex = map->getI(currentPoint.x, (currentPoint.y + 1));

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

		map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());


	}while(currentPoint.i != 0);

}

// ------------------------------------------------------------------------------


void Lee::drawPath()
{
	while(!path_final.empty())
	{
		map->setI(path_final.top().x, path_final.top().y, path_final.top().i);
		path_final.pop();

		map->updateData(wset.size(), profiler.getCurrentRSS(), profiler.getPeakRSS());

		Sleep(delay);
	}
}

