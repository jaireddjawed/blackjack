/* 
 * File:   Game.h
 * Author: Jaired Jawed
 *
 * Created on October 20, 2019, 6:26 PM
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include "Deck.h"
#include "Dealer.h"
#include "Player.h"
#include "Card.h"

class Game {
private:
    Deck* deck;
    Dealer* dealer;
    list <Player *> players;
    list <Player *>::iterator player;
public:
    void start();
    void pullFundingForPlayerWinner(Player*);
    void pullFundingForDealer();
};

int totalWinnings = 0;

// recursion to iterate through players list
bool recursionThroughPlayers(Player* winner, list<Player *>::iterator player, list<Player *>::iterator end) {
    if (player == end) return true;
    
    if (winner->getEmail() != (*player)->getEmail())
    {
        float playerWager = (*player)->getWager();
        totalWinnings += playerWager;

        string email = (*player)->getEmail();
        string password = (*player)->getPassword();
        string name = (*player)->getName();
        float newBalance = (*player)->getAccountBalance() - playerWager;

        (*player)->savePlayerToFile(email, password, name, newBalance);
    }

    return recursionThroughPlayers(winner, ++player, end);
}

// gets the winners winnings from other players and the dealer
void Game::pullFundingForPlayerWinner(Player* winner)
{
    recursionThroughPlayers(winner, players.begin(), players.end());

    // add winnings from dealer
    totalWinnings += dealer->getWager();
    // add to winner balance
    winner->addToBalance(totalWinnings);
}

// subtract all amounts from each player when the dealer wins
void Game::pullFundingForDealer()
{
    for (player = players.begin(); player != players.end(); ++player)
    {
        float playerWager = (*player)->getWager();
        string email = (*player)->getEmail();
        string password = (*player)->getPassword();
        string name = (*player)->getName();
        float newBalance = (*player)->getAccountBalance() - playerWager;

        (*player)->savePlayerToFile(email, password, name, newBalance);
    }
}

vector<Player *> sortedPlayersByScore;

// recursively sort through players by score
void sortPlayersByScore(int n) {
    if (n == 1) {
        return;
    }

    for (int i = 0; i < sortedPlayersByScore.size() - 1; i++) {
        if (sortedPlayersByScore[i]->checkHand() > sortedPlayersByScore[i + 1]->checkHand()) {
            swap(sortedPlayersByScore[i], sortedPlayersByScore[i + 1]);
        }
    }
  
    sortPlayersByScore(n - 1); 
}

void Game::start() {
    cout << "Welcome to Jaired's Blackjack program!" << endl;

    int numDecks = 0;
    while (numDecks <= 0) {
        cout << "Enter the number of decks that you would like to use: ";
        cin >> numDecks;
        
        if (numDecks <= 0) {
            cout << "Please enter a number greater than 0!" << endl;   
        }
    }
    
    // setup and shuffle deck
    deck = new Deck;
    deck->setupCardTypes();
    deck->setupDeck(numDecks);
    deck->shuffleDeck();

    //setup dealer
    dealer = new Dealer;
    dealer->setWager();

    int numPlayers = 0;
    while (numPlayers <= 0) {
        cout << "Please enter the number of players: ";
        cin >> numPlayers;
        
        if (numPlayers <= 0) {
            cout << "You must have at least one player." << endl;
        }
        
        // iterate through each player and ask them to enter their login
        for (int i = 1; i <= numPlayers; i++) {
            char decision;
            cout << "Player " << i << ", do you have an existing account (Y/N): ";
            cin >> decision;
            
            Player* player = new Player;
            string email;
            string password;
            string name;
            float accountBalance;

            while (decision != 'Y' && decision != 'N') {
                cout << "That wasn't one of the options. Please enter (Y/N): ";
                cin >> decision;
            }
          
            if (decision == 'Y') {
                bool accountErrors;
                
                do {
                    cout << "Enter your email address: ";
                    cin >> email;

                    cout << "Enter your password: ";
                    cin >> password;

                    accountErrors = !player->getPlayerFromFile(email, password);
                } while (accountErrors);
            } else if (decision == 'N') {
                cout << "Enter your name: ";
                cin >> name;
                
                cout << "Enter your email address: ";
                cin >> email;
                
                cout << "Enter your password: ";
                cin >> password;
            }
            
            cout << "Your account balance is $" << player->getAccountBalance() << "." << endl;
            cout << "Would you like to add to your account balance (Y/N): ";
            cin >> decision;  

            while (decision != 'Y' && decision != 'N') {
                cout << "That wasn't one of the options. Please enter (Y/N): ";
                cin >> decision;
            }
            
            // If they choose no and don't have a balance, warn them that they need a balance in order to play
            if (decision == 'N' && player->getAccountBalance() <= 0) {
                cout << "You need to have a positive account balance in order to play." << endl;
            }
            
            if (decision == 'Y' || player->getAccountBalance() <= 0) {
                cout << "How much would you like to add to your account balance: ";
                cin >> accountBalance;
                
                // if the user doesn't have an account, the email will be blank
                if (player->getEmail() == "") {
                    player->savePlayerToFile(email, password, name, accountBalance);
                } else {
                    // otherwise add a balance to the existing user
                    player->addToBalance(accountBalance);
                }
          
                while (player->getAccountBalance() <= 0 || accountBalance <= 0) {
                    cout << "You need to add to your balance in order to keep playing." << endl;
                    cout << "Enter how much you would like to add to your balance: ";
                    cin >> accountBalance;
                }
            }   
        
            players.push_back(player);
        }
    }
    
    // loops through player and sets their wager, shows their first two cards
    for (player = players.begin(); player != players.end(); ++player) {
        float wager;
        cout << (*player)->getName() << ", please enter your wager: ";
        cin >> wager;
        
        while (wager > (*player)->getAccountBalance()) {
            cout << "Your wager exceeds your account balance." << endl;
            cout << "Please enter a new wager: ";
            cin >> wager;
        }
        
        (*player)->setWager(wager);
        (*player)->pullCardsFromDeck(deck, 2);

        // list both of the player's cards
        cout << (*player)->getName() << " gets a " << (*player)->cards[(*player)->cards.size() - 1]->name <<
                " and a " << (*player)->cards[(*player)->cards.size() - 2]->name << "." << endl;
        cout << "Your total is " << (*player)->checkHand() << "." << endl;
        
        // if the user gets 21 with their first hand, end the game here
        if ((*player)->checkHand() == 21) {
            cout << (*player)->getName() << " wins!";
            // end game here and pull funding for the winner
            pullFundingForPlayerWinner((*player));
            exit(EXIT_FAILURE);
        } else if ((*player)->checkHand() > 21) {
            cout << "You bust!" << endl;
        }
    }
    
    // give cards to the dealer
    dealer->pullCardFromDeck(deck, 2);
    cout << endl;
    cout << "The dealer sets his wager at $" << dealer->getWager() << "." << endl;
    cout << "The dealer gets a " << dealer->cards[dealer->cards.size() - 1]->name << " and a hidden card." << endl;
    cout << "His total is hidden, too." << endl;
    cout << endl;
    
    for (player = players.begin(); player != players.end(); ++player)
    {
        cout << (*player)->getName() << "'s turn." << endl;
        cout << endl;
            
        while ((*player)->checkHand() < 21)
        {
            string choice;
            cout << (*player)->getName() << ", would you like to \"hit\" or \"stay\": ";
            cin >> choice;

            while (choice != "hit" && choice != "stay")
            {
                cout << "That choice is not allowed." << endl;
                cout << "Would you like to \"hit\" or \"stay\": ";
                cin >> choice;
            }

            if (choice == "hit")
            {
                // pull a card from the deck and display it to the player
                (*player)->pullCardsFromDeck(deck, 1);
                cout << "You drew a(n) " << (*player)->cards[(*player)->cards.size() - 1]->name << "." << endl;
                cout << "Your total is " << (*player)->checkHand() << "." << endl;
            }
            else {
                break;
            }
        }
        
        if ((*player)->checkHand() > 21) {
            cout << "You bust!" << endl;
        }
    }
    
    // Show the dealer's hidden card and get their total for their hand
    cout << "Okay, dealer's turn." << endl;
    cout << "His hidden card was a " << dealer->cards[dealer->cards.size() - 2]->name << "." << endl;
    cout << "His total was " << dealer->checkHand() << "." << endl;
    cout << endl;
    
    while (dealer->checkHand() < 21) {
        string choice = dealer->makeChoice();

        // dealer must choose to hit if their hand is less than or equal to 17
        if (dealer->checkHand() <= 17 || choice == "hit")
        {
            dealer->pullCardFromDeck(deck, 1);
            cout << "Dealer chooses to hit." << endl;
            cout << "He draws a " << dealer->cards[dealer->cards.size() - 1]->name << "." << endl;
            cout << "His total is " << dealer->checkHand() << "." << endl;
        }
        else {
            cout << "Dealer stays." << endl;
            break;
        }
    }
    
    cout << endl;
    Player *highestScoredPlayer = new Player;

    for (player = players.begin(); player != players.end(); ++player) {
        sortedPlayersByScore.push_back((*player));
    }

    int n = sortedPlayersByScore.size();
    // recursion to sort players by score
    sortPlayersByScore(n);

    // list the scores from lowest to highest order
    for (int i = 0; i < sortedPlayersByScore.size(); i++) {
        cout << sortedPlayersByScore[i]->getName() << "'s total is " << sortedPlayersByScore[i]->checkHand() << "." << endl;
    }

    cout << endl;
    cout << "The dealer's total is " << dealer->checkHand() << "." << endl;

    if (dealer->checkHand() < highestScoredPlayer->checkHand()) {
        cout << highestScoredPlayer->getName() << "wins!" << endl;
        pullFundingForPlayerWinner(highestScoredPlayer);
    } else {
        cout << "The dealer wins!" << endl;
        pullFundingForDealer();
    }

}

#endif /* GAME_H */
