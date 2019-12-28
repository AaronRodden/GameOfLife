#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include "string.h"

#include "Cell.h"

class Grid
{
	private: 
		int rows;
		int cols;
		//Cell cellGrid[rows][cols];
		std::vector<std::vector<Cell>> cellGrid;

	public:
		Grid(int rows, int cols);

		int getRows();
		int getCols();
		std::vector<std::vector<Cell>> getGrid();
		void initGrid();
		void setInitLiving(std::string);
		void setLiving(Cell cell);
		std::vector<std::tuple<int, int>> getNeighbors(int x, int y);
		int Rules(int x, int y);
		void update();
		void Display();
};