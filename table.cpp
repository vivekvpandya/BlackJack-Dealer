#include "table.h"

Table::Table()
{

}
//Table constructor to create a Table
Table::Table( QString tableName1,  QString tableCap1, int portNum){

    tableName = tableName1;
    port = portNum;
    tableCap = tableCap1;

}


QString Table::getTableName() const
{
    return tableName;
}

void Table::setTableName(const QString &tableName1 ){

    tableName = tableName1;
}

int Table::getPort() const
{
    return port;
}

void Table::setPort(int portNum)
{
    port = portNum;
}

QString Table::getTableCap() const
{
    return tableCap;
}

void Table::setTableCap(const QString &tableCap1)
{
    tableCap = tableCap1;
}

QSet<Peer> Table::getJoinedNickNames() const
{
    return joinedNickNames;
}

void Table::setJoinedNickNames(const QSet<Peer> &joinedNickNames1)
{
    joinedNickNames = joinedNickNames1;
}

void  Table::addNickName(const Peer &nickName) {

    joinedNickNames.insert(nickName);

}

void Table::removeNickName(const Peer &nickName){

    joinedNickNames.remove(nickName);
}

bool Table::checkNickNameAvailability(QString nickName){
    for(Peer peer:joinedNickNames){
        if(peer.getNickName().compare(nickName) == 0){
            return false;
        }

    }
    return true;
}

QDataStream & operator << (QDataStream & stream, const Table &table){
    stream << table.getTableName();
    stream << table.getTableCap();
    stream << table.getPort();
    QSet<Peer> joinedNicks = table.getJoinedNickNames();
    int joinedNicksSize = joinedNicks.size();
    stream << joinedNicksSize;
    for(Peer peer: joinedNicks){
        stream << peer;
    }

}
QDataStream & operator >>(QDataStream & stream, Table &table){
    QString tableName;
    QString tableCap;
    int tablePort;
    int joinedNickSize;
    stream >> tableName;
    table.setTableName(tableName);
    stream >> tableCap;
    table.setTableCap(tableCap);
    stream >> tablePort;
    table.setPort(tablePort);

    stream >> joinedNickSize;
    Peer peerObj;
    for(int i=0;i<joinedNickSize;i++){
        stream >> peerObj;
        table.addNickName(peerObj);
    }
}
