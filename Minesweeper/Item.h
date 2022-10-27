#define NOMINMAX
#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include "GridData.h"
#include "Game.h"
using namespace std;

#ifndef Item_H
#define Item_H

class Item {
	private:
		vector<vector<GridData>> grid;
		Game game;

	public:
		void gridDisplay();

		void gridCopyInit(vector<vector<GridData>> grid);

		bool checkBuyable(int itemIndex, int amount, int lel);

		void goldPig(bool* doubleMoney);

		void timeMachine(int row, int column);

		void magnifyingGlass(int row, int column);

		void mineDetector(int row, int column);

		void forceField(bool* shield);
};

#endif