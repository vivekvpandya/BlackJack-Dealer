#ifndef NETWORKOPERATIONMANAGER_H
#define NETWORKOPERATIONMANAGER_H
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include "dealer.h"

class Table;
class NetworkOperationManager : public QObject
{
    Q_OBJECT
public:
    NetworkOperationManager();
    qint64 multicastDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port);
    void connectToHost(const QHostAddress &address, quint16 port); // This is for TCPSocket
    bool isConnected();
    QString networkConnectionError();
    void requestTableList(); // This is asynchronous network call. Networkmanager will emit a signal when data available
signals:
    void tableDetailsAvailable(std::vector<Table> tableDetails);
    void tableDetailsOnSocket(QTcpSocket *socket);


private slots:
    void readyRead();
    void connected();
    void newConnectionServer();
    void disconnectedServerSocket();
    void readyReadServerSocket();
private:
    QUdpSocket *multicastSocket;
    QTcpSocket * connectionSocket;
    QTcpServer *tcpServer;
    Dealer * dealer;
};

#endif // NETWORKOPERATIONMANAGER_H
