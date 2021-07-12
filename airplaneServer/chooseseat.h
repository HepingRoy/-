#ifndef CHOOSESEAT_H
#define CHOOSESEAT_H

#include <QDialog>
#include <QCloseEvent>
#include<QDebug>
#include<QButtonGroup>
#include<QTcpSocket>



namespace Ui {
class chooseseat;
}

class chooseseat : public QDialog
{
    Q_OBJECT

public:
    explicit chooseseat(QWidget *parent = nullptr);
    ~chooseseat();
    void print(QByteArray q);
    void setsocket(QTcpSocket* s);
    void setseat(int s[]);


private slots:
    void on_back_clicked();

    void on_confirm_clicked();

private:
      Ui::chooseseat *ui;
      QTcpSocket *socket;
      QByteArray info[6];
      QButtonGroup *bgp=new QButtonGroup(this);
      QByteArray transform(QByteArray q);






};

#endif // CHOOSESEAT_H
