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
        qDebug()<<"got here in pending datagram";

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
           else if(mtype == MessageType::Hit)
           {
               std::vector<QString> cmd = message.getDataStrings();
               Card card = deck.popRandomCard(); // this will waste a card in case player is fold
               int foldStatus = table.addCardtoPlayerWithName(card,cmd[0]);
               // foldStatus = 0 => more cards can be added
               // foldStatus = 1 => autofold no more cards can be added
               // foldStatus = 2 => already fold card is wasted! Card can be added back to deck
               qDebug() << foldStatus << "foldStatus";
               Message messageNew = Message(MessageType::Card);
               QByteArray datagram;
               QDataStream out(&datagram, QIODevice::WriteOnly);
               out.setVersion(QDataStream::Qt_5_5);
              // messageNew.insertDataString(cmd[0]);  // Needs to be check
               if(foldStatus == 2){
                   messageNew.insertDataString("2");
               }
               else if(foldStatus == 1){
                   messageNew.insertDataString("1");
                   messageNew.insertCard(card);
               }
               else if (foldStatus == 0)
               {
                   messageNew.insertDataString("0");
                   messageNew.insertCard(card);
               }
               out << messageNew;
               udpSocket->writeDatagram(datagram, groupAddress, table.getPortNo());
               udpSocket->waitForBytesWritten(30000);
               qDebug() << "sending player details";

           }
           else if(mtype == MessageType::Fold)
           {
               std::vector<QString> cmd = message.getDataStrings();
               table.foldPlayerWithName(cmd[0]);
           }

    }
}

void TableController::sendPlayerDetails()
{
    addInitialCards();
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
    Card card1;
    for(int i=0; i<table.numberofConnectedPlayer(); i++)
    {   qDebug() << "in for " << i;
        card = deck.popRandomCard();
        card1= deck.popRandomCard();
        table.addCardtoPlayeratIndex(card, i);
        table.addCardtoPlayeratIndex(card1,i);
    }
}
