/* 
 * File:   main.cpp
 * Author: jairedjawed
 *
 * Created on October 20, 2019, 3:28 PM
 */

#include <iostream>
#include "Deck.h"

using namespace std;

int main() {
    Deck *deck = new Deck;
    deck->setupDeck();
    deck->shuffleDeck();
    return 0;
}
