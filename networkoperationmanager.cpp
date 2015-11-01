#include "networkoperationmanager.h"
#include "table.h"
#include "message.h"
#include <QTcpSocket>
#include <QObject>

NetworkOperationManager::NetworkOperationManager()
{
    connectionSocket = new QTcpSocket(this);
    connect(connectionSocket,SIGNAL(readyRead()),this,SLOT(readyRead());
    connect(connectionSocket,SIGNAL(connected()),this,SLOT(connected()));
}

void NetworkOperationManager::connectToHost(const QHostAddress &address, quint16 port)
{
    connectionSocket.connectToHost(address,port);
}

qint64 NetworkOperationManager::multicastDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port)
{
   return multicastSocket.writeDatagram(datagram,host,port);
}

bool NetworkOperationManager::isConnected()
{
    return connectionSocket.isValid();
}

QString NetworkOperationManager::networkConnectionError()
{
    return connectionSocket.errorString();
}

void NetworkOperationManager::getTableList()
{
    if(isConnected()){
        Message message = Message(MessageType::GetTableDetails);
        QByteArray block;
        QDataStream out(&block, QIODevice::ReadWrite);
        out.setVersion(QDataStream::Qt_5_5);
        out << (quint16)0;
        out << message;
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));
        qDebug()<<QString(block);
        socket->write(block);
        socket->flush();
        socket->waitForBytesWritten(3000);
        qDebug()<<"Table Details requested !";
    }
}

void NetworkOperationManager::connected()
{
    qDebug() << "Got Connected!";
}

void NetworkOperationManager::readyRead()
{
    qDebug() << "Reading ... " <<'\n';
    ui->roomList->clear();
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
    if(mtype == MessageType::TableDetails){
        qDebug() << "TableDetails";
        emit tableDetailsAvailable(message.getTableDetails());
    }
}
