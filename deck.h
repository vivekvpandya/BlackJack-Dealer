#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <list>

class Deck
{
public:
    Deck();
    Card popRandomCard();
    std::list<Card> * getCards() ;
    void insertCardToDeck(Card card);


private:
    std::list<Card> cards;

};

QDataStream & operator <<( QDataStream & stream,  Deck &deck);
QDataStream & operator >>(QDataStream & stream, Deck & deck);
#endif // DECK_H
