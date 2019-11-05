/* 
 * File:   Deck.h
 * Author: Jaired Jawed
 *
 * Created on October 20, 2019, 2:01 PM
 */

#ifndef DECK_H
#define DECK_H

#include <algorithm>
#include <vector>
#include <cstdlib>
#include <stack>
#include <map>
#include "Card.h"
using namespace std;

class Deck {
private:
    // a map of cards and their respective values
    // examples, the card name "2", would have a value of 2
    // and "Ace" gets a value of 11
    map<string, int> cardTypes;
    static int getRandomNum(int);
public:
    stack<Card *> cards;
    void setupCardTypes();
    void setupDeck(int);
    void shuffleDeck();
};

// generates a random number for shuffling the cards
int Deck::getRandomNum(int i) { 
    return rand() % i; 
}

// push all cardTypes to the map
void Deck::setupCardTypes() {
    cardTypes.insert(pair<string, int>("2", 2));
    cardTypes.insert(pair<string, int>("3", 3));
    cardTypes.insert(pair<string, int>("4", 4));
    cardTypes.insert(pair<string, int>("5", 5));
    cardTypes.insert(pair<string, int>("6", 6));
    cardTypes.insert(pair<string, int>("7", 7));
    cardTypes.insert(pair<string, int>("8", 8));
    cardTypes.insert(pair<string, int>("9", 9));
    cardTypes.insert(pair<string, int>("10", 10));
    cardTypes.insert(pair<string, int>("Jack", 10));
    cardTypes.insert(pair<string, int>("Queen", 10));
    cardTypes.insert(pair<string, int>("King", 10));
    cardTypes.insert(pair<string, int>("Ace", 11));
}

// creates a deck from the map cardTypes based on the number of decks that the user enters
void Deck::setupDeck(int numDecks) {
    // there are four cards with the same number per deck
    int numCards = numDecks * 4;
    map<string, int>::iterator cardType;
    
    for (cardType = cardTypes.begin(); cardType != cardTypes.end(); ++cardType) {
        for (int i = 1; i <= numCards; i++) {
            Card* card = new Card;
            card->name = cardType->first;
            card->value = cardType->second;
            cards.push(card);
        }
    }
}

// randomly shuffles the created deck
void Deck::shuffleDeck() {
    vector <Card *> shuffledCards;

    // copy card stack to vector and empty stack
    while (!cards.empty()) {
        shuffledCards.push_back(cards.top());
        cards.pop();
    }
    
    // randomly shuffle card vector
    random_shuffle(shuffledCards.begin(), shuffledCards.end(), Deck::getRandomNum);
    
    // add cards back to stack
    for (int i = 0; i < shuffledCards.size(); i++) {
        cards.push(shuffledCards[i]);
    }
}

#endif /* DECK_H */
