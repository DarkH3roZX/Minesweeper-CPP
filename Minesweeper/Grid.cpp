#include "Grid.h"

/*
 // Notes
 1. Every variable named x is equal to row
 2. Every variable named y is equal to column
 */

void Grid::copyDisplay() {
	item.gridDisplay();
}

void Grid::open(int x, int y, bool* secondChance) {
	// Variables Declaration
	int flags = 0;

	bool isValid = true;
	bool forceFieldDie = false;

	/* Checks if the player inputs the valid box to open */
	// Invalid case 1 = Inputted box is a flag
	if (grid[x][y].isFlag) {
		cout << "Remove the flag first and try again!";
		cin.get();

		return;
	}

	// Invalid case 2 = Inputted box and it's surroundings is already opened
	isValid = false;

	for (int i = (x - 1 >= 0 ? x - 1 : x); i <= (x + 1 < row ? x + 1 : x); i++) {
		for (int j = (y - 1 >= 0 ? y - 1 : y); j <= (y + 1 < column ? y + 1 : y); j++) {
			if (grid[i][j].isFlag)
				flags++;

			if (!grid[i][j].isOpen) {
				isValid = true;
			}
		}
	}

	if (!isValid) {
		cout << "Box and the area around it already opened!";
		cin.get();

		return;
	}

	// Changes the symbol '*' to 'X' if the player hits the bomb
	// Death Open With 2nd chance
	if (*secondChance && grid[x][y].symbol == '*') {
		cout << "You have been protected by a Force Field!";
		cin.get();

		*secondChance = false;
		grid[x][y].isFlag = true;

		// Copies the grid data to item class
		item.gridCopyInit(grid);

		return;
	}

	// Death Open Without 2nd chance
	else if (grid[x][y].symbol == '*') {
		grid[x][y].symbol = 'X';
	}

	// Open around if the area arround it is a 0
	else if (grid[x][y].symbol == '-') {
		openAround(x, y);
	}

	// Open around shortcut when the flag amount meet the number on the grid
	else if (isdigit(grid[x][y].symbol) && grid[x][y].isOpen && flags == grid[x][y].symbol - '0') {
		for (int i = (x - 1 >= 0 ? x - 1 : x); i <= (x + 1 < row ? x + 1 : x); i++) {
			for (int j = (y - 1 >= 0 ? y - 1 : y); j <= (y + 1 < column ? y + 1 : y); j++) {
				if (!grid[i][j].isFlag) {
					if (*secondChance && grid[i][j].symbol == '*') {
						forceFieldDie = true;
						grid[i][j].isFlag = true;

						continue;
					}

					grid[i][j].isOpen = true;

					// Death Open
					if (grid[i][j].symbol == '*' && !(*secondChance)) {
						grid[i][j].symbol = 'X';
					}

					// Open around if the area arround it is a 0
					else if (grid[i][j].symbol == '-') {
						openAround(i, j);
					}
				}
			}
		}

		if (forceFieldDie) {
			cout << "You have been protected by a Force Field!";
			cin.get();

			*secondChance = false;
		}
	}

	// Other invalid
	else if (grid[x][y].isOpen) {
		cout << "Invalid Input!";
		cin.get();

		return;
	}
			
	grid[x][y].isOpen = true;

	// Copies the grid data to item class
	item.gridCopyInit(grid);
}

void Grid::flag(int x, int y) {
	if (grid[x][y].isOpen) {
		cout << "Can't put flag in the opened box!";
		cin.get();
	}
	else {
		if (!grid[x][y].isFlag)
			grid[x][y].isFlag = true;
		else
			grid[x][y].isFlag = false;
	}

	// Copies the grid data to item class
	item.gridCopyInit(grid);
}

void Grid::sizeInit(int row, int column) {
	this->row = row;
	this->column = column;
}

void Grid::openAround(int x, int y) {
	bool isAlrOpen = true;

	// Open Around
	for (int i = (x - 1 >= 0 ? x - 1 : x); i <= (x + 1 < row ? x + 1 : x); i++) {
		for (int j = (y - 1 >= 0 ? y - 1 : y); j <= (y + 1 < column ? y + 1 : y); j++) {
			grid[i][j].isOpen = true;
		}
	}

	// i = row
	// j = column
	// Check if there's still a 0 in the area around the center
	for (int i = (x - 1 >= 0 ? x - 1 : x); i <= (x + 1 < row ? x + 1 : x); i++) {
		for (int j = (y - 1 >= 0 ? y - 1 : y); j <= (y + 1 < column ? y + 1 : y); j++) {
			// If the i and j points to the center, then don't check it again
			if (i == x && j == y)
				continue;

			if (grid[i][j].symbol == '-') {
				// This for loop prevents infinite recursive by not opening the opened zero again
				for (int k = (i - 1 >= 0 ? i - 1 : i); k <= (i + 1 < row ? i + 1 : i); k++) {
					for (int l = (j - 1 >= 0 ? j - 1 : j); l <= (j + 1 < column ? j + 1 : j); l++) {
						// If the k and l points to the center, then don't check it again
						if (k == i && l == j)
							continue;

						// If the grid is not opened yet, then it needs to be opened. So, the function runs again to open the area around it
						if (!grid[k][l].isOpen) {
							isAlrOpen = false;
							break;
						}
					}

					if (!isAlrOpen)
						break;
				}

				if (!isAlrOpen)
					openAround(i, j);
			}
		}
	}
}

void Grid::initialize(int x, int y, int bombAmount, int rowRestrict, int columnRestrict, bool noGuess) {
	// Int variables
	int row;
	int limit;
	int column;
	int temp;

	// Bool variables
	bool isValid;

	// bombLocations vectors
	vector<vector<bool>> bombLocations;
	vector<bool> bombTemp;

	// numbers vectors
	vector<vector<int>> numbers;
	vector<int> numbersTemp;

	// GridData temporary vectors
	GridData gridTemp;
	vector<GridData> gridVectorTemp;

	/*
	 * X means row
	 * Y means column
	 */

	/* Main Code */

	// Put the bomb amount value
	this->bombAmount = bombAmount;

	// Grid Init
	do
	{
		// Variables Reset
		isValid = true;

		// Clears the vectors
		grid.clear();
		bombLocations.clear();
		numbers.clear();

		// Initializes vector values
		for (int i = 0; i < x; i++) {
			bombLocations.push_back(bombTemp);
			numbers.push_back(numbersTemp);
			grid.push_back(gridVectorTemp);

			for (int j = 0; j < y; j++) {
				bombLocations[i].push_back(false);
				numbers[i].push_back(0);
				grid[i].push_back(gridTemp);
			}
		}

		// Put all the bombs
		for (int i = 0; i < bombAmount; i++) {
			do
			{
				isValid = true;

				if (i < bombAmount / x * x)
					row = i % x;
				else
					row = rand() % x;

				column = rand() % y;

				// Checks if the bomb is placed in restricted row and column
				// Restricted row and column means the coordinate where the player initializes
				for (int j = (rowRestrict - 1 >= 0 ? rowRestrict - 1 : rowRestrict); j <= (rowRestrict + 1 < x ? rowRestrict + 1 : rowRestrict); j++) {
					for (int k = (columnRestrict - 1 >= 0 ? columnRestrict - 1 : columnRestrict); k <= (columnRestrict + 1 < y ? columnRestrict + 1 : columnRestrict); k++) {
						if (row == j && column == k) {
							isValid = false;

							break;
						}
					}

					if (!isValid)
						break;
				}

				// Check if the bomb is placed in the area where already have a bomb
				if (bombLocations[row][column])
					isValid = false;
			}
			while (!isValid);

			bombLocations[row][column] = true;
		}

		// Checks the bomb placement and puts the numbers
		// If the bomb is in all 3x3, it means that the board is not valid
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				// Temp reset
				temp = 0;

				// Determines the limit
				// Limit is useful for the edge and corners
				limit = 8;

				if (i == 0 || i == x - 1 || j == 0 || j == y - 1) {
					limit = 3;

					if ((i != 0 && i != x - 1) || (j != 0 && j != y - 1))
						limit = 5;
				}

				// Actual Checking
				if (i - 1 >= 0 && j - 1 >= 0 && bombLocations[i - 1][j - 1])
					temp++;
				if (i - 1 >= 0 && bombLocations[i - 1][j])
					temp++;
				if (i - 1 >= 0 && j + 1 < y && bombLocations[i - 1][j + 1])
					temp++;
				if (j - 1 >= 0 && bombLocations[i][j - 1])
					temp++;
				if (j + 1 < y && bombLocations[i][j + 1])
					temp++;
				if (i + 1 < x && j - 1 >= 0 && bombLocations[i + 1][j - 1])
					temp++;
				if (i + 1 < x && bombLocations[i + 1][j])
					temp++;
				if (i + 1 < x && j + 1 < y && bombLocations[i + 1][j + 1])
					temp++;

				if (temp == limit && bombLocations[i][j]) {
					isValid = false;

					break;
				}

				numbers[i][j] = temp;
			}

			if (!isValid)
				break;
		}

		/*
		// noGuess extra checking
		if (noGuess) {

		}
		*/
	}
	while (!isValid);

	// Initializes the Grid
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			grid[i][j].isOpen = false;
			grid[i][j].isFlag = false;

			if (bombLocations[i][j]) {
				grid[i][j].symbol = '*';
			}
			else if (numbers[i][j] == 0) {
				grid[i][j].symbol = '-';
			}
			else {
				grid[i][j].symbol = numbers[i][j] + '0';
			}
		}
	}

	// Put the initialized grid value to item class
	item.gridCopyInit(grid);
}

void Grid::display(int mode) {
	// Mode = 0 -> Empty Grid Display
	// Mode = 1 -> Normal Display
	// Mode = 2 -> Endgame Display
	for (int i = 0; i < row * 2 + 1; i++) {
		// Prints the +---+---+
		if (i % 2 == 0) {
			cout << "    ";

			for (int j = 0; j < column; j++) {
				cout << "+---";
			}

			cout << "+" << endl;
		}

		// Prints the |   |   |
		else {
			cout << format(" {0:>2} ", row - i / 2);

			for (int j = 0; j < column; j++) {
				// Empty Grid Display
				if (mode == 0) {
					cout << "|   ";
				}

				// Normal Display
				else if (mode == 1) {
					if (grid[i / 2][j].isOpen) {
						cout << "| ";

						if (grid[i / 2][j].symbol == '1')
							SetConsoleTextAttribute(h, 9);
						else if (grid[i / 2][j].symbol == '2')
							SetConsoleTextAttribute(h, 10);
						else if (grid[i / 2][j].symbol == '3')
							SetConsoleTextAttribute(h, 12);
						else if (grid[i / 2][j].symbol == '4')
							SetConsoleTextAttribute(h, 13);
						else if (grid[i / 2][j].symbol == '5')
							SetConsoleTextAttribute(h, 14);
						else if (grid[i / 2][j].symbol == '6')
							SetConsoleTextAttribute(h, 11);
						else if (grid[i / 2][j].symbol == '7')
							SetConsoleTextAttribute(h, 6);
						else if (grid[i / 2][j].symbol == '8')
							SetConsoleTextAttribute(h, 7);
						else if (grid[i / 2][j].symbol == '-')
							SetConsoleTextAttribute(h, 8);

						cout << grid[i / 2][j].symbol;

						SetConsoleTextAttribute(h, 15);
						cout << " ";
					}
					else if (grid[i / 2][j].isFlag) {
						cout << "| ";
						cout << "F ";
					}
					else {
						cout << "|   ";
					}
				}

				// Endgame Display
				else if (mode == 2) {

					// Number, Bomb Exploded, Zero
					if (grid[i / 2][j].isOpen) {
						cout << "| ";

						if (grid[i / 2][j].symbol == '1')
							SetConsoleTextAttribute(h, 3);
						else if (grid[i / 2][j].symbol == '2')
							SetConsoleTextAttribute(h, 10);
						else if (grid[i / 2][j].symbol == '3')
							SetConsoleTextAttribute(h, 12);
						else if (grid[i / 2][j].symbol == '4')
							SetConsoleTextAttribute(h, 13);
						else if (grid[i / 2][j].symbol == '5')
							SetConsoleTextAttribute(h, 14);
						else if (grid[i / 2][j].symbol == '6')
							SetConsoleTextAttribute(h, 11);
						else if (grid[i / 2][j].symbol == '7')
							SetConsoleTextAttribute(h, 6);
						else if (grid[i / 2][j].symbol == '8')
							SetConsoleTextAttribute(h, 7);
						else if (grid[i / 2][j].symbol == '-')
							SetConsoleTextAttribute(h, 8);
						else if (grid[i / 2][j].symbol == 'X')
							SetConsoleTextAttribute(h, 79);

						if (grid[i / 2][j].symbol == 'X')
							cout << "*";
						else
							cout << grid[i / 2][j].symbol;

						SetConsoleTextAttribute(h, 15);
						cout << " ";
					}

					// Incorrect flag
					else if (grid[i / 2][j].isFlag && grid[i / 2][j].symbol != '*') {
						cout << "| ";

						SetConsoleTextAttribute(h, 79);
						cout << "F";
						SetConsoleTextAttribute(h, 15);

						cout << " ";
					}

					// Correct Flag
					else if (grid[i / 2][j].isFlag) {
						cout << "| ";
						cout << "F ";
					}

					// Unfound bomb
					else if (grid[i / 2][j].symbol == '*') {
						cout << "| * ";
					}

					// Empty
					else {
						cout << "|   ";
					}
				}
			}

			cout << "|" << endl;
		}
	}

	cout << "      ";

	for (int i = 0; i < column; i++) {
		cout << (char)(65 + i) << "   ";
	}

	cout << endl << endl;
}

bool Grid::checkDeath() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j].symbol == 'X') {
				return true;
			}
		}
	}

	return false;
}

bool Grid::checkVictory() {
	int opened = 0;

	// Check the amount of opened grid
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j].isOpen)
				opened++;
		}
	}

	// Checks whether all the non bomb grid is already opened or not
	// If yes, flag all the bombs then return true
	if (opened + bombAmount == row * column) {
		// Flags all the bomb
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (grid[i][j].symbol == '*')
					grid[i][j].isFlag = true;
			}
		}

		return true;
	}

	return false;
}

int Grid::prizeCount() {
	int result = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j].isFlag && grid[i][j].symbol == '*')
				result++;
		}
	}

	return result;
}

int Grid::flagAmount() {
	int result = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j].isFlag)
				result++;
		}
	}

	return result;
}