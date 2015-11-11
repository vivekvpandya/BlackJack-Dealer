#ifndef CARD_H
#define CARD_H


#include <QObject>

enum Rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
           JACK, QUEEN, KING};
enum Suit {SPADES, HEARTS, DIAMONDS, CLUBS};
//             1    2       3       4

QDataStream & operator <<( QDataStream & stream, const Rank &rank);
QDataStream & operator >>(QDataStream & stream, Rank & rank);

QDataStream & operator <<( QDataStream & stream, const Suit &suit);
QDataStream & operator >>(QDataStream & stream, Suit & suit);

using namespace std;
class Card
{

public:
    explicit Card();
    //overloading << operator so can send Card object to standard output
    friend ostream& operator<<(ostream& os, const Card& aCard);
    Card(Rank r, Suit s, bool ifu);
    //returns the value of a card, 1 - 11
    int getValue() const;
    //flips a card; if face up, becomes face down and vice versa
    void flip();
    string convert();
    Rank getRank() const;
    void setRank(const Rank &rank_ );
    Suit getSuit() const;
    void setSuit(const Suit &suit_);
    bool getFaceUp();
    void setFaceUp(bool faceUp_);


signals:

public slots:

private:
    Rank rank;
    Suit suit;
    bool isFaceUp;
};
QDataStream & operator <<( QDataStream & stream,  Card &card);
QDataStream & operator >>(QDataStream & stream, Card & card);

#endif // CARD_H
