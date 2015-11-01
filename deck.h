#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <list>

class Deck
{
public:
    Deck();
    Card popRandomCard();


private:
    std::list<Card> cards;

};

#endif // DECK_H
