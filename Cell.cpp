#include <iostream>

#include "Cell.h"


Cell::Cell() {}

Cell::Cell(bool l, int x, int y)
{
	living = l;
	xCor = x;
	yCor = y;
}

int Cell::getX()
{
		
	return xCor;
}

int Cell::getY()
{
	return yCor;
}

int Cell::getValue()
{
	if (living == false) {
		return 0;
	}
	else
	{
		return 1;
	}
}
