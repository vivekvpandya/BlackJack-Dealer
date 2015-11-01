#ifndef CARD_H
#define CARD_H


#include <QObject>

enum Rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
           JACK, QUEEN, KING};
enum Suit {SPADES, HEARTS, DIAMONDS, CLUBS};
//             1    2       3       4
using namespace std;
class Card
{

public:

    explicit Card();

    //overloading << operator so can send Card object to standard output
    friend ostream& operator<<(ostream& os, const Card& aCard);

    Card(Rank r = ACE, Suit s = CLUBS, bool ifu = true);

    //returns the value of a card, 1 - 11
    int getValue() const;

    //flips a card; if face up, becomes face down and vice versa
    void flip();

    string convert();

signals:

public slots:

private:
    Rank rank;
    Suit suit;
    bool isFaceUp;
};

#endif // CARD_H
