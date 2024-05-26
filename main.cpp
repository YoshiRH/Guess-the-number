#include "src/game.h"

#include <iostream>
#include <limits>

bool playAgain();

int main() {
    cout << "Welcome in the guess the number game!" << endl;
    cout << "Chose the mode you would like to play:" << endl;

    bool endGame{false};
    int gamemode{0};

    while(!endGame){
        cout << "1. Singleplayer" << endl;
        cout << "2. Versus (PC)" << endl;
        cout << "3. Computer guess" << endl;
        cout << "4. Versus (Multi)" << endl;
        cout << "5. Tournament" << endl;

        while (!(cin >> gamemode)) {
            cin.clear(); // Clear the errors flags
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
            cerr << "Error, you have to enter a number: ";
        }

        switch (gamemode) {
            case 1:{
                game::singleplayerMode();
                endGame = playAgain();
                break;
            }
            case 2:{
                game::versusMode();
                endGame = playAgain();
                break;
            }
            case 3:{
                game::computerMode();
                endGame = playAgain();
                break;
            }
            case 4:{
                game::versusMultiMode();
                endGame = playAgain();
                break;
            }
            case 5:{
                game::tournamentMode();
                endGame = playAgain();
                break;
            }
            default:{
                cout << "Wrong option, try again..." << endl;
                break;
            }
        }
    }

    cout << "\nThank you for the game!" << endl;
    return 0;
}

bool playAgain(){
    int value{0};

    cout << "Would you like to play again?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    while (!(cin >> value)) {
        cin.clear(); // Clear the errors flags
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
        cerr << "Error, you have to enter a number: ";
    }

    while(true) {

        switch (value) {
            case 1: {
                return false;
            }
            case 2: {
                return true;
            }
            default: {
                cout << "Wrong option, try again..." << endl;
                break;
            }
        }

    }
}
