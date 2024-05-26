#include "generateNumber.h"
#include <iostream>
#include <random>

using namespace std;

// generateRandomNumber function variant to generate a random number in specific range
// used for npc to guess the number in custom difficulty
int generateNumber::generateRandomNumberByRange(const int &min, const int &max) {
    random_device seed;
    mt19937 gen{seed()};

    uniform_int_distribution<int> distance{min,max};
    int randomNum = distance(gen);

    return randomNum;
}

//Function to generate a number in specific range based on passed difficulty
vector<int> generateNumber::generateRandomNumber(const int &difficulty) {
    random_device seed;
    mt19937 gen{seed()};
    int randomNum{},min{0},max{0};

    switch (difficulty) {
        case 1:{
            //Easy difficulty range 1-100
            uniform_int_distribution<int> distance{1,100};
            randomNum = distance(gen);
            min = 1;
            max = 100;
            break;
        }
        case 2:{
            //Medium difficulty range 1-10000
            uniform_int_distribution<int> distance{1,10000};
            randomNum = distance(gen);
            min = 1;
            max = 10000;
            break;
        }
        case 3:{
            //Hard difficulty range 1-1000000
            uniform_int_distribution<int> distance{1,1000000};
            randomNum = distance(gen);
            min = 1;
            max = 1000000;
            break;
        }
        case 4:{
            //Checking if max value is larger than min, if not asking user to enter them again.
            while(true){
                cout << "Enter the minimal value: ";
                while (!(cin >> min)) {
                    cin.clear(); // Clear the errors flags
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
                    cerr << "Error, you have to enter a number: ";
                }

                cout << "Enter the maximum value: ";
                while (!(cin >> max)) {
                    cin.clear(); // Clear the errors flags
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
                    cerr << "Error, you have to enter a number: ";
                }

                if(min >= max){
                    cout << "Error, maximum value must be larger than minimal value, try again..." << endl;
                    min = 0;
                    max = 0;
                }
                else{
                    break;
                }
            }

            uniform_int_distribution<int> distance{min,max};
            randomNum = distance(gen);
            break;
        }
        case 5:{
            //Coin flip, range 0-1
            uniform_int_distribution<int> distance{0,1};
            randomNum = distance(gen);
            min = 0;
            max = 1;
            break;
        }
        default:{
            cerr << "Something went wrong..." << endl;
            break;
        }
    }

    vector<int> results {randomNum,min,max};

    return results;
}

// Function to choose a difficulty which is later used to
// generate a number between specific range based on difficulty.
int generateNumber::choseDifficulty() {
    cout <<"\nChose the difficulty:"<< endl;
    cout <<"1. Easy (1-100)"<< endl;
    cout <<"2. Normal (1-10000)"<< endl;
    cout <<"3. Hard (1-1000000)"<< endl;
    cout <<"4. Custom" << endl;
    int selectDifficulty{};

    while(true){
        cout << "Enter: ";
        while (!(cin >> selectDifficulty)) {
            cin.clear(); // Clear the errors flags
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid data
            cerr << "Error, you have to enter a number: ";
        }

        switch (selectDifficulty) {
            case 1:{
                //Easy difficulty
                return 1;
            }
            case 2:{
                //Medium difficulty
                return 2;
            }
            case 3:{
                //Hard difficulty
                return 3;
            }
            case 4:{
                //Custom difficulty
                return 4;
            }
            default:{
                //Default option for wrong entry
                cout << "Invalid option, try again..." << endl;
                break;
            }
        }
    }
}
