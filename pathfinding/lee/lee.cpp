/*
#include "lee.h"


Lee::Lee()
{

}

// ------------------------------------------------------------------------------


void Lee::generatePath(point s, point e)
{
	start = s;
	end = e;

	// ToDo: update to work with Node board[][]
	//board.setSquare(start.x, start.y, start.i);
	//board.setSquare(end.x, end.y, end.i);

	board.draw();
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
			board.draw();
			temp++;
		}

		wset.pop_front();
	}

}

// ------------------------------------------------------------------------------


bool Lee::checkAdjIndex(point tester, int index)
{
	if(board.getSquare(tester.x + 1, tester.y) == index)
		return true;
	else
	{
		if(board.getSquare(tester.x - 1, tester.y) == index)
			return true;
		else
		{
			if(board.getSquare(tester.x, tester.y + 1) == index)
				return true;
			else
			{
				if(board.getSquare(tester.x, tester.y - 1) == index)
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
	int tempSquare = 0;

	// update the distance number of the West adjacent square
	// 1. get the x, y coordiantes of the West adjacnet square using the member funtion of
	// 2. and cheke whether it is empty by comparing the distance with the Macro "B_EMPTY"
	// 3. if it is empty, update the distance number using the current distance plus 1 using the member function of "board.setSquare()"
	// 4. push the updated West adjacnet square to the working set using the member function of "wset.push_back()".
	tempSquare = board.getSquare((current.x-1), current.y);

	if(tempSquare == B_EMPTY)
	{
		board.setSquare((current.x-1), current.y, (current.i + 1));

		wset.push_back(point((current.x-1), current.y, (current.i + 1)));
	}


	// update the distance number of the North adjacent square
	tempSquare = board.getSquare(current.x, (current.y-1));

	if(tempSquare == B_EMPTY)
	{
		board.setSquare(current.x, (current.y-1), (current.i + 1));

		wset.push_back(point(current.x, (current.y-1), (current.i + 1)));
	}

		
	// update the distance number of the East adjacent square
	tempSquare = board.getSquare((current.x+1), current.y);

	if(tempSquare == B_EMPTY)
	{
		board.setSquare((current.x+1), current.y, (current.i + 1));

		wset.push_back(point((current.x+1), current.y, (current.i + 1)));
	}

			
	// update the distance number of the South adjacent square
	tempSquare = board.getSquare(current.x, (current.y+1));

	if(tempSquare == B_EMPTY)
	{
		board.setSquare(current.x, (current.y+1), (current.i + 1));

		wset.push_back(point(current.x, (current.y+1), (current.i + 1)));
	}

}

// ------------------------------------------------------------------------------


void Lee::traceBack()
{
	int tempSquare = 0;

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
		tempSquare = board.getSquare((currentPoint.x - 1), currentPoint.y);

		if((tempSquare < currentPoint.i) && (tempSquare < B_WALL))
		{
			currentPoint.x--;
			currentPoint.i = tempSquare;
		}
		else
		{
			// NORTH ----------------------------------------------------------
			tempSquare = board.getSquare(currentPoint.x, (currentPoint.y - 1));

			if((tempSquare < currentPoint.i) && (tempSquare < B_WALL))
			{
				currentPoint.y--;
				currentPoint.i = tempSquare;
			}
			else
			{
				// EAST -----------------------------------------------------------
				tempSquare = board.getSquare((currentPoint.x + 1), currentPoint.y);

				if((tempSquare < currentPoint.i) && (tempSquare < B_WALL))
				{
					currentPoint.x++;
					currentPoint.i = tempSquare;
				}
				else
				{
					// SOUTH ----------------------------------------------------------
					tempSquare = board.getSquare(currentPoint.x, (currentPoint.y + 1));

					if((tempSquare < currentPoint.i) && (tempSquare < B_WALL))
					{
						currentPoint.y++;
						currentPoint.i = tempSquare;
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
		board.setSquare(path_final.top().x, path_final.top().y, path_final.top().i);
		path_final.pop();
		board.draw();
		Sleep(100);
	}
}
*/

