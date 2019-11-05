/* 
 * File:   Card.h
 * Author: jairedjawed
 *
 * Created on October 20, 2019, 3:29 PM
 */

#ifndef CARD_H
#define CARD_H

using namespace std;

class Card {
public:
    string name;
    int value;
    
    void setName(string);
    void setValue(int);
    string getName();
    int getValue();
};

void Card::setName(string name) {
    this->name = name;
}

void Card::setValue(int value) {
    this->value = value;
}

string Card::getName() {
    return name;
}

int Card::getValue() {
    return value;
}

#endif /* CARD_H */
