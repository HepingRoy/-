#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include<QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket clients[3];

private slots:  //建立槽函数
    void onReadyRead();//可读
    void onConnected();//连接
    void onDisconnected();//断开

    void lineeditEnable();

    void on_server_clicked();

    void on_search_clicked();

private:
    Ui::MainWindow *ui;
    typedef struct{
        QByteArray start;//起点
        QByteArray destination;//终点
        QByteArray time;//时间
        QByteArray seatclass;//舱位
        QByteArray airlines;//航空公司
    }flight;
    flight** airlines[3];





#endif // MAINWINDOW_H
};
