#include "generateNumber.h"
#include "computer.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor for the computer class
computer::computer():player("computer"), guessedNumbers{} { };

// MyTurn function for a computer, checking if the generated number was already typed by computer
// if yes, then generate a new unique one
int computer::myTurn(const int &min, const int &max) {
    int enteredValue {0};
    bool guessedAlready {false};

    do{
        // Generating a random number from min to max value
        enteredValue = generateNumber::generateRandomNumberByRange(min,max);

        // Checking if the generated number was already used in that game
        int i = count(guessedNumbers.begin(),guessedNumbers.end(),enteredValue);

        // If yes then the loop keep going
        if(i > 0){
            guessedAlready = true;
        }
        else{
            guessedAlready = false;
        }
    }while(guessedAlready);

    // Adding generated number to the list already used by the computer in that game
    guessedNumbers.emplace_back(enteredValue);

    cout << "Computer guess: " << enteredValue << endl;

    // Increasing the tryCount number
    tryCountIncrease();

    // Setting guessed Alredy bool back to true
    guessedAlready = true;

    return enteredValue;
}

