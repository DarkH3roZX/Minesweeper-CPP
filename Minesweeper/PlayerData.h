#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class PlayerData {
	private:
		// Player Data
		char username[21];
		char password[101];

		int LEL;
		int wins;
		int loses;
		int bombFound;
		int encryptionKey;
		int itemInventory[5];
		int bestTimeSecond[4];

		// Utility
		int levelPercentage;

	public:
		PlayerData();

		void init(string username, string password);

		void passwordUpdate(string passwordInput);

		void statsUpdate(int mode);

		string getUsername();

		string getPassword();

		string passwordEncrypt(string passwordInput);

		string passwordDecrypt(string passwordInput);

		void userFileUpdate(vector<PlayerData> player);

		void profileDisplay(PlayerData player);

		void editMoney(int amount, char mode);

		int moneyDisplay();

		int getLevel(int wins);

		int getWins();

		int getLoses();

		int getBombFound();

		int getTime(int index);

		int getInventory(int index);

		void editInventory(int index, int amount, string mode);

		void editTime(int difficulty, int newTime);

		void addBombFound(int value);
};