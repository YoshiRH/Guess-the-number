#ifndef PROJEKT_GENERATENUMBER_H
#define PROJEKT_GENERATENUMBER_H

#include <string>
#include <vector>

using namespace std;

//Class created to generate random number in selected
//difficulty range.
class generateNumber {
public:
    static int generateRandomNumberByRange(const int &min, const int &max);
    static vector<int> generateRandomNumber(const int& difficulty);
    static int choseDifficulty();
};


#endif //PROJEKT_GENERATENUMBER_H
