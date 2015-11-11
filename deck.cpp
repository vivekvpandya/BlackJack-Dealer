#include "deck.h"
#include "card.h"
#include <QDataStream>
Deck::Deck()
{
    for(int suitID = Suit::SPADES ; suitID <= Suit::CLUBS ; suitID++)
    {
        Suit suit = static_cast<Suit>(suitID);
        for(int rankID = Rank::ACE; rankID <= Rank::KING; rankID++)
        {
            Rank rank = static_cast<Rank>(rankID);
            Card card = Card(rank,suit,true);
            cards.push_back(card);
        }
    }
}

Card Deck::popRandomCard()
{
    unsigned index = arc4random() % cards.size();
    std::list<Card>::iterator it = cards.begin();
    std::advance(it, index);
    Card randomCard = *it;
    cards.erase(it); // remove card from the deck
    return randomCard;
}
 std::list<Card> * Deck::getCards()
 {
     return &cards;
 }

 void Deck::insertCardToDeck(Card card)
 {
     cards.push_back(card);
 }

QDataStream & operator <<( QDataStream & stream, Deck &deck)
{
    std::list<Card> * cards = deck.getCards();
    stream << (int)cards->size();
    std::list<Card>::iterator i,e;
    i = cards->begin();
    e = cards->end();
    for(; i != e; i++)
    {
        stream << *i;
    }
}
QDataStream & operator >>(QDataStream & stream, Deck & deck)
{
    int numberOfCards ;
    stream >> numberOfCards;
    Card card;
    for(int i = 0; i<numberOfCards; i++)
    {   stream >> card;
        deck.insertCardToDeck(card);
    }

}
