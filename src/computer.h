#ifndef PROJEKT_COMPUTER_H
#define PROJEKT_COMPUTER_H

#include "player.h"
#include <vector>

// Computer class which is derrivered from the player class, is supposed to take turns by auto.
class computer: public player{
private:
    vector<int> guessedNumbers {};

public:
    computer();
    int myTurn(const int &min, const int &max) override;
};


#endif //PROJEKT_COMPUTER_H
