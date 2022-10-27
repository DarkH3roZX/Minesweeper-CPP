#include "PlayerData.h"

PlayerData::PlayerData() {}

void PlayerData::init(string username, string realPassword) {
	this->encryptionKey = 3 + rand() % 18; // Generates random number from 3 - 20
	this->wins = 0;
	this->loses = 0;
	this->LEL = 0;
	this->bombFound = 0;

	strcpy_s(this->username, username.c_str());
	strcpy_s(this->password, passwordEncrypt(realPassword).c_str());

	for (int i = 0; i < 5; i++) {
		if (i != 4)
			this->bestTimeSecond[i] = -1;
		
		this->itemInventory[i] = 0;
	}
}

void PlayerData::passwordUpdate(string passwordInput) {
	strcpy_s(this->password, passwordInput.c_str());
}

void PlayerData::statsUpdate(int mode) {
	// Mode 1 = adds the wins on the stats
	if (mode == 1)
		wins++;
	
	// Mode 2 = adds the loses on the stats
	else if (mode == 2)
		loses++;
}

string PlayerData::getUsername() {
	return username;
}

string PlayerData::getPassword() {
	return password;
}

string PlayerData::passwordEncrypt(string passwordInput) {
	string result1 = ""; // Result from step 1
	string result2 = ""; // Final result

	int realKey = 2 * this->encryptionKey + 3; // realKey is the decrypted key
	int sum = 0;

	// Step 1
	// ASCII encrypt from total of previous index
	for (int i = 0; i < passwordInput.length(); i++) {
		if (i == 0)
			sum += passwordInput[i];
		else
			sum += passwordInput[i] - 33;

		result1 += 33 + (sum - 33) % 94;
	}

	// Step 2
	// Encrypt with the key
	for (int i = 0; i < result1.length(); i++) {
		result2 += 33 + (result1[i] + realKey - 33) % 94;
	}

	return result2;
}

string PlayerData::passwordDecrypt(string passwordInput) {
	string result1 = ""; // Result from step 1
	string result2 = ""; // Final result

	int realKey = 2 * this->encryptionKey + 3; // realKey is the decrypted key
	int temp;

	// Step 1
	// Decrypt with the key
	for (int i = 0; i < passwordInput.length(); i++) {
		result1 += 33 + (passwordInput[i] + 94 - realKey - 33) % 94;
	}

	// Step 2
	// ASCII decrypt from total of previous index
	result2 += result1[0];
	int x;

	for (int i = 1; i < result1.length(); i++) {
		temp = (int)result1[i];

		for (x = 0; temp != (int)result1[i - 1]; x++) {
			temp--;

			if (temp == 32)
				temp = 126;
		}

		result2 += x + 33;
	}

	return result2;
}

void PlayerData::userFileUpdate(vector<PlayerData> player) {
	fstream file;
	PlayerData playerCopy[1000]; // This is to prevent vector errors on binary file

	// Copies the player variable
	for (int i = 0; i < player.size(); i++) {
		playerCopy[i] = player[i];
	}

	// Updates the file
	file.open("Users.evan", ios::out | ios::binary);

	for (int i = 0; i < player.size(); i++) {
		file.write((char*)&playerCopy[i], sizeof(playerCopy[i]));
	}

	file.close();
}

void PlayerData::profileDisplay(PlayerData player) {
	cout << format("{0:<24} | Level {1:<18}", "Welcome!", player.getLevel(player.getWins(), player.getLoses())) << endl;
	cout << format("{0:<24} | {1} LEL", player.getUsername(), player.moneyDisplay()) << endl << endl;
}

void PlayerData::editMoney(int amount, char mode) {
	if (mode == '+') // Mode 1 = add money
		this->LEL += amount;
	else if (mode == '-') // Mode 2 = take money
		this->LEL -= amount;
}

int PlayerData::moneyDisplay() {
	return LEL;
}

int PlayerData::getLevel(int wins, int loses) {
	return (wins * 5 + loses) / 40 + 1;
}

int PlayerData::getWins() {
	return wins;
}

int PlayerData::getLoses() {
	return loses;
}

int PlayerData::getBombFound() {
	return bombFound;
}

int PlayerData::getTime(int index) {
	return bestTimeSecond[index];
}

int PlayerData::getInventory(int index) {
	return itemInventory[index];
}

void PlayerData::editInventory(int index, int amount, string mode) {
	if (mode == "Buy") {
		itemInventory[index] += amount;
	}
	else if (mode == "Use") {
		itemInventory[index]--;
	}
}

void PlayerData::editTime(int difficulty, int newTime) {
	bestTimeSecond[difficulty] = newTime;
}

void PlayerData::addBombFound(int value) {
	bombFound += value;
}