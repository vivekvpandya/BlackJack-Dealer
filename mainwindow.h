#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "table.h"
#include "dealer.h"
#include "networkoperationmanager.h"
#include "tablecontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    int on_createBtn_clicked();
    void newConnection();
    void disconnected();
    void readyRead();
    void onAvailableTablesListItemClicked(QListWidgetItem *listItem);
    //void updateAvalibaleTableList(std::vector<Table> tables);
    void resetTable(QString table);



    void on_availableTablesListWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    int portNum = 10000;
    QHash<QString, Table> tables;
    QTcpServer *server;
    QList<TableController *> tableControllers;


};

#endif // MAINWINDOW_H
