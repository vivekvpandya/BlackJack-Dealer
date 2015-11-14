#include "table.h"
#include "player.h"
#include "card.h"
#include <QDataStream>
#include <list>
#include <QDebug>
#include "message.h"
#include <QUdpSocket>
#include <QObject>

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

std::list<Player>  Table::getPlayerList()
{
    return connectedPalyer;
}

int Table::addCardtoPlayeratIndex(Card card, int index)
{
    std::list<Player >::iterator playerIt = connectedPalyer.begin();
    std::advance(playerIt, index);
    return  playerIt->addCardToHand(card); // need to manipulate on the pointer it seld
}

QDataStream & operator <<( QDataStream & stream, Table &table)
{
    stream << table.getCapacity();
    stream << table.getPortNo();
    stream << table.getTableName();
    stream << table.isWaitingForPlayer();
    return stream;
}
QDataStream & operator >>(QDataStream & stream, Table & table)
{   int capacity;
    qint64 portNo;
    QString tableName;
    bool isWaitingForPalyer;
    stream >> capacity;
    stream >> portNo;
    stream >> tableName;
    stream >> isWaitingForPalyer;
    table.setCapacity(capacity);
    table.setPortNo(portNo);
    table.setTableName(tableName);
    table.setWaitingForPlayer(isWaitingForPalyer);
    return stream;
}



bool Table::multicastGameInfo()
{
    if(numberofConnectedPlayer() == capacity)
    {

         return true;
    }
    else
    {
        return false;
    }
}

int Table::addCardtoPlayerWithName(Card card, QString name)
{   int returnVal = 0;
   std::list<Player>::iterator i,e;
   i = connectedPalyer.begin();
   e = connectedPalyer.end();

    for(; i != e ; i++)
    {

        if (name.compare(i->getName()) == 0 ){
          returnVal = i->addCardToHand(card);
        }
    }
    return returnVal;
}

void Table::foldPlayerWithName(QString name)
{
    for(Player player : connectedPalyer)
    {
        if(name.compare(player.getName()) == 0)
        {
            player.setFoldTrue();
        }
    }
}
