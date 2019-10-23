/* 
 * File:   Deck.h
 * Author: Jaired Jawed
 *
 * Created on October 20, 2019, 2:01 PM
 */

#ifndef DECK_H
#define DECK_H

#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "Card.h"

class Deck {
public:
    // a map of cards and their respective values
    // examples, the card name "2", would have a value of 2
    // and "Ace" gets a value of 11
    map<string, int> cardTypes;
    list<Card *> cards;

    // initializes Deck
    Deck();
    static int getRandomNum(int);
    void setupDeck(int);
    void shuffleDeck();
};

// push all cardTypes to the map
Deck::Deck() {
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

// generates a random number for shuffling the cards
int Deck::getRandomNum(int i) { 
    return rand() % i; 
}

// creates a deck from the map cardTypes based on the number of decks that the user enters
void Deck::setupDeck(int numDecks) {
    // there are four cards with the same number per deck
    int numCards = numDecks * 4;
    map<string, int>::iterator cardType;
    
    cardType = cardTypes.begin();
    while (cardType != cardTypes.end())
    {
        for (int i = 1; i <= numCards; i++)
        {
            Card *card = new Card;
            card->name = cardType->first;
            card->value = cardType->second;
            cards.push_back(card);
        }
        ++cardType;
    }
}

// copies the deck from a list to a vector so it can be randomly sorted
void Deck::shuffleDeck() {
    vector<Card *> copiedList(cards.begin(), cards.end());
    random_shuffle(copiedList.begin(), copiedList.end(), Deck::getRandomNum);
    
    cards.clear();
    copy(copiedList.begin(), copiedList.end(), back_inserter(cards));
}

#endif /* DECK_H */

