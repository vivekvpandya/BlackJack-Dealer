#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include <QObject>
#include "table.h"
#include <QUdpSocket>
#include "deck.h"

class TableController : public QObject
{
    Q_OBJECT

private:
    Table table;
    Deck deck;
    QUdpSocket *udpSocket;
    QHostAddress groupAddress;


public:
    explicit TableController(QObject *parent = 0);
    TableController(Table tablePrt,QObject *parent = 0);
    void sendPlayerDetails();
    void addInitialCards();

signals:

public slots:
    void processPendingDatagrams();
};

#endif // TABLECONTROLLER_H
