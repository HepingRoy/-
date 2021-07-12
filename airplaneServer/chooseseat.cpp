#include "chooseseat.h"
#include "ui_chooseseat.h"



chooseseat::chooseseat(QWidget *parent) :
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint),
    ui(new Ui::chooseseat)
{
    ui->setupUi(this);
    /*
    bgp->addButton(ui->s1);
    bgp->addButton(ui->s2);
    bgp->addButton(ui->s3);
    bgp->addButton(ui->s4);
    bgp->addButton(ui->s5);
    bgp->addButton(ui->s6);
    bgp->addButton(ui->s7);
    bgp->addButton(ui->s8);
    bgp->addButton(ui->s9);
    bgp->addButton(ui->s10);
    */
}

chooseseat::~chooseseat()
{
    delete ui;
}

void chooseseat::on_back_clicked()
{
    for(int i=0;i<6;i++)
    info[i]="";
    this->close();
    ui->textEdit->clear();
}



void chooseseat::print(QByteArray q){

    char* str = q.data();
    int tag=0;

    while(*str != '\0'){
        if(*str == ' '){
            tag++;
            ui->textEdit->insertPlainText(info[tag-1]+'\n');
        }else{
            info[tag] = info[tag] + *str;
        }

          str++;

         // qDebug()<<"print";
       }



}

void chooseseat::on_confirm_clicked()
{

    ui->s1->setDown(false);
    ui->s2->setDown(false);
    ui->s3->setDown(false);
    ui->s4->setDown(false);
    ui->s5->setDown(false);
    ui->s6->setDown(false);
    ui->s7->setDown(false);
    ui->s8->setDown(false);
    ui->s9->setDown(false);
    ui->s10->setDown(false);

   // bgp->checkedButton()->setChecked(false);
    qDebug()<<"请求发送成功";
    int a=0;
    if(ui->s1->isChecked()==1)
        a=1;
    else if(ui->s2->isChecked()==1)
        a=2;
    else if(ui->s3->isChecked()==1)
        a=3;

    else if(ui->s4->isChecked()==1)
        a=4;

    else if(ui->s5->isChecked()==1)
        a=5;

    else if(ui->s6->isChecked()==1)
        a=6;

    else if(ui->s7->isChecked()==1)
        a=7;

    else if(ui->s8->isChecked()==1)
        a=8;

    else if(ui->s9->isChecked()==1)
        a=9;
    else if(ui->s10->isChecked()==1)
        a=10;



     socket->write("2#"+info[0]+" "+info[1]+" "+info[2]+" "+info[3]+" "+transform(info[4])+" "+QByteArray::number(a));
     QString T="2#"+info[0]+" "+info[1]+" "+info[2]+" "+info[3]+" "+info[4]+" "+QByteArray::number(a);
     qDebug()<<T;
     for(int i=0;i<6;i++)  info[i]="";
     qDebug()<<"请求发送成功";
     ui->textEdit->clear();
     this->close();

}

void chooseseat::setsocket(QTcpSocket *s){
    socket=s;
}


QByteArray chooseseat::transform(QByteArray q){
    if(q=="e")
        return "经济舱";
    else if(q=="b")
        return "商务舱";
    else if(q=="f")
        return "头等舱";
    else if(q=="CZ")
        return "中国南方航空";
    else if(q=="CA")
        return "中国航空";
    else if(q=="MU")
        return "东方航空";
    else if(q=="经济舱")
        return "e";
    else if(q=="商务舱")
        return "b";
    else if(q=="头等舱")
        return "f";
    else if(q=="中国南方航空")
        return "CZ";
    else if(q=="中国航空")
        return "CA";
    else if(q=="东方航空")
        return "MU";


    else
        return nullptr;

}

void chooseseat::setseat(int s[]){
    ui->s1->setCheckable(false);
    ui->s2->setCheckable(false);
    ui->s3->setCheckable(false);
    ui->s4->setCheckable(false);
    ui->s5->setCheckable(false);
    ui->s6->setCheckable(false);
    ui->s7->setCheckable(false);
    ui->s8->setCheckable(false);
    ui->s9->setCheckable(false);
    ui->s10->setCheckable(false);

    ui->s1->setCheckable(true);
    ui->s2->setCheckable(true);
    ui->s3->setCheckable(true);
    ui->s4->setCheckable(true);
    ui->s5->setCheckable(true);
    ui->s6->setCheckable(true);
    ui->s7->setCheckable(true);
    ui->s8->setCheckable(true);
    ui->s9->setCheckable(true);
    ui->s10->setCheckable(true);



    if(s[0]==0){
        ui->s1->setCheckable(false);
        qDebug()<<"S1";
    }

    if(s[1]==0){
        ui->s2->setCheckable(false);
        qDebug()<<"S2";
    }

    if(s[2]==0){
        ui->s3->setCheckable(false);
        qDebug()<<"S3";
    }

    if(s[3]==0){
        ui->s4->setCheckable(false);
        qDebug()<<"S4";
    }

    if(s[4]==0){
        ui->s5->setCheckable(false);
        qDebug()<<"S5";
    }

    if(s[5]==0){
        ui->s6->setCheckable(false);
        qDebug()<<"S6";
    }

    if(s[6]==0){
        ui->s7->setCheckable(false);
        qDebug()<<"S7";
    }

    if(s[7]==0){
        ui->s8->setCheckable(false);
        qDebug()<<"S8";
    }

    if(s[8]==0){
        ui->s9->setCheckable(false);
        qDebug()<<"S9";
    }

    if(s[9]==0){
        ui->s10->setCheckable(false);
        qDebug()<<"S10";
    }



}
