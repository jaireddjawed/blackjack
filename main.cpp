/* 
 * File:   main.cpp
 * Author: Jaired Jawed
 *
 * Created on October 20, 2019, 3:28 PM
 */

#include <iostream>
#include <list>
#include "Deck.h"
#include "Player.h"

using namespace std;

int main() {
    cout << "Welcome to Jaired's Blackjack program!" << endl;
    cout << endl;

    int numDecks = 0;

    while (numDecks <= 0)
    {
        cout << "Enter the number of decks that you would like to use: ";
        cin >> numDecks;

        if (numDecks <= 0) {
            cout << "Please enter a number greater than 0!" << endl;   
        }
    }

    Deck *deck = new Deck;
    deck->setupDeck(numDecks);
    deck->shuffleDeck();

    list<Player *> players;
    int numPlayers = 0;

    while (numPlayers <= 0)
    {
        cout << "Enter the number of players: ";
        cin >> numPlayers;
        
        if (numPlayers <= 0) {
            cout << "You must have at least one player." << endl;
        }
        
        string name;

        for (int i = 0; i < numPlayers; i++)
        {
            cout << "Player " << i + 1 << ", enter your first name: ";
            cin >> name;

            Player *player = new Player;
            player->name = name;
            
            for (int j = 0; j < 2; j++) {
                player->cards.push_back(deck->cards.front());
                deck->cards.pop_front();
            }
         
            players.push_back(player);
        }
    }

    list<Player *>::iterator player;
    for (player = players.begin(); player != players.end(); ++player)
    {   
        cout << (*player)->name << " gets a ";
        list<Card *>::iterator card;

        int i = 0;
        
        for (card = (*player)->cards.begin(); card != (*player)->cards.end(); ++card)
        {
            cout << (*card)->name;
            if (i == 0) {
                cout << " and ";
            }

            i++;
        }

        cout << ".";
        cout << endl;
        
        cout << "Your total is " << (*player)->getScore() << "." << endl;
    }

    list<Player *>::iterator itr;
    for (itr = players.begin(); itr != players.end(); ++itr) {
        // check everyone's scores
        while ((*itr)->getScore() < 21) {
            string choice;

            cout << (*itr)->name << ", would you like to \"hit\" or \"stay\": ";
            cin >> choice;
                        
            if (choice == "hit") {
                Card *newCard = new Card;
                newCard->name = deck->cards.front()->name;
                newCard->value = deck->cards.front()->value;
                
                (*itr)->cards.push_back(newCard);
                deck->cards.pop_front();
                
                cout << "You drew a " << newCard->name << "." << endl;
                cout << "Your total is " << (*itr)->getScore() << "." << endl;
            }

            if (choice == "stay");

            cout << endl;      
        }
    }
    
    return 0;
}
