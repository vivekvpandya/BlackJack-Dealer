#ifndef NETWORKOPERATIONMANAGER_H
#define NETWORKOPERATIONMANAGER_H
#include <QUdpSocket>
#include <QTcpSocket>

class Table;
class NetworkOperationManager
{
public:
    NetworkOperationManager();
    qint64 multicastDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port);
    void connectToHost(const QHostAddress &address, quint16 port); // This is for TCPSocket
    bool isConnected();
    QString networkConnectionError();
    void requestTableList(); // This is asynchronous network call. Networkmanager will emit a signal when data available
signals:
    void tableDetailsAvailable(std::vector<Table> tableDetails);

private slots:
    void readyRead();
    void connected();
private:
    QUdpSocket multicastSocket;
    QTcpSocket connectionSocket;


};

#endif // NETWORKOPERATIONMANAGER_H
