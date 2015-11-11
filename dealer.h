#ifndef DEALER_H
#define DEALER_H
#include <QList>
#include <QObject>
#include <QHash>
#include "table.h"
#include <QTcpSocket>

class Dealer : public QObject
{
    Q_OBJECT
public:
    Dealer();
    int createNewTable(int capacity_, QString tableName_);
    QList<Table>::iterator getTablesBegin();
    QList<Table>::iterator getTablesEnd();

signals:
    void tableDetailsChanged(std::vector<Table> tables);


private:
    int portNum = 10000;
    QHash<QString, Table> tables;
private slots:
    void writeTableDetails(QTcpSocket *socket);




};

#endif // DEALER_H
