/* 
 * File:   Player.h
 * Author: Jaired Jawed
 *
 * Created on October 20, 2019, 3:55 PM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <list>

using namespace std;

class Player {
public:
    string name;
    list<Card *> cards;
    
    int getScore();
};

int Player::getScore() {
    int total = 0;

    list<Card *>::iterator card;
    card = cards.begin();
    
    while (card != cards.end())
    {
        total += (*card)->value;
        ++card;
    }
    
    return total;
}

#endif /* PLAYER_H */

