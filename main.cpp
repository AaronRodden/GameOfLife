// ConsoleApplication1.cpp : Defines the entry point for the console application.

//#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <direct.h>

#include <conio.h>

#include "Cell.h"
#include "Grid.h"

using namespace std;

int main()
{
	int i = -1;
	cout << "Please enter a row amount" << endl;
	cin >> i;
	int rowAmount = i;

	cout << "Please enter a col amount" << endl;
	cin >> i;
	int colAmount = i;

	Grid grid(rowAmount, colAmount);

	string str;
	cout << "Starting coordinates for living cell(s)?" << endl;
	getline(cin,str);
	getline (cin, str);
	string startingCoors = str;

	grid.setInitLiving(startingCoors);

	grid.Display();

	bool life = true;
	bool onceFlag = false;
	while (life) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			//cout << "ESCAPE-PRESSED" << endl;
			life = false;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{	
			//cout << "Space pressed" << endl;
			grid.update();
			cout << "" << endl;
			grid.Display();
			cout << "" << endl;
			sleep(1);
		}
		
	}

	return 0;
}

