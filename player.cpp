#include "player.h"
#include <QDataStream>

Player::Player()
{

}

Player::Player(QString nick, bool isFold)
{
    nick_name = nick;
    fold = isFold;
}

void Player::setFoldTrue()
{
    fold = true;
}

bool Player::isFold()
{
    return fold;
}

void Player::setUnique_num(int num)
{
    unique_num = num;
}

void Player::addCardToHand(Card card)
{
    hand.push_back(card);
}

std::vector<Card> * Player::getCardHand()
{
    return &hand;
}

QString  Player::getName() const
{
    return  nick_name;
}

int Player::getUnique_num()
{
    return unique_num;
}

void Player::setFold(bool fold_)
{
    fold = fold_;
}

void Player::setName(const QString name_)
{
    nick_name = name_;
}

QDataStream & operator <<( QDataStream & stream,  Player &player)
{
    stream << player.getUnique_num();
    stream << player.getName();
    stream << player.isFold();
    std::vector<Card> * hand = player.getCardHand();
    std::vector<Card>::iterator i,e;
    i = hand->begin();
    e = hand->end();
    stream << (int)hand->size();
    for(;i != e; i++)
    {
        stream << *i;
    }
    return stream;
}
QDataStream & operator >>(QDataStream & stream, Player & player){
    int unique_num ;
    stream >> unique_num;
    QString nick_name;
    stream >> nick_name;
    bool fold;
    stream >> fold;
    player.setUnique_num(unique_num);
    player.setName(nick_name);
    player.setFold(fold);
    int handSize;
    stream >> handSize;
    Card card;
    for(int i =0 ; i < handSize ; i++)
    {
     stream >> card;
     player.addCardToHand(card);
    }
    return stream;
}
