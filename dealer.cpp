#include "dealer.h"
#include "table.h"
#include <QList>
#include <QHash>
#include <vector>
#include "message.h"




Dealer::Dealer()
{

}

int Dealer::createNewTable(int capacity_, QString tableName_)
{   portNum++;
    if(tables.contains(tableName_))
        return -1;
    Table table = Table(capacity_,tableName_,portNum);
    tables.insert(tableName_,table);
    std::vector<Table> tableDetails;
    QList<Table> list = tables.values();
    QList<Table>::iterator i;
    for( i = list.begin(); i != list.end(); i++ )
    {
        tableDetails.push_back(*i);
    }
   emit tableDetailsChanged(tableDetails);
    return 0;
}

QList<Table>::iterator Dealer::getTablesBegin()
{
    return tables.values().begin();
}

QList<Table>::iterator Dealer::getTablesEnd()
{
    return tables.values().end();
}


void Dealer::writeTableDetails(QTcpSocket *socket)
{   qDebug() << "writing details";
      Message response = Message(MessageType::TableDetails);
      QByteArray block;
      QDataStream out(&block, QIODevice::ReadWrite);
      out.setVersion(QDataStream::Qt_5_5);
      out << (quint16)0;

    QList<Table> tablesValues = tables.values();
      QList<Table>::iterator i = tablesValues.begin();
       QList<Table>::iterator e = tablesValues.end();
      for (; i != e; ++i){
        qDebug() << ((Table)*i).getTableName() << "Dealer writing";
         response.insertTable(*i);
      }
      out << response;
      out.device()->seek(0);
      out << (quint16)(block.size() - sizeof(quint16));
      qDebug()<<QString(block);
      qDebug() << socket->write(block);
      socket->flush();
      socket->waitForBytesWritten(3000);
}
