#include "tablecontroller.h"
#include "table.h"
#include "message.h"
#include "deck.h"
#include "player.h"
#include "card.h"

TableController::TableController(QObject *parent) : QObject(parent)
{

}

TableController::TableController(Table tablePtr, QObject *parent) : QObject(parent)
{   deck = Deck();
    table = tablePtr;
    groupAddress = QHostAddress("239.255.43.21");
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4,table.getPortNo(), QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
    qDebug() << "Table controller is created";
    qDebug() << table.getPortNo() ;
}

void TableController::processPendingDatagrams()
{   Message message;
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        //statusLabel->setText(tr("Received datagram: \"%1\"").arg(datagram.data()));
        qDebug()<<"got here";

        QDataStream in(&datagram, QIODevice::ReadOnly);
           in.setVersion(QDataStream::Qt_5_5);
           in >> message;
           MessageType mtype = message.getMessageType();
           if(mtype == MessageType::Message){
                std::vector<QString> cmd = message.getDataStrings();
                qDebug() << cmd[0];
           }
           else if(mtype == MessageType::GetTableDetails)
           {
               sendPlayerDetails();
           }

    }
}

void TableController::sendPlayerDetails()
{
    std::list<Player> players = table.getPlayerList();
    Message message = Message(MessageType::GameDetails); // A GameDetials Message
    for(Player player : players)
    {
      message.insertPlayer(player);
    }
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << message;
    udpSocket->writeDatagram(datagram, groupAddress, table.getPortNo());
    qDebug() << "sending player details";
}

void TableController::addInitialCards()
{
    Card card;
    for(int i=0; i<table.numberofConnectedPlayer(); i++)
    {
        card = deck.popRandomCard();
        table.addCardtoPlayeratIndex(card, i);
    }
}
