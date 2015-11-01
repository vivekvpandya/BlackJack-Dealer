#include "player.h"

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
