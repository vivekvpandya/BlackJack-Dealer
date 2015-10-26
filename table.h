#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QString>
#include <QHostAddress>
#include <QSet>
#include "peer.h"
class Table
{


public:
    Table();

    Table( QString tableName1, QString tableCap1, int  portNum);

    QString getTableName() const;
    void setTableName(const QString &tableName1);

    QString getTableCap() const;
    void setTableCap(const QString &tableCap1);

    int getPort() const;
    void setPort(int portNum);

    QSet<Peer> getJoinedNickNames() const;
    void setJoinedNickNames(const QSet<Peer> &joinedNickNames1);

    void addNickName(const Peer &nickName) ;
    void removeNickName(const Peer &nickName);
    bool checkNickNameAvailability(QString nickName);


private:
    // To hold Table name
    QString tableName;
    // To hold Table Capacity
    QString tableCap;
    // This variable holds multicast group port
    int port;

    // To hold list of nick names connected to this Table
    // Need to change this to QSet
    QSet<Peer> joinedNickNames; // Peer object do not define equals method.

};
QDataStream & operator <<( QDataStream & stream, const Table &Table);
QDataStream & operator >>(QDataStream & stream, Table & Table);
#endif // Table_H
