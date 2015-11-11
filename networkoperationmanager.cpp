#include "networkoperationmanager.h"
#include "table.h"
#include "message.h"
#include <QTcpServer>
#include <QObject>

NetworkOperationManager::NetworkOperationManager()
{
    connectionSocket =  new QTcpSocket(this);
    connect(connectionSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(connectionSocket,SIGNAL(connected()),this,SLOT(connected()));
    //Creating new TCP connection to communicate to client
    tcpServer = new QTcpServer(this);
    dealer = new Dealer();
    // whenever a user connects, it will emit signal
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnectionServer()));

    if(!tcpServer->listen(QHostAddress::Any, 15000))
    {   // this message should be added to GUI
         qDebug() << "Server could not start";
    }
    else{

        qDebug() << "Server started!";
    }
}

void NetworkOperationManager::connectToHost(const QHostAddress &address, quint16 port)
{
    connectionSocket->connectToHost(address,port);
}

qint64 NetworkOperationManager::multicastDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port)
{
   return multicastSocket->writeDatagram(datagram,host,port);
}

bool NetworkOperationManager::isConnected()
{
    return connectionSocket->isValid();
}

QString NetworkOperationManager::networkConnectionError()
{
    return connectionSocket->errorString();
}



void NetworkOperationManager::connected()
{
    qDebug() << "Got Connected!";
}

void NetworkOperationManager::readyRead()
{
//    qDebug() << "Reading ... " <<'\n';
//    ui->roomList->clear();
//    quint16 blockSize=0;
//    QDataStream in(socket);
//    in.setVersion(QDataStream::Qt_5_5);
//    if (blockSize == 0) {
//        if (socket->bytesAvailable() < (int)sizeof(quint16))
//            return;
//        in >> blockSize;
//    }
//    if (socket->bytesAvailable() < blockSize)
//        return;
//    Message message ;
//    in >> message;
//    MessageType mtype = message.getMessageType();
//    if(mtype == MessageType::TableDetails){
//        qDebug() << "TableDetails";
//        emit tableDetailsAvailable(message.getTableDetails());
//    }
}

void NetworkOperationManager::disconnectedServerSocket()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    socket->deleteLater();
}

void NetworkOperationManager::readyReadServerSocket()
{
    qDebug()<<"Ok";
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    quint16 blockSize=0;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_5);
    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize)
        return;
    Message message ;
    in >> message;
    MessageType mtype = message.getMessageType();



    if (mtype == MessageType::GetTableDetails){

      qDebug() <<"GetTableDetails";
      emit tableDetailsOnSocket(socket);

    }
    else if(mtype == MessageType::JoinTable){
//         qDebug() <<"JoinTable";
//         for(QString tableName: message.getDataStrings()){
//             qDebug() << tableName +"table name received";
//             Table table = MainWindow::tables[tableName];
//            for(Peer peer: message.getPeerVector()){
//             table.addNickName(peer);
//            }
//             tables[tableName] = table;
//         }

    }
    else if(mtype == MessageType::LeaveTable){
//         qDebug() <<"LeaveTable";
//         for(QString tableName: message.getDataStrings()){
//             Table table = MainWindow::tables[tableName];
//            for(Peer peer: message.getPeerVector()){
//             table.removeNickName(peer);
//            }
//             tables[tableName] = table;
//         }

    }
}

void NetworkOperationManager::newConnectionServer()
{
    while(tcpServer->hasPendingConnections())
    {
        QTcpSocket *socket = tcpServer->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()),this, SLOT(readyReadServerSocket()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectedServerSocket()));
    }
}
