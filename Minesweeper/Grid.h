#define NOMINMAX
#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include "GridData.h"
#include "Item.h"
using namespace std;

class Grid {
	private:
		vector<vector<GridData>> grid;

		int row, column;
		int bombAmount;
		
		HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );

	public:
		Item item;

		void copyDisplay();

		void open(int row, int column, bool* secondChance);

		void flag(int row, int column);

		void sizeInit(int row, int column);

		void openAround(int x, int y);

		void initialize(int x, int y, int bombAmount, int rowRestrict, int columnRestrict, bool noGuess);

		void display(int mode);

		bool checkDeath();

		bool checkVictory();

		int prizeCount();

		int flagAmount();

		int totalBombFound();
};