#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

class Player
{
public:
    Player();
    Player(QString nick,bool isFold = false);
    void setUnique_num(int num);
    int getUnique_num();
    void addCardToHand(Card card);
    void setFoldTrue();
    void setFold(bool fold_);
    bool isFold();
    std::vector<Card> * getCardHand();
    QString getName() const;
    void setName(const QString name_);
private:
    QString nick_name;
    int unique_num;
    std::vector<Card> hand;
    bool fold;
};

QDataStream & operator <<( QDataStream & stream,  Player &player);
QDataStream & operator >>(QDataStream & stream, Player & player);
#endif // PLAYER_H
