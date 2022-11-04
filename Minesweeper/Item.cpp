#include "Item.h"

void Item::gridDisplay() {
	system("cls");

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			cout << grid[i][j].symbol << " ";
		}

		cout << "\n\n";
	}

	getchar();
}

void Item::gridCopyInit(vector<vector<GridData>> grid) {
	this->grid = grid;
}

bool Item::checkBuyable(int itemIndex, int amount, int lel) {
	int price;

	// Check the item price
	if (itemIndex == 1)
		price = 50; // Gold Pig
	else if (itemIndex == 2)
		price = 150; // Time Machine
	else if (itemIndex == 3)
		price = 225; // Magnifying Glass
	else if (itemIndex == 4)
		price = 300; // Mine Detector
	else if (itemIndex == 5)
		price = 400; // Force Field

	// Checks if the item is buyable
	if (price * amount <= lel)
		return true;
	else
		return false;
}

void Item::goldPig(bool* doubleMoney) {
	*doubleMoney = true;

	cout << "2x Money activated!";
	cin.get();
}

void Item::timeMachine(int row, int column) {
	int rowInput;
	int columnInput;

	bool validInput;

	string cellInput;

	do
	{
		// Reset
		validInput = true;

		// Cell input
		game.boxInput(&validInput, &cellInput);

		// Check whether the input is valid or not
		if (!validInput) {
			continue;
		}

		// Put the value to rowName and columnName
		rowInput = row - stoi(cellInput.substr(1, 2));
		columnInput = tolower(cellInput[0]) - 'a';

		// Input validation (value)
		if (rowInput >= row || rowInput < 0 || columnInput >= column || columnInput < 0) {
			continue;
		}

		break;
	}
	while (true);

	// If the chosen box is a bomb, no more chance to look at another one
	if (grid[rowInput][columnInput].symbol == '*') {
		cout << "You will die if you open " << (char)toupper(cellInput[0]) << cellInput.substr(1, 2) << "!";
		cin.get();
	}

	// Other chance
	else {
		cout << (char)toupper(cellInput[0]) << cellInput.substr(1, 2) << " is \'" << grid[rowInput][columnInput].symbol << "\'" << endl;
		cout << "You can find out 1 more box!" << endl;

		do
		{
			// Reset
			validInput = true;

			// Cell input
			game.boxInput(&validInput, &cellInput);

			// Check whether the input is valid or not
			if (!validInput) {
				continue;
			}

			// Put the value to rowName and columnName
			rowInput = row - stoi(cellInput.substr(1, 2));
			columnInput = tolower(cellInput[0]) - 'a';

			// Input validation (value)
			if (rowInput >= row || rowInput < 0 || columnInput >= column || columnInput < 0) {
				continue;
			}

			break;
		}
		while (true);

		// If the chosen box is a bomb
		if (grid[rowInput][columnInput].symbol == '*') {
			cout << "You will die if you open " << (char)toupper(cellInput[0]) << cellInput.substr(1, 2) << "!";
			cin.get();
		}

		// If the chosen box is a number
		else {
			cout << (char)toupper(cellInput[0]) << cellInput.substr(1, 2) << " is \'" << grid[rowInput][columnInput].symbol << "\'" << endl;
			cin.get();
		}
	}
}

void Item::magnifyingGlass(int row, int column) {
	int x, y; // x == column, y == row (basically cartesian coordinates)

	do
	{
		x = rand() % column;
		y = rand() % row;
	}
	while (grid[y][x].symbol == '*' || grid[y][x].isOpen);

	cout << (char)(x + 'A') << row - y << " is a safe box!";
	cin.get();
}

void Item::mineDetector(int row, int column) {
	int x, y; // x == column, y == row (basically cartesian coordinates)

	do
	{
		x = rand() % column;
		y = rand() % row;
	}
	while (!grid[y][x].isFlag && grid[y][x].symbol != '*');

	// (char)(x + 'A') << y + 1
	// Case 1 - Incorrect Flag
	// Case 2 - Correct Flag
	// Case 3 - Unfound bomb Flag
	if (grid[y][x].isFlag && grid[y][x].symbol != '*')
		cout << (char)(x + 'A') << row - y << "is not a bomb!";
	else if (grid[y][x].isFlag && grid[y][x].symbol == '*')
		cout << "Flag on " << (char)(x + 'A') << row - y << " is already placed correctly!";
	else
		cout << "Bomb found on " << (char)(x + 'A') << row - y << "!";

	cin.get();
}

void Item::forceField(bool* shield) {
	*shield = true;

	cout << "Force Field activated!";
	cin.get();
}