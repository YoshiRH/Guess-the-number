#include "game.h"
#include "player.h"
#include "computer.h"
#include "generateNumber.h"

#include <string>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Singleplayer mode, user choose the difficulty (range of the random number) and next he needs to guess the number
void game::singleplayerMode() {
    // Asking for the nickname
    string nick;
    cout << "Enter your nickname: ";
    cin >> nick;

    // Creating a player and checking if the save with that name already exist
    player p1(nick);
    p1.hasSave();

    // Asking for the difficulty and then generating a random number in specific range
    int diff = generateNumber::choseDifficulty();

    // Returning 1) random number 2) minimum value 3) maximum value to the vector which is container
    vector<int> customGenerateResults = generateNumber::generateRandomNumber(diff);

    // Align a number received from the generateRandomNumber function to the randomNumber
    // and value of min and max of that range
    int randomNumber = customGenerateResults[0];
    int minValue = customGenerateResults[1];
    int maxValue = customGenerateResults[2];

    bool endGame{false};
    int enteredValue{0};

    cout << "\n----------START----------\n" << endl;
    // cout << randomNumber << endl; Line to show the number

    // Loop which is ended after the right guess
    while(!endGame){
        // myTurn function asking player for a number, checking if the number is in the range
        // and then returning that number to "enteredValue"
        enteredValue = p1.myTurn(minValue,maxValue);

        // Checking if the enteredValue is the same as the randomNumber
        if(enteredValue == randomNumber){
            // Starts the hasWon function - increasing the correct win Count mode and then saving the results
            p1.hasWon("single");
            endGame = true;
        }
        // Checking if the player is a leader
        else if(p1.checkLeader()){
            //Wrong number, giving a hint for player if he's a leader
            if(enteredValue > randomNumber + maxValue*0.1 || enteredValue < randomNumber - maxValue*0.1){
                cout << "You are far from the correct number..." << endl;
            }
            else{
                cout << "You are close to the correct number..." << endl;
            }
        }

        else{
            cout << "Wrong number, try again..." << endl;
        }

    }
}

// Versus mode, user play against computer in selected difficulty
void game::versusMode() {
    // Asking for the nickname
    string nick;
    cout << "Enter your nickname: ";
    cin >> nick;

    // Creating a list of players one user, one computer,
    // Have to use a pointer of player because the computer which is derrivered from the player class will be inside
    vector<player*> playerList;

    // Coin flip
    vector<int> whoStarts = generateNumber::generateRandomNumber(5);

    // Setting the order of players
    if (whoStarts[0] == 1) {
        playerList.emplace_back(new player(nick));
        playerList.at(0)->hasSave();

        playerList.emplace_back(new computer());
        playerList.at(1)->hasSave();
    } else {
        playerList.emplace_back(new computer());
        playerList.at(0)->hasSave();

        playerList.emplace_back(new player(nick));
        playerList.at(1)->hasSave();
    }

    // Asking for the difficulty and then generating a random number in specific range
    int diff = generateNumber::choseDifficulty();

    // Returning 1) random number 2) minimum value 3) maximum value to the vector which is container
    vector<int> customGenerateResults = generateNumber::generateRandomNumber(diff);

    // Setting values for the generated number in specific range entered by the user
    // and value of min and max of that range
    int randomNumber = customGenerateResults[0];
    int minValue = customGenerateResults[1];
    int maxValue = customGenerateResults[2];
        

    bool endGame{false};
    int enteredValue{0},pos{0};

    cout << "\n----------START----------\n" << endl;
    // cout << randomNumber << endl; Line to show the number

    // Loop for the players to guess the number
    while (!endGame) {
        // myTurn function asking player for a number, checking if the number is in the range
        // and then returning that number to "enteredValue"
        enteredValue = playerList.at(pos)->myTurn(minValue,maxValue);

        //Checking if the enteredValue is the same as the randomNumber
        if (enteredValue == randomNumber) {
            // Starts the hasWon function - increasing the correct win Count mode and then saving the results
            playerList.at(pos)->hasWon("versus");

            // Removing the winner from the playerlist
            playerList.erase(playerList.begin()+pos);

            // Starting hasLost function for all the other players expect the winner, because he's already erased
            // from the list of players
            for(auto player:playerList){
                player->hasLost("versus");
            }

            endGame = true;
        }

        // Checking if the player is a leader
        else if(playerList.at(pos)->checkLeader()){
            // Wrong number, giving a hint for player if he's a leader
            if(enteredValue > randomNumber + maxValue*0.1 || enteredValue < randomNumber - maxValue*0.1){
                cout << "You are far from the correct number..." << endl;
            }
            else{
                cout << "You are close to the correct number..." << endl;
            }
        }

        else{
            cout << "Wrong number, try again..." << endl;
        }

        pos++;

        if(pos == playerList.size()){
            pos = 0;
        }
    }
}

// Computer mode, user enter the number which computer needs to guess
void game::computerMode() {
    // Choosing the difficulty to let computer know in which range he should try to guess the number
    int diff = generateNumber::choseDifficulty();
    int numberToGuess{0}, min{0}, max{0};
    
    // Switch made to let the user pick a number to guess by the computer in specific range
    switch (diff) {
        case 1: {

            // Loop asking user for the number in specific range
            while (true) {
                cout << "Enter the number from 1 to 100 to guess by the computer\nNumber: ";
                while (!(cin >> numberToGuess)) {
                    cin.clear(); // Clear the errors flags
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
                    cerr << "Error, you have to enter a number: ";
                }

                // Checking if the min value is larger than max
                if (numberToGuess < 1 || numberToGuess > 100) {
                    cout << "Invalid number, try again..." << endl;
                }
                else {
                    // Setting the minimum and maximum of the range in which computer will be guessing the number
                    min = 1;
                    max = 100;

                    break;
                }

            }

            break;
        }
        case 2: {

            // Loop asking user for the number in specific range
            while (true) {
                cout << "Enter the number from 1 to 10000 to guess by the computer\nNumber: ";
                cin >> numberToGuess;

                // Checking if the min value is larger than max
                if (numberToGuess < 1 || numberToGuess > 10000) {
                    cout << "Invalid number, try again..." << endl;
                }
                else {
                    // Setting the minimum and maximum of the range in which computer will be guessing the number
                    min = 1;
                    max = 10000;

                    break;
                }

                break;
            }

            break;
        }
        case 3: {

            // Loop asking user for the number in specific range
            while (true) {
                cout << "Enter the number from 1 to 1000000 to guess by the computer\nNumber: ";
                cin >> numberToGuess;

                // Checking if the min value is larger than max
                if (numberToGuess < 1 || numberToGuess > 1000000) {
                    cout << "Invalid number, try again..." << endl;
                }
                else {
                    // Setting the minimum and maximum of the range in which computer will be guessing the number
                    min = 1;
                    max = 1000000;

                    break;
                }

                break;
            }

            break;
        }
        case 4: {
            int minTemp{0}, maxTemp{0};

            // Loop asking user for the minimum and maximum value of the range in which computer will be guessing
            // the number
            while (true) {
                cout << "Enter the minimal value: ";
                cin >> minTemp;
                cout << "Enter the maximum value: ";
                cin >> maxTemp;

                // Checking if the min value is larger than max
                if (minTemp >= maxTemp) {
                    cout << "Error, maximum value must be larger than minimal value, try again..." << endl;

                    minTemp = 0;
                    maxTemp = 0;
                }
                else {
                    break;
                }
            }

            // Loop asking user for the number in specific range
            while (true) {
                cout << "Enter the number from " << minTemp << " to " << maxTemp << " to guess by the computer\nNumber: ";
                cin >> numberToGuess;

                if (numberToGuess < minTemp || numberToGuess > maxTemp) {
                    cout << "Invalid number, try again..." << endl;
                }
                else {
                    // Setting the minimum and maximum of the range in which computer will be guessing the number
                    min = minTemp;
                    max = maxTemp;

                    break;
                }

            }

            break;
        }
        default:{
            cout << "Something went wrong..." << endl;
            break;
        }
    }

    computer c1;
    c1.hasSave();
    bool endGame = false;

    cout << "\n----------START----------\n" << endl;

    // Loop which is ended after the right guess
    while(!endGame){
        // myTurn function returning a number in a range entered by the user
        int enteredValue = c1.myTurn(min,max);

        //Checking if the enteredValue is the same as the numberToGuess
        if(enteredValue == numberToGuess){
            // Starts the hasWon function - increasing the correct win Count mode and then saving the results
            c1.hasWon("single");
            endGame = true;
        }
    }
}

// Player vs x Players mode, user enter the number of players
void game::versusMultiMode() {
    // Creating a value to select a length of the game
    int bestOf{0};

    cout << "Choose the length of the game:" << endl;
    cout << "1. To one win" << endl;
    cout << "2. To three wins" << endl;
    cout << "3. To five wins" << endl;

    bool lengthSelected {false};

    while(!lengthSelected){
        while (!(cin >> bestOf)) {
            cin.clear(); // Clear the errors flags
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
            cerr << "Error, you have to enter a number: ";
        }

        switch (bestOf) {
            case 1:{
                bestOf = 1;
                lengthSelected = true;
                break;
            }
            case 2:{
                bestOf = 3;
                lengthSelected = true;
                break;
            }
            case 3:{
                bestOf = 5;
                lengthSelected = true;
                break;
            }
            default:{
                cout << "Wrong option, try again..." << endl;
                break;
            }
        }
    }

    int numberOfPlayers {0};

    cout << "Enter the number of players: ";
    while (!(cin >> numberOfPlayers)) {
        cin.clear(); // Clear the errors flags
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
        cerr << "Error, you have to enter a number: ";
    }


    // Creating a vector of players and a loop in the size of numberOfPlayers number
    // asking for a nickname for each and creating a new player in the vector
    vector<player> players{};
    for(int i=0 ; i<numberOfPlayers; i++){

        string nick;
        cout << "Enter your nickname: ";
        cin >> nick;

        players.emplace_back(nick);
        players.at(i).hasSave();
    }

    // Asking for the difficulty and then generating a random number in specific range
    int diff = generateNumber::choseDifficulty();

    // Returning 1) random number 2) minimum value 3) maximum value to the vector which is container
    vector<int> customGenerateResults = generateNumber::generateRandomNumber(diff);

    // Align a number received from the generateRandomNumber function to the randomNumber
    // and value of min and max of that range
    int randomNumber = customGenerateResults[0];
    int minValue = customGenerateResults[1];
    int maxValue = customGenerateResults[2];

    bool endGame{false};
    int enteredValue{0};

    cout << "\n----------START----------\n" << endl;
    // cout << randomNumber << endl; Line to show the number

    int pos{0};

    // Loop for the players to guess the number
    while (!endGame) {
        // myTurn function asking player for a number, checking if the number is in the range
        // and then returning that number to "enteredValue"
        enteredValue = players.at(pos).myTurn(minValue,maxValue);

        //Checking if the enteredValue is the same as the randomNumber
        if (enteredValue == randomNumber) {
            // After a good guess increasing the bestOfWinCount for the winner
            players.at(pos).bestOfIncrease();

            // Checking if the amount of the games that player won is equal to the bestOf value which is a length of the game
            // If yes then ending the game
            if(players.at(pos).getBestOfWinCount() == bestOf){

                // Starts the hasWon function - increasing the correct win Count mode and then saving the results
                players.at(pos).hasWon("versusMulti");

                // Removing the winner from the playerlist
                players.erase(players.begin()+pos);

                // Starting hasLost function for all the other players expect the winner, because he's already erased
                // from the list of players
                for(auto player:players){
                    player.hasLost("versusMulti");
                }

                endGame = true;

            }

            // If not then give a info about the win and generate a new random numeber to guess
            else{
                cout << "You have guessed the number!" << endl;
                cout << "You have to win " << bestOf - players.at(pos).getBestOfWinCount() << " more times to win the game.\n\n" << endl;

                // Generate a new number
                customGenerateResults = generateNumber::generateRandomNumber(diff);
                randomNumber = customGenerateResults[0];

                cout << "New number has been generated to guess, good luck!" << endl;
                cout << "--------------------------------------------------------\n\n" << endl;
                cout << randomNumber << endl;
                // Reseting the position of players
                pos = -1;
            }
        }

        // Checking if the player is a leader
        else if (players.at(pos).checkLeader()) {
            //Wrong number, giving a hint for player if he's a leader
            if (randomNumber > enteredValue) {
                cout << "Wrong number, aim higher" << endl;
            } else {
                cout << "Wrong number, aim lower" << endl;
            }
        }

        else{
            cout << "Wrong number, try again..." << endl;
        }

        // Moving to the next player
        pos++;

        // Reset the position to create a loop for player position
        if(pos == players.size()){
            pos = 0;
        }
    }
}

// Tournament mode
void game::tournamentMode() {
    int numberOfPlayers {0};

    // Asking for the numbers of players and validate it
    cout << "Enter the number of players: ";
    while (!(cin >> numberOfPlayers)) {
        cin.clear(); // Clear the errors flags
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
        cerr << "Error, you have to enter a number: ";
    }


    // Creating a vector of players and a loop in the size of numberOfPlayers number
    // asking for a nickname for each and creating a new player in the vector
    vector<player> players{};
    for(int i=0 ; i<numberOfPlayers; i++){

        string nick;
        cout << "Enter your nickname: ";
        cin >> nick;

        players.emplace_back(nick);
        players.at(i).hasSave();
    }

    // Asking for the difficulty and then generating a random number in specific range
    int diff = generateNumber::choseDifficulty();

    // Vector of class player object for losers of the tournamnt
    vector<player> losers{};

    // Starting a loop which is ended when there is only one player remaining -> winner of the tournament
    while (players.size() > 1) {
        // Vector of player to select winners of current stage to keep them in the game
        vector<player> nextRound {};

        // A for loop to represent a stage of the tournament, dividing players in pairs and start the game to
        // find a winner of that pair, loser is out of players vector
        for (int i = 0; i < players.size(); i++) {
            int pos = i;

            // Check if there is a pair of players
            if (i + 1 < players.size()) {
                bool endGame{false};
                int enteredValue{0};

                // Returning 1) random number 2) minimum value 3) maximum value to the vector which is container
                vector<int> customGenerateResults = generateNumber::generateRandomNumber(diff);

                // Align a number received from the generateRandomNumber function to the randomNumber
                // and value of min and max of that range
                int randomNumber = customGenerateResults[0];
                int minValue = customGenerateResults[1];
                int maxValue = customGenerateResults[2];

                cout << "\n\n START: " << players.at(pos).getName() << " vs " << players.at(pos+1).getName() << endl;
                // cout << randomNumber << endl; Line to show the number

                // Loop for the players to guess the number
                while (!endGame) {
                    // myTurn function asking player for a number, checking if the number is in the range
                    // and then returning that number to "enteredValue"
                    enteredValue = players.at(pos).myTurn(minValue,maxValue);

                    //Checking if the enteredValue is the same as the randomNumber
                    if (enteredValue == randomNumber) {

                        // Winner is moved to the winners vector
                        nextRound.push_back(players.at(pos));
                        cout << "The winner is " << players.at(pos).getName() << endl;

                        pos++;
                        // Validate the position of player (loser)
                        if(pos > i+1) {
                            pos = i;
                        }

                        cout << players.at(pos).getName() << " has lost and is out of the tournament." << endl;

                        // Moving loser of that pair do the vector of loser and removing him from the players vector
                        losers.emplace_back(players.at(pos));
                        players.erase(players.begin()+pos);

                        endGame = true;
                    }

                    // Checking if the player is a leader
                    else if (players.at(pos).checkLeader()) {
                        //Wrong number, giving a hint for player if he's a leader
                        if (randomNumber > enteredValue) {
                            cout << "Wrong number, aim higher" << endl;
                        } else {
                            cout << "Wrong number, aim lower" << endl;
                        }
                    }

                    else{
                        cout << "Wrong number, try again..." << endl;
                    }

                    // Moving to the next player
                    pos++;

                    // Reset the position to create a loop for player position
                    if(pos > i+1) {
                        pos = i;
                    }
                }

            }

            // Check if there is a not even number of players
            else {
                nextRound.push_back(players.at(i));
                cout << players.at(i).getName() << " Advance, because there is not even number of players" << endl;
            }
        }

        players = nextRound;
        cout << "\n\nRound has ended, the remaining players are: ";

        for (const auto &player : players) {
            cout << player.getName() << " ";
        }

        cout << "\n\n";
    }

    players.at(0).hasWon("versusMulti");

    for(auto player: losers){
        player.hasLost("versusMulti");
    }
}

