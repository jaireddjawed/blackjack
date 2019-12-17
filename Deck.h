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
#include <queue>
#include "Card.h"
using namespace std;


// quarternary tree
struct Node {
    Card *data;
    
    Node *child1;
    Node *child2;
    Node *child3;
    Node *child4;
};

// add a new card to the tree
struct Node* newNode(Card* card) {
    struct Node* temp = new Node;
    
    if (card == NULL) {
        return temp;
    }

    temp->data = new Card;
    temp->data->name = card->name;
    temp->data->value = card->value;

    return temp;
}

// inserts a new card into our tree
void insert(struct Node* temp, Card* card) {
    queue<struct Node*> q;
    q.push(temp);
    
    while (!q.empty()) { 
        struct Node* temp = q.front(); 
        q.pop(); 
  
        if (!temp->child1) {
            temp->child1 = newNode(card);
            break;
        } else {
            q.push(temp->child1);
        }
        
        if (!temp->child2) {
            temp->child2 = newNode(card);
            break;
        } else {
            q.push(temp->child2);
        }
        
        if (!temp->child3) {
            temp->child3 = newNode(card);
            break;
        } else {
            q.push(temp->child3);
        }
        
        if (!temp->child4) {
            temp->child4 = newNode(card);
            break;
        } else {
            q.push(temp->child4);
        }
    }
}

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
    void addTreeToStack(struct Node *);
};

// generates a random number for shuffling the cards
int Deck::getRandomNum(int i) { 
    return rand() % i; 
}

// push all cardTypes to the map
void Deck::setupCardTypes() {
    // a map of all the card types, ace is not included because
    // those will be the top nodes for our tree
    
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
}

// creates a deck from the map cardTypes based on the number of decks that the user enters
void Deck::setupDeck(int numDecks) {
    // there are four cards with the same number per deck
    map<string, int>::iterator cardType;
    
    Card* ace = new Card;
    ace->name = "Ace";
    ace->value = 11;

    struct Node* root = newNode(NULL);

    struct Node* firstAce = newNode(ace);
    struct Node* secondAce = newNode(ace);
    struct Node* thirdAce = newNode(ace);
    struct Node* fourthAce = newNode(ace);

    root->child1 = firstAce;
    root->child2 = secondAce;
    root->child3 = thirdAce;
    root->child4 = fourthAce;
    
    for (cardType = cardTypes.begin(); cardType != cardTypes.end(); ++cardType) {
        Card *card1 = new Card;
        card1->name = cardType->first;
        card1->value = cardType->second;
        insert(firstAce, card1);
        
        Card *card2 = new Card;
        card2->name = cardType->first;
        card2->value = cardType->second;
        insert(secondAce, card2);
        
        Card *card3 = new Card;
        card3->name = cardType->first;
        card3->value = cardType->second;
        insert(thirdAce, card3);
        
        Card *card4 = new Card;
        card4->name = cardType->first;
        card4->value = cardType->second;
        insert(fourthAce, card4);
    }

    for (int i = 1; i <= numDecks; i++) {
        // traverse the tree and add each card to the stack
        addTreeToStack(root->child1);
        addTreeToStack(root->child2);
        addTreeToStack(root->child3);
        addTreeToStack(root->child4);
    }
}

void Deck::addTreeToStack(struct Node* node) {
    if (node == NULL) {
        return;
    }

    Card* card = new Card;
    card->name = node->data->name;
    card->value = node->data->value;
    cards.push(card);

    addTreeToStack(node->child1);
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
