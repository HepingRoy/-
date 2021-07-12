#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    for(int i=0;i<3;i++){
    connect(&clients[i],SIGNAL(readyRead()),
            this,SLOT(onReadyRead()));

    connect(&clients[i],SIGNAL(connected()),
            this,SLOT(onConnected()));

    connect(&clients[i],SIGNAL(disconnected()),
            this,SLOT(onDisconnected()));
    }

    clients[0].connectToHost("81.68.107.40",18103);//南航

    connect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(lineeditEnable()));

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::onDisconnected()
{
    QObject *obj= this->sender();//接受
    QTcpSocket *socket=qobject_cast<QTcpSocket*>(obj);//转换为socket类型
    socket->deleteLater();//删除socket

    qDebug()<<"断开连接";
}

void MainWindow::onConnected(){
    qDebug()<<"连接到服务器";
}


void MainWindow::onReadyRead(){

    QObject *obj= this->sender();
    QTcpSocket *socket=qobject_cast<QTcpSocket*>(obj);//转换为socket类型

    QByteArray dataFull=socket->readAll();


    qDebug()<<"read:"<<dataFull;


    //判断消息类型
        QString prefix=dataFull.mid(0,2);
        QByteArray data=dataFull.mid(2);


        if(prefix=="0%")                       //连接服务器
            qDebug()<<"连接到中国南方航空服务器";



        else if(prefix=="1%"){                 //接受服务器查询反馈
            qDebug()<<"接收到来自服务器的查询反馈";
            QByteArray info[100];    //Starting Terminal date flytime seat_class seat_number
               char* str = data.data();
               int tag=0;

               while(*str != '\0'){
                   if(*str == ' '){
                       tag++;
                   }else{
                       info[tag] = info[tag] + *str;
                   }
                   if((tag+1)%5==0)
                     ui->listWidget->addItem(info[tag-4]+" "+info[tag-3]+" "+info[tag-2]+" "+info[tag-1]+" "+info[tag]);
                   str++;

               }






        }



}



void MainWindow::lineeditEnable(){
    QByteArray arry=ui->listWidget->currentItem()->text().toUtf8();
    QByteArray info[5];    //Starting Terminal date flytime seat_class seat_number
    char* str = arry.data();
    int tag=0;
    while(*str != '\0')
        if(*str == ' '){
            tag++;
        }
        else{
            info[tag] = info[tag] + *str;
        }
     //if(info[4]=="中国南方航空"){

     //}
}





void MainWindow::on_search_clicked()
{
    QString msgInput="0#"+ui->start->text()+" "+ui->destination->text()+" "+ui->time->text()+" ";
    if(ui->class_2->currentText()=="经济舱")
        msgInput+="e";
    else if(ui->class_2->currentText()=="商务舱")
         msgInput+="b";
    else if(ui->class_2->currentText()=="头等舱")
        msgInput+="f";


    for(int i=0;i<3;i++){
      clients[i].write(msgInput.toUtf8().data());
      qDebug()<<"查找已信息发送";

    }
}
