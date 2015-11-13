#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QByteArray>
#include <QNetworkInterface>
#include <QMessageBox>
#include "message.h"
#include "dealer.h"
#include "table.h"
#include "tablecontroller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new QTcpServer();
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::Any, 15000))
    {   // this message should be added to GUI
         qDebug() << "Server could not start";
    }
    else{
        qDebug() << "Server started!";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Function to create table and to add table to the list of available tables
/* *** This is a slot responsible to handle clicked signal sent by create button.
 * The slot will read details from the text fields and creates a table object and added it to tables collection.
 * */
int MainWindow::on_createBtn_clicked()
{
    QString tableName = ui->tableName->text();
    QString tableCapS = ui->tableCap->text();
    int tableCap = tableCapS.toInt();
    if(tableName.isEmpty() == true){
        QMessageBox box;
        box.setText("Oops! Table Name empty.Please enter valid table Name.");
        box.exec();
        return -1;

    }

    if(tableCapS.toInt() > 5 || tableCapS.toInt() < 1){

        QMessageBox box;
        box.setText("Sorry ! Table capacity must be between 1 to 5.");
        box.exec();
        return -1;

    }
    portNum++;
        if(tables.contains(tableName))
           {
            QMessageBox box;
            box.setText("Sorry! Table Name already occupied.");
            box.exec();
            return -1;
        }
        else{
        Table table = Table(tableCap,tableName,portNum);
        tables.insert(tableName,table);
        ui->availableTablesListWidget->addItem(table.getTableName());

        }



    //MainWindow::tables.insert(table.getTableName(),table);
return 0;

}
//Function to display table description when table is selected from available table list
/* This is a slot responsible to handle click signal sent by availabletablesListWidget from ui.
 * It will print the information for the selected table from the tables collection.
 * */
void MainWindow::onAvailableTablesListItemClicked(QListWidgetItem *listItem){

    ui->infoPanelTextBox->clear();
    Table table = MainWindow::tables.value(listItem->text());
    QString tableName = "Table name: "+table.getTableName()+"\n";
    QString tablePort = "Listening port: "+QString::number(table.getPortNo())+"\n";
    QString tableCap = "Table Capacity: "+QString::number(table.getCapacity())+"\n";
    qDebug() << tableName << "yeay";
    QString tableConnectedNicks = "Connected Nicks: \n";

    for (Player player : table.getPlayerList()) {
       tableConnectedNicks.append(player.getName()+"\n");
    }

    ui->infoPanelTextBox->insertPlainText(tableName+"\n");
    ui->infoPanelTextBox->insertPlainText(tablePort+"\n");
    ui->infoPanelTextBox->insertPlainText(tableCap+"\n");
    ui->infoPanelTextBox->insertPlainText(tableConnectedNicks+"\n");


}

//Function to handle clients connecting to sockets and to send them list of available tables
/* This is a slot responsible to handle newConnection signal sent by QTcpServer reference.
 * It binds readyRead and disconnected signals of connected socket with this class’s slots for readRead and disconnected.
 * */
void MainWindow::newConnection()
{
    // Get socket for pending connection

  /*  Sample s;
    s.message = "Hello classes!";
    s.sender = "Vivek Pandya";
*/
  /* QHostAddress ownIPaddress;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            ownIPaddress = address;
    }

    Peer peer = Peer("Dipu Bhai",ownIPaddress);
    Peer peer1 = Peer("LLVM_Ninja", ownIPaddress);


Message message = Message(MessageType::tableDetails);
message.insertDataString("Hello World");
message.insertDataString("C++ is difficult , but when you are used to it every thing becomes easy.");
message.insertPeerObj(peer);
message.insertPeerObj(peer1);
*/
    while(server->hasPendingConnections()){

        QTcpSocket *socket = server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
       /* QByteArray block;
        QDataStream out(&block, QIODevice::ReadWrite);
        out.setVersion(QDataStream::Qt_5_5);
    //! [4] //! [6]
        out << (quint16)0;
        //out << s;
        //out << peer;
        out << message;
        out.device()->seek(0);

        out << (quint16)(block.size() - sizeof(quint16));
    //! [6] //! [7]
       qDebug()<<QString(block);
       socket->write(block);
       socket->flush();

       socket->waitForBytesWritten(3000);
       qDebug()<<"Here!";
*/
    }


/*
    QTcpSocket *socket = server->nextPendingConnection();
    QString responseString;
    QHash<QString, table>::iterator i;
    for (i = MainWindow::tables.begin(); i != MainWindow::tables.end(); ++i){
       table table = i.value();
    responseString.append(table.gettableName()+":"+QString::number(table.getPort())+":");
    }
    //To convert QString object to Character Pointer for Write Function of Socket.
    QByteArray tempByteArray = responseString.toUtf8();
    const char *tempChar = tempByteArray.data();
    socket->write(tempChar);

    socket->flush();

    socket->waitForBytesWritten(3000);
    */
    //socket->close();

    //Note: The returned QTcpSocket object cannot be used from another thread.
    //If you want to use an incoming connection from another thread,
    //you need to override incomingConnection().
}

/*This slot will be triggered when any connected socket receives any data.
 *  It will modify the server data structures according to message type received.
 * */
void MainWindow::readyRead(){
    qDebug()<<"Ok";
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());

    quint16 blockSize=0;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_5);

    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;
//! [8]

//! [10]
        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize)
        return;
//! [10] //! [11]

   // Sample sample;
   // in >> sample;
   // qDebug() << sample.message+"Message Recieved";
   // qDebug()<<sample.sender+"From Sender ";
   // Peer peer;
    //in >> peer;

    //qDebug() << peer.getNickName();
    //qDebug() << peer.getpeerAddress();
    Message message ;
    in >> message;
    MessageType mtype = message.getMessageType();
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_5_5);
           out << (quint16)0;
           //out << s;
           //out << peer;



    if (mtype == MessageType::GetTableDetails){
        Message response = Message(MessageType::TableDetails);
        qDebug() <<"GetTableDetails";
        // Give all available tables in reply


//        response.insertDataString("Vivek");
//        response.insertDataString("Dipu");

        QHash<QString, Table>::iterator i;
        for (i = MainWindow::tables.begin(); i != MainWindow::tables.end(); ++i){
           Table table = i.value();
           qDebug() << table.getCapacity();
           response.insertTable(table);
        }

//        Card card = Card();
//        card.setRank(Rank::KING);
//        card.setSuit(Suit::CLUBS);
//        card.setFaceUp(false);
//        response.insertCard(card);
//        Card card1 = Card();
//        card1.setRank(Rank::FOUR);
//        card1.setSuit(Suit::HEARTS);
//        card1.setFaceUp(true);
//        response.insertCard(card1);

        out << response;
        out.device()->seek(0);

        out << (quint16)(block.size() - sizeof(quint16));
    //! [6] //! [7]
       qDebug()<< (quint16)(block.size() - sizeof(quint16));
       socket->write(block);
       socket->flush();

       socket->waitForBytesWritten(4000);

    }
    else if(mtype == MessageType::JoinTable){
         qDebug() <<"JoinTable";
         std::vector<QString> cmd = message.getDataStrings();
         Player player = Player(cmd[0],false);
         Table table = tables[cmd[1]];
         QByteArray block;
         Message response;
         QDataStream out(&block, QIODevice::ReadWrite);
         out.setVersion(QDataStream::Qt_5_5);
                out << (quint16)0;
         if(table.getCapacity() != table.numberofConnectedPlayer())
         {
         table.addPlayerToTable(player);
         if(table.getCapacity() == table.numberofConnectedPlayer())
         {
               qDebug() << "Only one time intialization for a table";
                 TableController *controller = new TableController(table);
                 tableControllers.push_back(controller);
         }
         tables[cmd[1]] = table;
         response = Message(MessageType::AddedToTable);
         response.insertDataString(table.getTableName());
         }
         else{
          response = Message(MessageType::TableOverFolw);
          response.insertDataString(table.getTableName());
         }
         out << response;
         out.device()->seek(0);

         out << (quint16)(block.size() - sizeof(quint16));
     //! [6] //! [7]
        qDebug()<< (quint16)(block.size() - sizeof(quint16));
        socket->write(block);
        socket->flush();

        socket->waitForBytesWritten(4000);
    }
    else if(mtype == MessageType::LeaveTable){
         qDebug() <<"LeaveTable";


    }

}

/* This slot will be triggered in response to connected socket’s disconnect signal
 * and it will delete the closed socket.
 * */
void MainWindow::disconnected(){

    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

        socket->deleteLater();

}

//void MainWindow::updateAvalibaleTableList(std::vector<Table> tables)
//{
//    ui->availableTablesListWidget->clear();
//    for(std::vector<Table>::iterator i = tables.begin(), e = tables.end(); i!=e ; i++ )
//    {
//        ui->availableTablesListWidget->addItem(i->getTableName());
//    }
//}

void MainWindow::on_availableTablesListWidget_doubleClicked(const QModelIndex &index)
{
    ui->infoPanelTextBox->clear();
    Table table = MainWindow::tables.value(ui->availableTablesListWidget->currentItem()->text());
    QString tableName = "Table name: "+table.getTableName()+"\n";
    QString tablePort = "Listening port: "+QString::number(table.getPortNo())+"\n";
    QString tableCap = "Table Capacity: "+QString::number(table.getCapacity())+"\n";
    qDebug() << tableName << "yeay";
    QString tableConnectedNicks = "Connected Nicks: \n";

    for (Player player : table.getPlayerList()) {
       tableConnectedNicks.append(player.getName()+"\n");
    }

    ui->infoPanelTextBox->insertPlainText(tableName+"\n");
    ui->infoPanelTextBox->insertPlainText(tablePort+"\n");
    ui->infoPanelTextBox->insertPlainText(tableCap+"\n");
    ui->infoPanelTextBox->insertPlainText(tableConnectedNicks+"\n");
}
