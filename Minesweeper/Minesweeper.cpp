#define NOMINMAX
#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include "Utilities.h"
#include "Game.h"
#include "PlayerData.h"
#include "Grid.h"
#include "Item.h"
using namespace std;

int main()
{
    // Classes
    Utilities utility;
    Game game;
    vector<PlayerData> player;
    Grid grid;
    Item items;

    PlayerData playerServices;

    // Files
    fstream playerFile;
    fstream loginFile;

    // Temporary Variables
    PlayerData playerTemp;
    int tempInt;

    // Utility Variables
    int currPlayer = -1; // Index of the logged in player. -1 means no one logged in
    int amountInput;

    // Warp Variables
    int mainWarp;
    int loginWarp;
    int checkWarp;
    int shopWarp;
    int gameWarp;
    int itemWarp;
    int endGameWarp;
    int difficultyWarp;

    int adminWarp;
    int itemCheatWarp;

    // Game Variables
    int mines;
    int price;
    int startTime;
    int endTime;
    int timeSecond;
    int row, column; // Column vertical row horizontal
    int rowInput;
    int columnInput;
    int difficulty;
    int buyAmount;

    float area;
    float winRate;

    // Item Variables
    bool doubleMoney;
    bool shield; // Second chance item

    // Input variables
    string usernameInput;
    string passwordInput;
    string confirmInput;
    string cellInput;

    // Bool Variables
    bool isLoggedIn = false;
    bool validInput;
    bool noGuess = false;
    bool endGame;
    bool successFlag;
    bool deathFlag;
    bool roundZero;
    bool loadingPrinted;

    // Randomizer seed
    srand(time(NULL));

    // Color
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);

    /*
     File Code
     */
    // Access Users file and put it to the PlayerData Class
    playerFile.open("Users.evan", ios::in | ios::binary);

    // Creates the file if there's no file found
    if (!playerFile.is_open()) {
        playerFile.close();
        playerFile.open("Users.evan", ios::out | ios::binary);
    }

    // Reads the file
    else {
        while (!playerFile.eof()) {
            playerFile.read((char*)&playerTemp, sizeof(playerTemp));
            player.push_back(playerTemp);
        }
    }

    playerFile.close();

    // Accesses the login file and put it to the login data
    loginFile.open("LoginData.evan", ios::in | ios::binary);

    // Creates the file if there's no file found
    if (!loginFile.is_open()) {
        loginFile.close();
        loginFile.open("LoginData.evan", ios::out | ios::binary);

        loginFile.write((char*)&isLoggedIn, sizeof(isLoggedIn));
        loginFile.write((char*)&currPlayer, sizeof(currPlayer));
    }

    // Reads the file
    else {
        loginFile.read((char*)&isLoggedIn, sizeof(isLoggedIn));
        loginFile.read((char*)&currPlayer, sizeof(currPlayer));
    }

    loginFile.close();

    /*
    // Forgot password hack
    cout << playerServices.passwordDecrypt(player[0].getPassword());
    cin.get();
    */

    /*
     Game Code
     */
    do
    {
        // This code didn't run if one of the player logged in before
        if (!isLoggedIn) {
            do
            {
                // Login main menu
                do
                {
                    utility.logo();

                    cout << "1. Login" << endl;
                    cout << "2. Register" << endl;
                    cout << "3. Exit" << endl << endl;

                    cout << "Your choice : ";
                    cin >> loginWarp;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                while (loginWarp != 1 && loginWarp != 2 && loginWarp != 3);

                // Login
                if (loginWarp == 1) {
                    utility.logo();
                    utility.subtitle("Login");

                    // Username Input
                    cout << "Username : ";
                    getline(cin, usernameInput);

                    // Checks the index
                    currPlayer = -1;

                    for (int i = 0; i < player.size(); i++) {
                        if (usernameInput == player[i].getUsername()) {
                            currPlayer = i;

                            break;
                        }
                    }

                    // Password Input
                    cout << "Password : ";
                    SetConsoleTextAttribute(h, 255);
                    getline(cin, passwordInput);
                    SetConsoleTextAttribute(h, 15);

                    // Checks the password
                    if (currPlayer == -1) {
                        cout << "Incorrect Password!";
                        cin.get();

                        continue;
                    }
                    if (player[currPlayer].passwordEncrypt(passwordInput) != player[currPlayer].getPassword()) {
                        cout << "Incorrect Password!";
                        cin.get();

                        continue;
                    }

                    // Declare and update the login file
                    isLoggedIn = true;

                    game.loginFileUpdate(isLoggedIn, currPlayer);

                    break;
                }

                // Register
                else if (loginWarp == 2) {
                    utility.logo();
                    utility.subtitle("Register");

                    // Username Input
                    cout << "Username : ";
                    getline(cin, usernameInput);

                    // Checks whether the name is already taken or not
                    validInput = true;

                    for (auto& user : player) {
                        if (usernameInput == user.getUsername()) {
                            validInput = false;

                            break;
                        }
                    }

                    if (!validInput) {
                        cout << "Username already taken!";
                        cin.get();

                        continue;
                    }

                    // Checks if the username is not more then 20 characters long
                    if (usernameInput.length() > 20) {
                        cout << "Username is too long!";
                        cin.get();

                        continue;
                    }
                    
                    utility.logo();
                    utility.subtitle("Register");

                    // Password and Confirm Password Input
                    cout << "Password : ";
                    SetConsoleTextAttribute(h, 255);
                    getline(cin, passwordInput);
                    SetConsoleTextAttribute(h, 15);

                    cout << "Confirm password : ";
                    SetConsoleTextAttribute(h, 255);
                    getline(cin, confirmInput);
                    SetConsoleTextAttribute(h, 15);

                    // Checks whether password and confirm password is the same
                    if (passwordInput != confirmInput) {
                        cout << "Password and Confirm Password doesn't match!";
                        cin.get();

                        continue;
                    }

                    // Checks if the password is at least 8 characters long
                    if (passwordInput.length() < 8) {
                        cout << "Password must be at least 8 characters long!";
                        cin.get();

                        continue;
                    }

                    // Checks if the password is not more then 100 characters long
                    if (passwordInput.length() > 100) {
                        cout << "Password is too long!";
                        cin.get();

                        continue;
                    }

                    // Inputs the registration input to the data
                    playerTemp.init(usernameInput, passwordInput);
                    player.push_back(playerTemp);

                    // Login system in register menu
                    currPlayer = player.size() - 1;
                    isLoggedIn = true;

                    // File Update
                    game.loginFileUpdate(isLoggedIn, currPlayer);
                    playerServices.userFileUpdate(player);

                    break;
                }

                // Exit
                else if (loginWarp == 3) {
                    game.exitMenu();

                    return 0;
                }
            }
            while (true);
        }

        do
        {
            do
            {
                utility.logo();
                playerServices.profileDisplay(player[currPlayer]);

                cout << "1. Play Game" << endl;
                cout << "2. Stats" << endl;
                cout << "3. Shop" << endl;
                cout << "4. Instructions" << endl;
                cout << "5. Log Out" << endl;
                cout << "6. Exit" << endl << endl;

                cout << "Your Choice : ";
                cin >> mainWarp;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            while (mainWarp != 1 && mainWarp != 2 && mainWarp != 3 && mainWarp != 4 && mainWarp != 5 && mainWarp != 6 && mainWarp != 276145);

            // Play Game
            if (mainWarp == 1) {
                do
                {
                    // Difficulty Select
                    do
                    {
                        // Title and Subtitle display
                        utility.logo();
                        utility.subtitle("Select Difficulty");

                        // Menu display
                        cout << "1. Easy (8x8, 8 bombs)" << endl;
                        cout << "2. Normal (12x12, 24 bombs)" << endl;
                        cout << "3. Hard (16x16, 55 bombs)" << endl;
                        cout << "4. Extreme (20x20, 100 bombs)" << endl;
                        cout << "5. Custom Mode" << endl;

                        // no guess mode display
                        cout << "6. Turn ";

                        if (noGuess)
                            cout << "OFF no guess mode ";
                        else
                            cout << "ON no guess mode ";

                        cout << "(Coming Soon!)" << endl;

                        cout << "7. Main Menu" << endl << endl;

                        // Choice Input
                        cout << "Your Choice : ";
                        cin >> difficultyWarp;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    while (difficultyWarp != 1 && difficultyWarp != 2 && difficultyWarp != 3 && difficultyWarp != 4 && difficultyWarp != 5 && difficultyWarp != 6 && difficultyWarp != 7);

                    // Easy
                    if (difficultyWarp == 1) {
                        // Initializes grid size and bomb amount
                        mines = 8;
                        row = 8;
                        column = 8;
                        difficulty = 0;
                    }

                    // Normal
                    else if (difficultyWarp == 2) {
                        // Initializes grid size and bomb amount
                        mines = 24;
                        row = 12;
                        column = 12;
                        difficulty = 1;
                    }

                    // Hard
                    else if (difficultyWarp == 3) {
                        // Initializes grid size and bomb amount
                        mines = 55;
                        row = 16;
                        column = 16;
                        difficulty = 2;
                    }

                    // Extreme
                    else if (difficultyWarp == 4) {
                        // Initializes grid size and bomb amount
                        mines = 100;
                        row = 20;
                        column = 20;
                        difficulty = 3;
                    }

                    // Custom Game
                    else if (difficultyWarp == 5) {
                        utility.logo();
                        utility.subtitle("Custom Game");

                        // Column amount input
                        cout << "Input the amount of columns (7-20) : ";
                        cin >> column;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // Column declaration
                        if (column < 7 || column > 20) {
                            cout << "Invalid Input!";
                            cin.get();

                            continue;
                        }

                        // Column amount input
                        cout << "Input the amount of rows (7-20) : ";
                        cin >> row;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // Column declaration
                        if (row < 7 || row > 20) {
                            cout << "Invalid Input!";
                            cin.get();

                            continue;
                        }

                        // Amount of bombs input
                        // "area / 3.33" algorithm is to limit the bomb amount, so the game wont be so hard
                        // Which means the area and bomb ratio must be the maximum of 1 : 3.33
                        area = (float)row * column;

                        cout << "Input the amount of bombs (7-" << (int)(area / 3.33) << ") : ";
                        cin >> mines;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // Amount of bomb declaration
                        if (mines < 7 || mines > (int)(area / 3.33)) {
                            cout << "Invalid Input!";
                            cin.get();

                            continue;
                        }

                        difficulty = 4;
                    }

                    // Turn on/off anti guess
                    else if (difficultyWarp == 6) {
                        cout << "This feature is unavailable yet!";
                        cin.get();

                        continue;
                    }

                    // Main Menu
                    else if (difficultyWarp == 7) {
                        break;
                    }

                    // Size initialization
                    grid.sizeInit(row, column);
                    
                    // Play Game
                    do
                    {
                        endGame = false;
                        deathFlag = false;
                        roundZero = true;
                        successFlag = false;
                        shield = false;
                        doubleMoney = false;

                        do
                        {
                            // Selection Menu
                            do
                            {
                                // Grid Display
                                system("cls");

                                if (roundZero) {
                                    cout << "Flag Counter : " << mines << endl << endl;
                                    grid.display(0);
                                }
                                else {
                                    cout << "Flag Counter : " << mines - grid.flagAmount() << endl << endl;
                                    grid.display(1);
                                }

                                // UI Display
                                cout << "1. Open" << endl;
                                cout << "2. Flag" << endl;
                                cout << "3. Restart" << endl;
                                cout << "4. Use Item" << endl;
                                cout << "5. Exit" << endl << endl;

                                cout << "Your Choice : ";
                                cin >> gameWarp;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            while (gameWarp != 1 && gameWarp != 2 && gameWarp != 3 && gameWarp != 4 && gameWarp != 5);

                            // Open
                            if (gameWarp == 1) {
                                // IsValid Reset
                                validInput = true;

                                // Cell input
                                game.boxInput(&validInput, &cellInput);

                                // Check whether the input is valid or not
                                if (!validInput) {
                                    cout << "Invalid Input!";
                                    cin.get();

                                    continue;
                                }

                                // Put the value to rowName and columnName
                                rowInput = stoi(cellInput.substr(1, 2)) - 1;
                                columnInput = tolower(cellInput[0]) - 'a';

                                // Input validation (value)
                                if (rowInput >= row || rowInput < 0 || columnInput >= column || columnInput < 0) {
                                    cout << "Invalid Input!";
                                    cin.get();

                                    continue;
                                }

                                // Open the cell
                                // If the grid is not initialized yet, open the grid
                                if (roundZero) {
                                    roundZero = false;
                                    grid.initialize(row, column, mines, row - 1 - rowInput, columnInput, false);

                                    // Time starter
                                    loadingPrinted = false;
                                    startTime = time(NULL);

                                    while (startTime == time(NULL)) {
                                        if (!loadingPrinted) {
                                            system("cls");
                                            cout << "Flag Counter : " << mines << endl << endl;
                                            grid.display(0);

                                            cout << "Generating Mines...";

                                            loadingPrinted = true;
                                        }
                                    }

                                    startTime++;
                                }

                                grid.open(row - 1 - rowInput, columnInput, &shield);
                            }

                            // Flag
                            else if (gameWarp == 2) {
                                // Check so the player can't flag while the box is not initialized yet
                                if (roundZero) {
                                    cout << "Cannot flag when it's not initialized!";
                                    cin.get();

                                    continue;
                                }

                                // IsValid Reset
                                validInput = true;

                                // Cell input
                                game.boxInput(&validInput, &cellInput);

                                // Check whether the input is valid or not
                                if (!validInput) {
                                    cout << "Invalid Input!";
                                    cin.get();

                                    continue;
                                }

                                // Put the value to rowName and columnName
                                rowInput = stoi(cellInput.substr(1, 2)) - 1;
                                columnInput = tolower(cellInput[0]) - 'a';

                                // Input validation (value)
                                if (rowInput >= row || rowInput < 0 || columnInput >= column || columnInput < 0) {
                                    cout << "Invalid Input!";
                                    cin.get();

                                    continue;
                                }

                                // Flags the grid
                                grid.flag(row - 1 - rowInput, columnInput);
                            }

                            // Restart
                            else if (gameWarp == 3) {
                                do
                                {
                                    cout << "Are you sure you want to restart?" << endl;
                                    cout << "1. Yes" << endl;
                                    cout << "2. No" << endl << endl;

                                    cout << "Your Choice : ";
                                    cin >> checkWarp;
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                while (checkWarp != 1 && checkWarp != 2);

                                if (checkWarp == 1) {
                                    deathFlag = true;
                                    player[currPlayer].statsUpdate(2);
                                }
                            }

                            // Use Item
                            else if (gameWarp == 4) {
                                do
                                {
                                    cout << endl << "1. Gold Pig (" << player[currPlayer].getInventory(0) << ")" << endl;
                                    cout << "2. Mine Detector (" << player[currPlayer].getInventory(1) << ")" << endl;
                                    cout << "3. Magnifying Glass (" << player[currPlayer].getInventory(2) << ")" << endl;
                                    cout << "4. Time Machine (" << player[currPlayer].getInventory(3) << ")" << endl;
                                    cout << "5. Force Field (" << player[currPlayer].getInventory(4) << ")" << endl;
                                    cout << "6. Exit" << endl << endl;

                                    cout << "Your Choice : ";
                                    cin >> itemWarp;
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                while (itemWarp != 1 && itemWarp != 2 && itemWarp != 3 && itemWarp != 4 && itemWarp != 5 && itemWarp != 6);

                                // Gold Pig
                                if (itemWarp == 1) {
                                    if (!roundZero) {
                                        cout << "Item can't be activated during game!";
                                        cin.get();
                                    }
                                    else if (player[currPlayer].getInventory(0) < 1) {
                                        cout << "Insufficent amount!";
                                        cin.get();
                                    }
                                    else if (doubleMoney) {
                                        cout << "Item already activated!";
                                        cin.get();
                                    }
                                    else {
                                        items.goldPig(&doubleMoney);
                                        player[currPlayer].editInventory(0, 1, "Use");

                                        // File Update
                                        playerServices.userFileUpdate(player);
                                    }
                                }

                                // Mine Detector
                                else if (itemWarp == 2) {
                                    if (roundZero) {
                                        cout << "Initialize the grid first before using!";
                                        cin.get();
                                    }
                                    else if (player[currPlayer].getInventory(1) < 1) {
                                        cout << "Insufficent amount!";
                                        cin.get();
                                    }
                                    else {
                                        grid.item.mineDetector(row, column);
                                        player[currPlayer].editInventory(1, 1, "Use");

                                        // File Update
                                        playerServices.userFileUpdate(player);
                                    }
                                }

                                // Magnifying Glass
                                else if (itemWarp == 3) {
                                    if (roundZero) {
                                        cout << "Initialize the grid first before using!";
                                        cin.get();
                                    }
                                    else if (player[currPlayer].getInventory(2) < 1) {
                                        cout << "Insufficent amount!";
                                        cin.get();
                                    }
                                    else {
                                        grid.item.magnifyingGlass(row, column);
                                        player[currPlayer].editInventory(2, 1, "Use");

                                        // File Update
                                        playerServices.userFileUpdate(player);
                                    }
                                }

                                // Time Machine
                                else if (itemWarp == 4) {
                                    if (roundZero) {
                                        cout << "Initialize the grid first before using!";
                                        cin.get();
                                    }
                                    else if (player[currPlayer].getInventory(3) < 1) {
                                        cout << "Insufficent amount!";
                                        cin.get();
                                    }
                                    else {
                                        grid.item.timeMachine(row, column);
                                        player[currPlayer].editInventory(3, 1, "Use");

                                        // File Update
                                        playerServices.userFileUpdate(player);
                                    }
                                }

                                // Force Field
                                else if (itemWarp == 5) {
                                    if (player[currPlayer].getInventory(4) < 1) {
                                        cout << "Insufficent amount!";
                                        cin.get();
                                    }
                                    else if (shield) {
                                        cout << "Item already active!";
                                        cin.get();
                                    }
                                    else {
                                        grid.item.forceField(&shield);
                                        player[currPlayer].editInventory(4, 1, "Use");

                                        // File Update
                                        playerServices.userFileUpdate(player);
                                    }
                                }
                            }

                            // Exit
                            else if (gameWarp == 5) {
                                do
                                {
                                    cout << "Are you sure you want to exit?" << endl;
                                    cout << "1. Yes" << endl;
                                    cout << "2. No" << endl << endl;

                                    cout << "Your Choice : ";
                                    cin >> checkWarp;
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                while (checkWarp != 1 && checkWarp != 2);

                                if (checkWarp == 1) {
                                    endGame = true;
                                    deathFlag = true;

                                    // File Update
                                    player[currPlayer].statsUpdate(2);
                                    playerServices.userFileUpdate(player);
                                }
                            }

                            // Check death
                            if (!roundZero && grid.checkDeath()) {
                                deathFlag = true;
                            }

                            // Check success
                            if (!roundZero && !deathFlag && grid.checkVictory()) {
                                successFlag = true;
                            }
                        }
                        while (!deathFlag && !successFlag);

                        // Death Display
                        if (deathFlag && !roundZero && grid.checkDeath()) {
                            // Time End
                            endTime = time(NULL);
                            timeSecond = endTime - startTime;

                            validInput = true;

                            // UI Display
                            do
                            {
                                // Grid Display
                                system("cls");
                                cout << "Flag Counter : " << mines - grid.flagAmount() << endl << endl;

                                grid.display(2);

                                // UI Display
                                cout << "=============" << endl;
                                cout << " YOU DIED!!!\a" << endl;
                                cout << "=============" << endl << endl;

                                // Stats display
                                game.timeDisplay(timeSecond);

                                cout << format("{0:<13} : ", "Bomb Found") << grid.prizeCount() << endl;
                                cout << format("{0:<13} : ", "Total Reward") << grid.prizeCount() << endl;

                                // Money Display and adds the price
                                // Valid Input prevents money duplicating by inputting an invalid input
                                if (validInput)
                                    player[currPlayer].editMoney(grid.prizeCount(), '+');

                                cout << format("{0:<13} : ", "Current Money") << player[currPlayer].moneyDisplay() << endl << endl;

                                cout << "1. Restart" << endl;
                                cout << "2. Game Menu" << endl;
                                cout << "Your Choice : ";
                                cin >> endGameWarp;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                if (endGameWarp != 1 && endGameWarp != 2)
                                    validInput = false;
                            }
                            while (endGameWarp != 1 && endGameWarp != 2);

                            // Main Menu
                            if (endGameWarp == 2) {
                                endGame = true;
                            }

                            // File Update
                            player[currPlayer].addBombFound(grid.prizeCount());
                            player[currPlayer].statsUpdate(2);
                        }

                        // Success Display
                        if (successFlag) {
                            // Time End
                            endTime = time(NULL);
                            timeSecond = endTime - startTime;

                            validInput = true;

                            do
                            {
                                // Grid Display
                                system("cls");
                                cout << "Flag Counter : " << mines - grid.flagAmount() << endl << endl;

                                grid.display(1);

                                // UI Display
                                cout << "============" << endl;
                                cout << " YOU WIN!!! " << endl;
                                cout << "============" << endl << endl;

                                // Time and best time display
                                if (difficulty != 4 && (player[currPlayer].getTime(difficulty) == -1 || timeSecond < player[currPlayer].getTime(difficulty))) {
                                    cout << "NEW BEST TIME!!" << endl;

                                    player[currPlayer].editTime(difficulty, timeSecond);
                                }

                                // Level Up Display
                                if (playerServices.getLevel(player[currPlayer].getWins()) != playerServices.getLevel(player[currPlayer].getWins() + 1)) {
                                    cout << "LEVEL UP (" << playerServices.getLevel(player[currPlayer].getWins() + 1) << ")!!" << endl;
                                }

                                game.timeDisplay(timeSecond);

                                // Stats display
                                cout << format("{0:<13} : ", "Bomb Found") << mines << endl;
                                cout << format("{0:<13} : ", "Win Reward") << mines / 4 << endl;
                                cout << format("{0:<13} : ", "Total Reward");

                                if (doubleMoney)
                                    cout << (mines + mines / 4) * 2 << " (2x Money)" << endl;
                                else
                                    cout << (mines + mines / 4) << endl;

                                // Money Display and adds the price
                                // Valid Input prevents money duplicating by inputting an invalid input
                                if (validInput) {
                                    if (doubleMoney)
                                        player[currPlayer].editMoney((mines + mines / 4) * 2, '+');
                                    else
                                        player[currPlayer].editMoney(mines + mines / 4, '+');
                                }

                                cout << format("{0:<13} : ", "Current Money") << player[currPlayer].moneyDisplay() << endl << endl;

                                // UI Display
                                cout << "1. Play Again" << endl;
                                cout << "2. Game Menu" << endl;
                                cout << "Your Choice : ";
                                cin >> endGameWarp;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                
                                if (endGameWarp != 1 && endGameWarp != 2)
                                    validInput = false;
                            }
                            while (endGameWarp != 1 && endGameWarp != 2);

                            // Main Menu
                            if (endGameWarp == 2) {
                                endGame = true;
                            }

                            // File Update
                            player[currPlayer].addBombFound(grid.prizeCount());
                            player[currPlayer].statsUpdate(1);
                        }

                        // File Update 2
                        playerServices.userFileUpdate(player);
                    }
                    while (!endGame);
                }
                while (true);
            }

            // Stats
            else if (mainWarp == 2) {
                // Logo and Subtitle Display
                utility.logo();
                utility.subtitle("Stats");

                // Win Rate Counter
                if (player[currPlayer].getWins() + player[currPlayer].getLoses() == 0)
                    winRate = 0;
                else
                    winRate = (float)player[currPlayer].getWins() / ((float)player[currPlayer].getWins() + (float)player[currPlayer].getLoses()) * 100;

                // Win and Lose Display
                cout << "Wins: " << player[currPlayer].getWins() << endl;
                cout << "Loses: " << player[currPlayer].getLoses() << endl;
                cout << "Win Rate: " << winRate << "%" << endl << endl;

                // Statistic Display
                cout << "Total bombs found: " << player[currPlayer].getBombFound() << endl;
                cout << "Games played: " << player[currPlayer].getWins() + player[currPlayer].getLoses() << endl << endl;

                // Best Time Display
                cout << "Best Time" << endl;

                // Easy Mode
                cout << "Easy: ";

                if (player[currPlayer].getTime(0) == -1) {
                    cout << "NO DATA" << endl;
                }
                else {
                    cout << player[currPlayer].getTime(0) / 60 << ":";

                    if (player[currPlayer].getTime(0) % 60 < 10)
                        cout << "0" << player[currPlayer].getTime(0) % 60 << endl;
                    else
                        cout << player[currPlayer].getTime(0) % 60 << endl;
                }

                // Normal Mode
                cout << "Normal: ";

                if (player[currPlayer].getTime(1) == -1) {
                    cout << "NO DATA" << endl;
                }
                else {
                    cout << player[currPlayer].getTime(1) / 60 << ":";

                    if (player[currPlayer].getTime(1) % 60 < 10)
                        cout << "0" << player[currPlayer].getTime(1) % 60 << endl;
                    else
                        cout << player[currPlayer].getTime(1) % 60 << endl;
                }

                // Hard Mode
                cout << "Hard: ";

                if (player[currPlayer].getTime(2) == -1) {
                    cout << "NO DATA" << endl;
                }
                else {
                    cout << player[currPlayer].getTime(2) / 60 << ":";

                    if (player[currPlayer].getTime(2) % 60 < 10)
                        cout << "0" << player[currPlayer].getTime(2) % 60 << endl;
                    else
                        cout << player[currPlayer].getTime(2) % 60 << endl;
                }

                // Extreme Mode
                cout << "Extreme: ";

                if (player[currPlayer].getTime(3) == -1) {
                    cout << "NO DATA" << endl;
                }
                else {
                    cout << player[currPlayer].getTime(3) / 60 << ":";

                    if (player[currPlayer].getTime(3) % 60 < 10)
                        cout << "0" << player[currPlayer].getTime(3) % 60 << endl;
                    else
                        cout << player[currPlayer].getTime(3) % 60 << endl;
                }

                // Footer Display
                cout << endl << "Press 'Enter' to go back to main menu.";
                cin.get();
            }

            // Shop
            else if (mainWarp == 3) {
                do
                {
                    do
                    {
                        shopWarp = 0;
                        utility.logo();
                        utility.subtitle("Items Shop");

                        cout << format(" {0:<3} | {1:<16} | {2:<8} | {3:<6} ", "Num", "Item Name", "Price", "Owned") << endl;
                        cout << "===========================================" << endl;
                        cout << format(" {0:<3} | {1:<16} | {2:<8} | {3:<6} ", 1, "Gold Pig", "50 LEL", player[currPlayer].getInventory(0)) << endl;
                        cout << format(" {0:<3} | {1:<16} | {2:<8} | {3:<6} ", 2, "Mine Detector", "150 LEL", player[currPlayer].getInventory(1)) << endl;
                        cout << format(" {0:<3} | {1:<16} | {2:<8} | {3:<6} ", 3, "Magnifying Glass", "225 LEL", player[currPlayer].getInventory(2)) << endl;
                        cout << format(" {0:<3} | {1:<16} | {2:<8} | {3:<6} ", 4, "Time Machine", "300 LEL", player[currPlayer].getInventory(3)) << endl;
                        cout << format(" {0:<3} | {1:<16} | {2:<8} | {3:<6} ", 5, "Force Field", "400 LEL", player[currPlayer].getInventory(4)) << endl << endl;

                        cout << "Cash : " << player[currPlayer].moneyDisplay() << endl;
                        cout << "Pick an item to buy (Input 6 to exit to main menu) : ";
                        cin >> shopWarp;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } 
                    while (shopWarp != 1 && shopWarp != 2 && shopWarp != 3 && shopWarp != 4 && shopWarp != 5 && shopWarp != 6);
                    
                    if (shopWarp != 6) {
                        // Input an amount of item to buy
                        cout << "How much would you like to buy : ";
                        cin >> buyAmount;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // Checks if the inputted value is valid
                        if (buyAmount <= 0) {
                            cout << "Invalid Input!";
                            cin.get();

                            continue;
                        }

                        // Checks if the player have enough LEL and level
                        if (!items.checkBuyable(shopWarp, buyAmount, player[currPlayer].moneyDisplay())) {
                            cout << "Not Enough Money!";
                            cin.get();

                            continue;
                        }

                        // Buy the item code
                        player[currPlayer].editInventory(shopWarp - 1, buyAmount, "Buy");

                        if (shopWarp == 1)
                            player[currPlayer].editMoney(50, '-');
                        else if (shopWarp == 2)
                            player[currPlayer].editMoney(150, '-');
                        else if (shopWarp == 3)
                            player[currPlayer].editMoney(225, '-');
                        else if (shopWarp == 4)
                            player[currPlayer].editMoney(300, '-');
                        else if (shopWarp == 5)
                            player[currPlayer].editMoney(400, '-');

                        cout << "Purchase Successful, Press 'Enter' to continue!";
                        cin.get();

                        // File Update
                        playerServices.userFileUpdate(player);
                    }
                }
                while (shopWarp != 6);
            }

            // Instructions
            else if (mainWarp == 4) {
                game.instructions();
            }

            // Log Out
            else if (mainWarp == 5) {
                isLoggedIn = false;
                currPlayer = -1;

                game.loginFileUpdate(isLoggedIn, currPlayer);

                break;
            }

            // Exit
            else if (mainWarp == 6) {
                game.exitMenu();

                return 0;
            }

            // Special Administrator Menu
            else if (mainWarp == 276145 && (player[currPlayer].getUsername() == "lol" || player[currPlayer].getUsername() == "DarkHeroZX" || player[currPlayer].getUsername() == "adVenT")) {
                do
                {
                    do
                    {
                        utility.logo();
                        utility.subtitle("Administrator Menu");

                        cout << "1. Money Cheat" << endl;
                        cout << "2. Burn Money" << endl;
                        cout << "3. Items Cheat" << endl;
                        cout << "4. Main Menu" << endl << endl;

                        cout << "Your Choice : ";
                        cin >> adminWarp;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    while (adminWarp != 1 && adminWarp != 2 && adminWarp != 3 && adminWarp != 4);

                    // Money Cheat
                    if (adminWarp == 1) {
                        cout << "Input amount of money to add : ";
                        cin >> amountInput;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        player[currPlayer].editMoney(amountInput, '+');

                        cout << amountInput << " LEL is added to your account!";
                        cin.get();
                    }

                    // Burn Money
                    else if (adminWarp == 2) {
                        player[currPlayer].editMoney(player[currPlayer].moneyDisplay(), '-');

                        cout << "All your LEL have been burnt!";
                        cin.get();
                    }

                    // Items Cheat
                    else if (adminWarp == 3) {
                        system("cls");
                        utility.logo();

                        cout << "1. Gold Pig" << endl;
                        cout << "2. Mine Detector" << endl;
                        cout << "3. Magnifying Glass" << endl;
                        cout << "4. Time Machine" << endl;
                        cout << "5. Force Field" << endl << endl;

                        cout << "Input item name : ";
                        cin >> itemCheatWarp;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Input amount of item to add : ";
                        cin >> amountInput;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        player[currPlayer].editInventory(itemCheatWarp - 1, amountInput, "Buy");

                        cout << "Item cheat success!";
                        cin.get();
                    }

                    playerServices.userFileUpdate(player);
                }
                while (adminWarp != 4);
            }
        }
        while (true);
    }
    while (true);

    return 0;
}