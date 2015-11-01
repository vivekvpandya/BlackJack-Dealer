#include "table.h"
#include "player.h"
#include "card.h"

Table::Table()
{

}

int Table:: getCapacity()
{
    return capacity;
}

void Table:: setCapacity(int capacity_)
{
    capacity = capacity_;
}

QString Table::getTableName()
{
    return tableName;
}

void Table::setTableName(QString tableName_)
{
    tableName = tableName_;
}

qint64 Table::getPortNo()
{
    return portNo;
}

void Table::setPortNo(qint64 portNo_)
{
    portNo = portNo_;
}

bool Table::isWaitingForPlayer()
{
    return waitForPalyer;
}

void Table::setWaitingForPlayer(bool wait)
{
    waitForPalyer = wait;
}

void Table::addPlayerToTable(Player player)
{
    connectedPalyer.push_back(player);
}

std::list< Player >::iterator Table::playerListBegin()
{
    return connectedPalyer.begin();
}

std::list< Player >::iterator Table::playerListEnd()
{
    return connectedPalyer.end();
}

void Table::addCardtoPlayeratIndex(Card card, int index)
{
    std::list<Player >::iterator playerIt = connectedPalyer.begin();
    std::advance(playerIt, index);
    (*playerIt).addCardToHand(card);
}


