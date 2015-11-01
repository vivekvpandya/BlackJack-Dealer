#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

class Player
{
public:
    Player();
    Player(QString nick,bool isFold = false);
    void setUnique_num(int num);
    void addCardToHand(Card card);
    void setFoldTrue();
    bool isFold();
    std::vector<Card> * getCardHand();
    QString getName() const;



private:
    QString nick_name;
    int unique_num;
    std::vector<Card> hand;
    bool fold;
};

#endif // PLAYER_H
