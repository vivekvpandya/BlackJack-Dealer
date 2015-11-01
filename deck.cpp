#include "deck.h"
#include "card.h"

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

