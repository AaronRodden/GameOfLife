
#include "Grid.h"

Grid::Grid(int r, int c) 
{
	rows = r;
	cols = c;

	cellGrid.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		cellGrid[i].resize(cols);
	}

	initGrid();
}

int Grid::getRows() {
	return rows;
}

int Grid::getCols() {
	return cols;
}

std::vector<std::vector<Cell>> Grid::getGrid() {
	return cellGrid;
}


void Grid::initGrid()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Cell c (0, i, j);
			cellGrid[i][j] = c;
		}
	}
}
std::vector<std::string> tokenize(std::string coor, bool tokString) {
	
	std::vector<std::string> tokens;

	std::stringstream check1(coor);

	std::string intermediate;

	if (tokString == true) {
		while (getline(check1, intermediate, ' '))
		{
			tokens.push_back(intermediate);
		}
	}
	else {
		while (getline(check1, intermediate, ','))
		{
			tokens.push_back(intermediate);
		}
	}

	return tokens;
}

void Grid::setInitLiving(std::string coordinates)
{
	bool tokString = true;

	std::vector<std::string> tokens = tokenize(coordinates,tokString);
	tokString = false;

	for (int i = 0; i < tokens.size(); i++)
	{
		//std::cout << tokens[i] + "\n";
		std::vector<std::string> xy = tokenize(tokens[i],tokString);
		for (int j = 0; j < xy.size(); j += 2)
		{
			//std::cout << xy[j] + "\n";
			int x, y;
			
			x = std::stoi(xy[j]);
			y = std::stoi(xy[j + 1]);

			//std::cout << (x + y + " ");

			Cell c(true, x, y);
			cellGrid[x][y] = c;
		}
	}
}

void Grid::setLiving(Cell cell)
{
	int x = cell.getX();
	int y = cell.getY();

	cellGrid[x][y] = cell;

}

std::vector<std::tuple<int,int>> Grid::getNeighbors(int x, int y)
{
	std::vector<std::tuple<int,int>> neighbors;

	std::tuple<int,int> n1 = std::make_tuple(x - 1, y - 1);
	std::tuple<int, int> n2 = std::make_tuple(x - 1, y);
	std::tuple<int, int> n3 = std::make_tuple(x - 1, y + 1);

	std::tuple<int, int> n4 = std::make_tuple(x, y - 1);
	std::tuple<int, int> n5 = std::make_tuple(x, y + 1);

	std::tuple<int, int> n6 = std::make_tuple(x + 1, y - 1);
	std::tuple<int, int> n7 = std::make_tuple(x + 1, y);
	std::tuple<int, int> n8 = std::make_tuple(x + 1, y + 1);

	/*std::make_tuple<int, int>[] neighbors = { n1, n2, n3, n4, n5, n6, n7, n8 };*/

	neighbors.push_back(n1);
	neighbors.push_back(n2);
	neighbors.push_back(n3);
	neighbors.push_back(n4);
	neighbors.push_back(n5);
	neighbors.push_back(n6);
	neighbors.push_back(n7);
	neighbors.push_back(n8);

	return neighbors;

}

int Grid::Rules(int x, int y)
{
	int cellStatus = cellGrid[x][y].getValue();
	//Any live cell with fewer than two live neighbours dies, as if by underpopulation.
	//Any live cell with two or three live neighbours lives on to the next generation.
	//Any live cell with more than three live neighbours dies, as if by overpopulation.
	//Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
	int neighborCount = 0;

	std::vector<std::tuple<int, int>> neighbors = getNeighbors(x, y);

	for (int i = 0; i < neighbors.size(); i++)
	{
		std::tuple<int,int> neighbor = neighbors[i];

		int tupleX, tupleY;
		std::tie(tupleX, tupleY) = neighbors[i];
		//int tupleX = (int) std::get<0>(neighbor);
		//int tupleY = (int) std::get<1>(neighbor);

		//std::cout << tupleX + " " + tupleY << std::endl;

		if (tupleX < 0 || tupleY < 0) {
			continue;
		}
		if (tupleX > rows - 1 || tupleY > cols - 1)
		{
			continue;
		}

		if (cellGrid[tupleX][tupleY].getValue() == 1)
		{
			neighborCount++;
			//std::cout << "found a neighbor!\n";
		}
	}
	if (neighborCount < 2)
	{
		//Console.Write("Rule 1\n");
		return 0;
	}
	else if ((neighborCount == 2 || neighborCount == 3) && cellStatus == 1)
	{
		//Console.Write("Rule 2\n");
		return 1;
	}
	else if (neighborCount > 3)
	{
		//Console.Write("Rule 3\n");
		return 0;
	}
	else if (neighborCount == 3 && cellStatus == 0)
	{
		//Console.Write("Rule 4\n" + "");
		return 1;
	}
	else
	{
		return -1;
	}
}

void Grid::update()
{
	int row = getRows();
	int col = getCols();

	std::vector<Cell> newCells;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//Console.WriteLine(i);
			//Console.WriteLine(j);
			if (Rules(cellGrid[i][j].getX(), cellGrid[i][j].getY()) == 1)
			{
				Cell cell(true, i, j);
				newCells.push_back(cell);
			}
			else
			{
				Cell cell(false, i, j);
				newCells.push_back(cell);
			}
		}
	}

	for (int i = 0; i < newCells.size(); i++)
	{
		Cell cell = newCells[i];
		setLiving(cell);
	}

}

void Grid::Display()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << cellGrid[i][j].getValue();
		}
		std::cout << "" << std::endl;
	}
}
