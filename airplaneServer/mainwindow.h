#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include<QList>
#include<QListWidget>
#include<chooseseat.h>
#include<refund.h>
#include<order.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:  //建立槽函数
    void onReadyRead();//可读
    void onConnected();//连接
    void onDisconnected();//断开
    void onError(QAbstractSocket::SocketError socketError);

     void onclicked();


    void on_search_clicked();

    void on_refunding_2_clicked();

    void on_connectserver_clicked();

    void on_orderbumber_clicked();

private:
    Ui::MainWindow *ui;
    chooseseat choose;
    refund refunding;
    order ordering;

    QTcpSocket clients[3];
    QByteArray transform(QByteArray q);
    int seat[10];//座位是否可任选数组






#endif // MAINWINDOW_H
};
