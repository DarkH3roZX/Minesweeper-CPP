#include "Game.h"

void Game::exitMenu() {
	utils.logo();

	cout << "=====================" << endl;
	cout << " Thanks for playing! " << endl;
	cout << "=====================" << endl << endl;

	cout << "Made by DarkH3roZX" << endl;
	cin.get();
}

void Game::loginFileUpdate(bool isLoggedIn, int currPlayer) {
	fstream file;

	file.open("LoginData.evan", ios::out | ios::binary);

	file.write((char*)&isLoggedIn, sizeof(isLoggedIn));
	file.write((char*)&currPlayer, sizeof(currPlayer));

	file.close();
}

void Game::boxInput(bool* validInput, string* cellInput) {
	string input;

	cout << "Input a cell number : ";
	getline(cin, input);

	// Input validation (length)
	if (input.length() != 2 && input.length() != 3) {
		*validInput = false;
	}

	// Input validation (column and row below 10)
	if (input.length() == 2 && (!isalpha(input[0]) || !isdigit(input[1]))) {
		*validInput = false;
	}

	// Input validation (column and row above and equal 10)
	if (input.length() == 3 && (!isalpha(input[0]) || !isdigit(input[1]) || !isdigit(input[2]))) {
		*validInput = false;
	}

	// Put the cell value
	if (*validInput) {
		*cellInput = input;
	}
}

void Game::timeDisplay(int second) {
	cout << "Time : " << second / 60 << ":";

	if (second % 60 < 10)
		cout << "0" << second % 60;
	else
		cout << second % 60;

	cout << endl << endl;
}

void Game::instructions() {
	int warp;

	do
	{
		do
		{
			utils.logo();
			utils.subtitle("Instructions");

			cout << "1. Basic Minesweeper Rules" << endl;
			cout << "2. How To Play" << endl;
			cout << "3. Items" << endl;
			cout << "4. Tips & Tricks" << endl;
			cout << "5. Main Menu" << endl << endl;

			cout << "Your Choice : ";
			cin >> warp;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		while (warp != 1 && warp != 2 && warp != 3 && warp != 4 && warp != 5);

		utils.logo();

		switch (warp) {
			case 1:
				utils.subtitle("Basic Minesweeper Rules");

				cout << "- Your objectives is to find all the bombs in the grid and if you do, you win." << endl;
				cout << "- The number indicates the amount of bombs available in the area around the number." << endl;
				cout << "  (For example 2 means there is 2 bomb in the area around the number." << endl;
				cout << "- If you think that the box is a bomb, you should flag the box." << endl << endl;

				cout << "Press 'Enter' to go back to instructions menu!";
				cin.get();

				break;

			case 2:
				utils.subtitle("How To Play");

				//SetConsoleTextAttribute(h, 79);

				cout << "I. Board Symbols" << endl;
				cout << "(1, 2, 3, ..., 8) : Numbers" << endl;
				cout << "(-) : Zero" << endl;
				cout << "(*) : Bomb" << endl;
				cout << "(F) : Flag" << endl;

				cout << "(";
				SetConsoleTextAttribute(h, 79);
				cout << "*";
				SetConsoleTextAttribute(h, 15);
				cout << ") : Bomb Exploded" << endl;

				cout << "(";
				SetConsoleTextAttribute(h, 79);
				cout << "F";
				SetConsoleTextAttribute(h, 15);
				cout << ") : Misplaced Flag" << endl;
				
				cout << "(Empty Board) : Unopened" << endl << endl;

				cout << "II. Shortcuts";
				cout << "- If all the flag requirement is put around a box, you can open the area all around" << endl;
				cout << "  that box. If you misplace the flag, you will die." << endl;
				cout << "- If the opened box is a 0, the area around it will open automatically" << endl << endl;

				cout << "III. Cell Input" << endl;
				cout << "- The cell contains row and column" << endl;
				cout << "- Row is named with numbers starting from 1" << endl;
				cout << "- Column is named with alphabet characters starting from \'A\'" << endl;
				cout << "- Cell input format must be \"(Column)(Row)\" without any spaces" << endl;
				cout << "- Column input can be lowercase or uppercase" << endl << endl;

				cout << "Press 'Enter' to go back to instructions menu!";
				cin.get();

				break;

			case 3:
				utils.subtitle("Items");

				cout << "I. GOLD PIG" << endl;
				cout << "- Doubles the amount of reward." << endl;
				cout << "- Player only can get the double reward on win." << endl;
				cout << "- This item can only be used before initializing the grid." << endl << endl;

				cout << "II. TIME MACHINE" << endl;
				cout << "- Allows the player to see what happened if a player opens the chosen box." << endl;
				cout << "- If the chosen box is safe, then the player can choose one more box to look at." << endl << endl;

				cout << "III. MAGNIFYING GLASS" << endl;
				cout << "- Helps the player to find 1 random unopened safe box." << endl << endl;

				cout << "IV. MINE DETECTOR" << endl;
				cout << "- Helps the player for 3 things randomly:" << endl;
				cout << "  a. Tell if the flag is correct." << endl;
				cout << "  b. Tell if the flag is incorrect." << endl;
				cout << "  c. Find the unflagged bomb." << endl << endl;

				cout << "V. FORCE FIELD" << endl;
				cout << "- Protects the player from death." << endl;
				cout << "- This item will expire when the player wins the game." << endl << endl;

				cout << "Press 'Enter' to go back to instructions menu!";
				cin.get();

				break;

			case 4:
				utils.subtitle("Tips & Tricks");

				cout << "1-2-1" << endl;
				cout << "+---+---+---+" << endl;
				cout << "| F |   | F |" << endl;
				cout << "+---+---+---+" << endl;
				cout << "| ";

				SetConsoleTextAttribute(h, 3);
				cout << "1";

				cout << " | ";
				SetConsoleTextAttribute(h, 10);
				cout << "2";

				cout << " | ";
				SetConsoleTextAttribute(h, 3);
				cout << "1";

				SetConsoleTextAttribute(h, 15);
				cout << " |" << endl;

				cout << "+---+---+---+" << endl << endl;

				cout << "1-2-2-1" << endl;

				cout << "+---+---+---+---+" << endl;
				cout << "|   | F | F |   |" << endl;
				cout << "+---+---+---+---+" << endl;
				cout << "| ";

				SetConsoleTextAttribute(h, 3);
				cout << "1";

				cout << " | ";
				SetConsoleTextAttribute(h, 10);
				cout << "2";

				cout << " | ";
				SetConsoleTextAttribute(h, 10);
				cout << "2";

				cout << " | ";
				SetConsoleTextAttribute(h, 3);
				cout << "1";

				SetConsoleTextAttribute(h, 15);
				cout << " |" << endl;

				cout << "+---+---+---+" << endl << endl;

				cout << "Press 'Enter' to go back to instructions menu!";
				cin.get();

				break;
		}
	}
	while (warp != 5);
}