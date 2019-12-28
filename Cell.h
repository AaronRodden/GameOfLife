#pragma once

class Cell
{
	private:
		bool living;
		int xCor;
		int yCor;
	public:
		Cell();
		Cell(bool living, int xCor, int yCor);

		int getX();
		int getY();
		int getValue();

};