#ifndef TABLE_H
#define TABLE_H
#include <QString>
#include <list>
#include "player.h"

class Card;

class Table
{
public:
    Table();
    Table(int capacity_, QString tableName_ , qint64 portNo_);
    int getCapacity() const;
    void setCapacity(int capacity_);
    QString getTableName() const;
    void setTableName(QString  tableName_);
    qint64 getPortNo() const;
    void setPortNo(qint64 portNo_);
    bool isWaitingForPlayer() const;
    void setWaitingForPlayer(bool wait);
    void addPlayerToTable(Player player);
    std::list< Player >::iterator playerListBegin();
    std::list< Player >::iterator playerListEnd();
    void addCardtoPlayeratIndex(Card card, int index);
    int numberofConnectedPlayer() const;
    std::list<Player> * getPlayerList();
private:
    int capacity;
    QString tableName;
    qint64 portNo;
    std::list< Player >connectedPalyer;
    bool waitForPalyer;

};

QDataStream & operator <<( QDataStream & stream, Table &table);
QDataStream & operator >>(QDataStream & stream, Table & table);

#endif // TABLE_H
