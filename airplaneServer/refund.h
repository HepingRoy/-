#ifndef REFUND_H
#define REFUND_H

#include <QDialog>
#include<qtcpsocket.h>

namespace Ui {
class refund;
}

class refund : public QDialog
{
    Q_OBJECT

public:
    explicit refund(QWidget *parent = nullptr);
    ~refund();
    void setsocket(QTcpSocket *s);
    void print(QByteArray q);

private slots:
    void on_back_clicked();

    void on_confirm_clicked();

private:
    Ui::refund *ui;
    QTcpSocket* socket;
};

#endif // REFUND_H
