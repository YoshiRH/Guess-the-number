#include "player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include <limits>

//Constructor of a player
player::player(string nick)
:nickname{std::move(nick)}, tryCountSingle{0}, bestTryCountSingle{0}, winCountSingle{0}, winCountVersus{0}, loseCountVersus{0},
winCountVersusMulti{0}, loseCountVersusMulti{0},bestOfWinCount{0}, isLeader{false} { }

// Function to save a data of the object of player to the txt file
void player::save() {
    // Create a name of file based on a nickname of player
    string fileName = "../saves/" + nickname + ".txt";

    // Open the file to read
    ifstream infile(fileName);

    // Find and check the existing value of bestTryCountSingle in the file and if it's smaller than
    // the value in the player object assign it to the value of the object
    if(infile.is_open()){
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            string key, value;
            ss >> key >> value;
            if (key == "Najlepsza") {
                int oldBestTryCountSingle;
                ss >> oldBestTryCountSingle;
                if (bestTryCountSingle > oldBestTryCountSingle) {
                    bestTryCountSingle = oldBestTryCountSingle;
                }
                break;
            }
        }
        // Close the file
        infile.close();
    }

    // Open the file
    ofstream outfile(fileName);

    // Check if something went wrong while trying to open the file
    if (!outfile.is_open()) {
        cerr << "Error, something went wrong, can't open the file." << endl;
        return;
    }

    // Save the data to file.txt
    outfile << "Nickname: " << nickname << endl;
    outfile << "[Single] Best_try_count: " << bestTryCountSingle << endl;
    outfile << "[Single] Win_count: " << winCountSingle << endl;
    outfile << "[Versus-Comp] Win_count: " << winCountVersus << endl;
    outfile << "[Versus-Comp] Lose_count: " << loseCountVersus << endl;
    outfile << "[Versus-Multi] Win_count: " << winCountVersusMulti << endl;
    outfile << "[Versus-Multi] Lose_count: " << loseCountVersusMulti << endl;
    outfile << "[Bool] Is_leader: " << (isLeader ? 1 : 0) << endl;

    // Close the file
    outfile.close();

    // Return info
    cout << "Saved in: " << fileName << endl;
}

// Function to check if the save file of the nickname of the player already exist
void player::hasSave() {
    // Create a name of file based on a nickname of player
    string fileName = "../saves/" + nickname + ".txt";
    bool end{false};

    // Check if file already exist
    ifstream infile(fileName);
    if (infile.good()) {
        infile.close();

        // Ask the user if he wants to load the data from the file
        int choice;
        do{
            cout << "Save of the player with nickname '" << nickname << "' already exist, what you want to do?" << endl;
            cout << "1. Load data" << endl << "2. Clear save" << endl;
            cin >> choice;

            switch (choice) {
                case 1:{
                    infile.open(fileName);
                    string line;
                    while (getline(infile, line)) {
                        // Parse the line from file
                        stringstream ss(line);
                        string key, name;
                        int value;
                        ss >> key >> name >> value;

                        // Assign the value from the file to the correct values in the object of player
                        if (key == "Nickname:")
                            nickname = name;
                        else if (key == "[Single]" && name == "Best_try_count:")
                            bestTryCountSingle = value;
                        else if (key == "[Single]" && name == "Win_count:")
                            winCountSingle = value;
                        else if (key == "[Versus-Comp]" && name == "Win_count:")
                            winCountVersus = value;
                        else if (key == "[Versus-Comp]" && name == "Lose_count:")
                            loseCountVersus = value;
                        else if (key == "[Versus-Multi]" && name == "Win_count:")
                            winCountVersusMulti = value;
                        else if (key == "[Versus-Multi]" && name == "Lose_count:")
                            loseCountVersusMulti = value;
                        else if (key == "[Bool]")
                            isLeader = value;
                    }
                    end = true;
                    infile.close();
                    break;
                }

                case 2:{
                    ofstream outfile(fileName, ios::trunc);
                    outfile.close();
                    cout << "File '" << nickname << "' has been cleared." << endl;
                    end = true;
                    break;
                }

                default:{
                    cerr << "Wrong option, try again..." << endl;
                    break;
                }
            }
        } while(!end);


    } else {
        // If there is no file with a name like the nickname of object close the function
        infile.close();
        return;
    }
}

// Player turn function
int player::myTurn(const int &min, const int &max) {
    int enteredValue {0};

    while(true){
        // Asking user for a number
        cout << "[ " << nickname << " ] Enter the number: ";
        while (!(cin >> enteredValue)) {
            cin.clear(); // Clear the errors flags
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
            cerr << "Error, you have to enter a number: ";
        }

        // Checking if the number is in range
        if(enteredValue < min || enteredValue > max){
            cout << "Number out of range, try again..." << endl;
        }
        else{
            break;
        }
    }

    // Increasing the tryCount number
    tryCountIncrease();

    return enteredValue;
}

// Function to increase the tryCount number
void player::tryCountIncrease() {
    tryCountSingle++;
}

void player::bestOfIncrease() {
    bestOfWinCount++;
}

// Function activated after the win of the player
void player::hasWon(const string &mode) {

    // Checking the mode of the game passed in the function and increasing
    // specific winCount game mode
    if(mode == "single"){
        cout << "Congratulations!\n" << nickname << " has guessed the number in " << tryCountSingle << " tries!\n\n" << endl;

        winCountSingle++;
        if(tryCountSingle<bestTryCountSingle || bestTryCountSingle==0){
            bestTryCountSingle = tryCountSingle;
        }
    }
    else if(mode == "versus"){
        cout << "Congratulations!\n" << nickname << " has guessed the number in " << tryCountSingle << " tries!\n\n" << endl;

        winCountVersus++;
    }
    else if(mode == "versusMulti"){
        cout << "Congratulations!\n" << nickname << " has won the game." << endl;

        winCountVersusMulti++;

        if(!isLeader){
            isLeader = true;
        }
    }

    // Saving data
    save();
}
// Function activated after defeat
void player::hasLost(const string &mode) {
    // Checking the mode of the game passed in the function and increasing
    // specific winCount game mode

    if(mode == "versus"){
        loseCountVersus++;
    }
    else if(mode == "versusMulti"){
        loseCountVersusMulti++;

        if(isLeader){
            isLeader = false;
        }
    }

    // Saving data
    save();
}

player::~player() = default;

