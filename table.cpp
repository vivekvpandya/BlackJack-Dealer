#include "table.h"
#include "player.h"
#include "card.h"
#include <QDataStream>
#include <list>
#include <QDebug>
Table::Table()
{

}
Table::Table(int capacity_, QString tableName_, qint64 portNo_)
{
    capacity = capacity_;
    tableName = tableName_;
    portNo = portNo_;
    waitForPalyer = true;

}

int Table:: getCapacity() const
{
    return capacity;
}

void Table:: setCapacity(int capacity_)
{
    capacity = capacity_;
}

QString Table::getTableName() const
{
    return tableName;
}

void Table::setTableName(QString tableName_)
{
    tableName = tableName_;
}

qint64 Table::getPortNo() const
{
    return portNo;
}

void Table::setPortNo(qint64 portNo_)
{
    portNo = portNo_;
}

bool Table::isWaitingForPlayer() const
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

int Table::numberofConnectedPlayer() const
{
    return connectedPalyer.size();
}

std::list<Player> * Table::getPlayerList()
{
    return &connectedPalyer;
}

void Table::addCardtoPlayeratIndex(Card card, int index)
{
    std::list<Player >::iterator playerIt = connectedPalyer.begin();
    std::advance(playerIt, index);
    (*playerIt).addCardToHand(card);
}

QDataStream & operator <<( QDataStream & stream,  Table &table)
{
    stream << table.getCapacity();
    stream << table.getPortNo();
    stream << table.getTableName();
    qDebug() << "Sendig name "<<table.getTableName();
    stream << table.isWaitingForPlayer();
    stream << table.numberofConnectedPlayer();
    std::list<Player> *connectedPlayer = table.getPlayerList();
    std::list<Player>::iterator i,e ;
    i = connectedPlayer->begin();
    e = connectedPlayer->end();
    for(;i!=e; i++)
    {   qDebug() << "Player sent!";
        stream << *i;
    }
    return stream;
}
QDataStream & operator >>(QDataStream & stream, Table & table)
{
    int capacity_;
    int portNo_;
    QString tableName_;
    bool isWaitingForPlayer_;
    int numberofConnectedPlayer_;
    stream >> capacity_;
    table.setCapacity(capacity_);
    stream >> portNo_;
    table.setPortNo(portNo_);
    stream >> tableName_;
    table.setTableName(tableName_);
    stream >> isWaitingForPlayer_;
    table.setWaitingForPlayer(isWaitingForPlayer_);
    stream >> numberofConnectedPlayer_;
    Player player;
    for(int i=0; i< numberofConnectedPlayer_ ; i++)
    {   qDebug() << "Player";
        stream >> player;
        table.addPlayerToTable(player);
    }
    return stream;
}
