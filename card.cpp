#include "card.h"
#include <iostream>
#include <sstream>
#include <QDataStream>

using namespace std;
Card::Card()
{ }
    Card::Card(Rank r, Suit s, bool isFace)
    { rank = r;
      suit = s;
      isFaceUp = isFace;
    }

    Rank Card::getRank() const
    {
        return rank;
    }

    void Card::setRank(const Rank &rank_)
    {
        rank = rank_;
    }

    Suit Card::getSuit() const
    {
        return suit;
    }

    void Card::setSuit(const Suit &suit_)
    {
        suit = suit_;
    }

    bool Card::getFaceUp()
    {
        return isFaceUp;
    }

    void Card::setFaceUp(bool faceUp_)
    {
        isFaceUp = faceUp_;
    }

    int Card::getValue() const
    {
        //if a cards is face down, its value is 0
        int value = 0;
        if (isFaceUp)
        {
            if(rank > 10)
                value = 10;
            else
                value = rank;

    }
        return value;
    }

    void Card::flip()
    {
            isFaceUp = !isFaceUp;
    }

    string Card::convert()
    {
        std::ostringstream oss;
        string str;
            const string RANKS[] = {"0", "1", "2", "3", "4", "5", "6", "7",
                "8", "9","10", "11", "12", "13"};
            const string SUITS[] = {"1", "2", "3", "4"};

            if (isFaceUp)
                oss << ":images/" << SUITS[suit] << RANKS[rank] << ".png";
            else
                oss << ":images/" << "back" << ".png";

            str = oss.str();
            return str;
    }

QDataStream & operator <<( QDataStream & stream, const Rank &rank)
{
    return stream << (int)rank;
}
QDataStream & operator >>(QDataStream & stream, Rank & rank)
{
    int rankValue;
    stream >> rankValue;
    rank = Rank(rankValue);
    return stream;
}

QDataStream & operator <<( QDataStream & stream, const Suit &suit)
{
    return stream << (int)suit;
}
QDataStream & operator >>(QDataStream & stream, Suit & suit)
{
    int suitValue;
    stream >> suitValue;
    suit = Suit(suitValue);
    return stream;
}


QDataStream & operator <<( QDataStream & stream, Card &card)
{
    stream << card.getRank();
    stream << card.getSuit();
    stream << card.getFaceUp();
}
QDataStream & operator >>(QDataStream & stream, Card & card)
{
    Rank rank;
    Suit suit;
    bool isFaceUp;
    stream >> rank;
    stream >> suit;
    stream >> isFaceUp;
    card.setFaceUp(isFaceUp);
    card.setRank(rank);
    card.setSuit(suit);
    return stream;
}

