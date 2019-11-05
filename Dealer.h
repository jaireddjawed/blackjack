/* 
 * File:   Dealer.h
 * Author: Jaired Jawed
 *
 * Created on October 20, 2019, 6:14 PM
 */

#ifndef DEALER_H
#define DEALER_H

#include <algorithm>
#include <vector>
#include <stdlib.h>

#include "Deck.h"
#include "Card.h"

using namespace std;

class Dealer {
private:
    float wager;
public:
    vector <Card *> cards;
    int checkHand();
    string makeChoice();
    void setWager();
    float getWager();
    void pullCardFromDeck(Deck*, int);
};

// gives the dealer a random value for their wager
void Dealer::setWager() {
    this->wager = rand() % 100 + 1;
}

// gets the dealer's wager
float Dealer::getWager() {
    return wager;
}

// takes the specified number of cards from the deck and
// gives them to the dealer
void Dealer::pullCardFromDeck(Deck* deck, int numCards) {
    if (deck->cards.size() < numCards) {
        cout << "The deck doesn't have enough cards!" << endl;
    } else {
        for (int i = 1; i <= numCards; i++) {
            Card* card = deck->cards.top();
            cards.push_back(card);
            deck->cards.pop();
        }
    }
}

int Dealer::checkHand() {
    int score = 0;
    for (int i = 0; i < cards.size(); i++) {
        score += cards[i]->value;
    }
    return score;
}

// randomly selects between hit and stay for the Dealer
string Dealer::makeChoice() {
    int choiceNumber = rand() % 2 + 1;

    if (choiceNumber == 1) {
        return "hit";
    }
    
    return "stay";
}

#endif /* DEALER_H */
