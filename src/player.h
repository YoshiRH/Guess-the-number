#ifndef PROJEKT_PLAYER_H
#define PROJEKT_PLAYER_H

#include <string>

using namespace std;

// Base player class, is used to create a object for a user (player)
class player {
private:
    string nickname;
    int tryCountSingle;
    int bestTryCountSingle;
    int winCountSingle;
    int winCountVersus;
    int loseCountVersus;
    int winCountVersusMulti;
    int loseCountVersusMulti;
    int bestOfWinCount;
    bool isLeader;

public:
    explicit player(string nick);
    virtual ~player();

    virtual void save();
    virtual void hasSave();
    void tryCountIncrease();
    void bestOfIncrease();
    virtual int myTurn(const int &min, const int &max);
    virtual void hasWon(const string &mode);
    virtual void hasLost(const string &mode);

    int getBestOfWinCount() const {return bestOfWinCount;};
    string getName() const {return nickname; };
    bool checkLeader() const { return isLeader;};
};


#endif //PROJEKT_PLAYER_H
