/* 
 * File:   Deck.h
 * Author: jairedjawed
 *
 * Created on October 20, 2019, 3:28 PM
 */

#ifndef DECK_H
#define DECK_H

#include <map>
#include <list>
#include <iterator>
#include <stdlib.h>
#include "Card.h"

class Deck {
public:
    list<Card *> cards;
    // a map of cards and their respective values
    // examples, the card name "2", would have a value of 2
    // and "Ace" gets a value of 11
    map<string, int> cardTypes;
    void setupDeck();
    void shuffleDeck();

    // initializes deck
    Deck();
};

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

// creates a deck of 52 cards from the card types
void Deck::setupDeck()
{
    map<string, int>::iterator cardType;

    for (cardType = cardTypes.begin(); cardType != cardTypes.end(); ++cardType)
    {
        // add 4 of each card to the deck
        for (int numCards = 1; numCards <= 4; numCards++)
        {
            Card *card = new Card;
            card->name = cardType->first;
            card->value = cardType->second;
            cards.push_back(card);
        }
    }
}

void Deck::shuffleDeck()
{
    list<Card *>::iterator card;

    for (card = cards.begin(); card != cards.end(); ++card)
    {
        cout << *card->name << endl;
    }
}

#endif /* DECK_H */

