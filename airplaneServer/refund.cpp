#include "refund.h"
#include "ui_refund.h"

refund::refund(QWidget *parent) :
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint),
    ui(new Ui::refund)
{
    ui->setupUi(this);
}

refund::~refund()
{
    delete ui;

}

void refund::setsocket(QTcpSocket *s){

    socket=s;

}


void refund::on_back_clicked()
{
    close();
    ui->textEdit->clear();
    ui->lineEdit->clear();


}

void refund::on_confirm_clicked()
{
    ui->textEdit->clear();
    QByteArray order;
    order=ui->lineEdit->text().toUtf8();
    QByteArray prefix=order.mid(0,2);

    if(prefix=="CZ")
     socket[0].write("3#"+order);
    else if(prefix=="CA")
        socket[1].write("3#"+order);
    else if(prefix=="MU")
        socket[2].write("3#"+order);
    else
       print("订单号格式错误");
}

void refund::print(QByteArray q){
    ui->textEdit->insertPlainText(q);
}
