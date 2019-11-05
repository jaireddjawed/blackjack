/* 
 * File:   Player.h
 * Author: Jaired Jawed
 *
 * Created on October 20, 2019, 3:55 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>

#include "Deck.h"
#include "Card.h"

using namespace std;

bool isFloat(string);

class Player {
private:
    // class variables
    ifstream readPlayerFile;
    ofstream writePlayerFile;
    string email;
    string name;
    string password;
    float wager;
    float accountBalance;

public:
    // constructor, destructor, & method prototypes
    Player();
    ~Player();

    vector <Card *> cards;
    int checkHand();
    string getName();
    string getEmail();
    string getPassword();
    float getAccountBalance();
    float getWager();
    vector <Card *> getCards();

    void setName(string);
    void setEmail(string);
    void setPassword(string);
    void addToBalance(float);
    void setWager(float);
    
    void pullCardsFromDeck(Deck *, int);
    void savePlayerToFile(string, string, string, float);
    bool getPlayerFromFile(string, string);
};

Player::Player() {
    email = "";
    readPlayerFile.open("Players.txt");
    writePlayerFile.open("Players.txt", ios::app);
}

Player::~Player() {
    readPlayerFile.close();
    writePlayerFile.close();
}

// writes a new Player to the players file so their records can be saved for later
void Player::savePlayerToFile(string email, string password, string name, float accountBalance) {
    ofstream temp ("temp.txt");
    string line;
    
    if (readPlayerFile.is_open()) {
        while(getline(readPlayerFile, line)) {
            temp << line << endl;
        }

        temp << endl;
        temp << email << endl;
        temp << password << endl;
        temp << name << endl;
        temp << accountBalance << endl;
        temp << endl;
        temp.flush();

        temp.close();
        remove("Players.txt");
        rename("temp.txt", "Players.txt");

        this->email = email;
        this->password = password;
        this->name = name;
        this->accountBalance = accountBalance;
    } else {
        cout << "Failed to open players text file." << endl;
    }
}

bool Player::getPlayerFromFile(string email, string password) {
    // check if the email is valid
    regex emailRegex("^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,}$");
    if (regex_match(email, emailRegex)) {
        cout << "Your email is invalid!" << endl;
        return false;
    }

    if (readPlayerFile.is_open()) {
        string line;

        while (getline(readPlayerFile, line)) {
            if (email == line) {
                // we can skip to the following line and find the password
                // since we store them right below the email
                // we need to set the email now so since we'll be
                // skipping to the next line
                this->email = email;

                getline(readPlayerFile, line);
                string passwordFromTxtFile = line;

                // check if the password is correct
                if (passwordFromTxtFile == password) {
                    // set the user info after validating their password
                    this->password = password;
                    
                    getline(readPlayerFile, line);
                    this->name = line;
                    
                    getline(readPlayerFile, line);
                    this->accountBalance = stof(line);
                    
                    return true;
                } else {
                    // resets the email address if their password wasn't valid
                    cout << "Invalid Password." << endl;
                }
            }
        }
        // if email is not defined, the user doesn't exist
        if (this->email == "") {
            cout << "No user has been found." << endl;
        }
    } else {
        cout << "Unable to open player file!" << endl;
    }

    return false;
}

string Player::getName() {
    return name;
}

void Player::setName(string name) {
    this->name = name;
}

string Player::getEmail() {
    return email;
}

void Player::setEmail(string email) {
    this->email = email;
}

void Player::setPassword(string password) {
    this->password = password;
}

string Player::getPassword() {
    return password;
}

float Player::getAccountBalance() {
    return accountBalance;
}

void Player::setWager(float wager) {
    this->wager = wager;
}

float Player::getWager() {
    return wager;
}

// removes user from file, adds to their balance and rewrites them to the file
void Player::addToBalance(float addedBalance) {
    string line;
  
    ofstream tempFile("temp.txt");

    while(getline(readPlayerFile, line)) {
        if (this->email != line && this->password != line && this->name != line)
        {
            if (isFloat(line) == true) {
                cout << stof(line) << endl;
            } else {
                tempFile << line << endl;
            }
        }
    }

    this->accountBalance += addedBalance;
    
    tempFile << "\n";
    tempFile << this->email << endl;
    tempFile << this->password << endl;
    tempFile << this->name << endl;
    tempFile << this->accountBalance << endl;

    tempFile.close();
    remove("Players.txt");
    rename("temp.txt", "Players.txt");
}

// takes the specified number of cards from the deck
void Player::pullCardsFromDeck(Deck * deck, int numCards)
{
    if (deck->cards.size() < numCards) {
        cout << "The deck doesn't have enough cards!" << endl;
    } else {
        for (int i = 1; i <= numCards; i++) {
            // pull a card from the top of the deck and add it to the players hand
            // remove the card afterwards
            Card* card = deck->cards.top();
            cards.push_back(card);
            deck->cards.pop();
        }
    }
}

// gets the total of the players hand by looping through the vector
int Player::checkHand()
{
    int score = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        score += cards[i]->value;
    }
    return score;
}

bool isFloat(string myString)
{
    istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail(); 
}

#endif /* PLAYER_H */
