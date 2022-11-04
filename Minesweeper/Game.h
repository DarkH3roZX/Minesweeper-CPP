#define NOMINMAX
#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include "Utilities.h"
using namespace std;

#ifndef Game_H
#define Game_H

class Game {
	private:
		Utilities utils;

		HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );

	public:
		void exitMenu();

		void loginFileUpdate(bool isLoggedIn, int currPlayer);

		void boxInput(bool* validInput, string* cellInput);

		void timeDisplay(int second);

		void instructions();

		void symbolPrint(char symbol);
};

#endif