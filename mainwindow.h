#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "table.h"
#include <QListWidgetItem>
#include <QTcpSocket>
#include <QTcpServer>

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
    void onAvailableTablesListItemClicked(QListWidgetItem *listItem);
    void newConnection();
    void disconnected();
    void readyRead();



private:
    Ui::MainWindow *ui;
    int portNum = 10000;
    QHash<QString, Table> tables;
    QTcpServer *server;

};

#endif // MAINWINDOW_H
