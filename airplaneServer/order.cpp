#include "order.h"
#include "ui_order.h"

order::order(QWidget *parent) :
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint),
    ui(new Ui::order)
{
    ui->setupUi(this);
}

order::~order()
{
    delete ui;
}

void order::on_back_clicked()
{
  close();
  ui->listWidget->clear();
}

void order::add(QString q){

}
