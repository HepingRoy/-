#include<qmessagebox.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>


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

    connect(&clients[i],SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(onError(QAbstractSocket::SocketError)));
    }

    clients[0].connectToHost("81.68.107.40",18103);//南航
    clients[1].connectToHost("81.68.107.40",18104);//国航
    clients[2].connectToHost("81.68.107.40",18105);//东航


    connect(ui->listWidget,SIGNAL( itemClicked ( QListWidgetItem*)),this,SLOT(onclicked()));

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::onDisconnected()
{
  // QObject *obj= this->sender();//接受
//   QTcpSocket *socket=qobject_cast<QTcpSocket*>(obj);//转换为socket类型
 //   socket->deleteLater();//删除socket
    qDebug()<<"断开连接";
}

void MainWindow::onConnected(){
    qDebug()<<"连接到服务器";
}

void MainWindow::onError(QAbstractSocket::SocketError socketError)
{
qDebug()<<"error:"<<socketError;
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
            qDebug()<<"连接到航空服务器";



        else if(prefix=="1%"){                 //接受服务器查询反馈
            qDebug()<<"接收到来自服务器的查询反馈";
            QByteArray info[6];    //Starting Terminal date flytime seat_class seat_number
               char* str = data.data();
               int tag=0;

               while(*str != '\0'){
                   if(*str == ' '){
                       tag++;
                   }else{
                       info[tag] = info[tag] + *str;
                   }

                   str++;

                   if(tag==6){
                     ui->listWidget->addItem(info[0]+" "+info[1]+" "+info[2]+" "+info[3]+" "+transform(info[4])+" "+transform(info[5]));
                     qDebug()<<info[0];
                     tag=0;
                     for(int i=0;i<6;i++)
                     info[i]="";
                   }

               }
                   qDebug()<<"跳出循环";

        }

        else if(prefix=="2%"){

               QByteArray info[10];
               char* str = data.data();
               int tag=0;
               int n;

               for(int i=0;i<10;i++) seat[i]=1;

               while(*str != '\0'){
                   if(*str == ' '){
                       n=info[tag].toInt();
                       qDebug()<<n;
                       seat[n-1]=0;
                       tag++;
                   }else{
                       info[tag] = info[tag] + *str;
                   }

                   str++;

               }
               choose.setseat(seat);


         }

        else if(prefix=="3%"){             //订单反馈
           QMessageBox::information(NULL, "提示", data, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
           qDebug()<<"收到订票反馈";

           QFile file("D:/airplaneServer/order.txt");
           file.open(QIODevice::WriteOnly | QIODevice::Append);
           file.write(data+'\n');
           file.close();
        }


        else if(prefix=="4%"){
            refunding.print(data);
        }

        else if(prefix=="5%")
             QMessageBox::information(NULL, "提示",data, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);



}



void MainWindow::onclicked(){
    qDebug()<<"点击生效";
    QByteArray choosearry=ui->listWidget->currentItem()->text().toUtf8();
    qDebug()<<choosearry;
    QByteArray info[6];    //Starting Terminal date flytime seat_class seat_number
    char* str = choosearry.data();
    int tag=0;
    while(*str != '\0'){
        if(*str == ' '){
            tag++;
        }
        else
        {
            info[tag] = info[tag] + *str;

        }
        str++;
    }

    qDebug()<<"点击生效";
   if(info[5]==transform("CZ")){
        clients[0].write("1#"+info[0]+" "+info[1]+" "+info[2]+" "+info[3]+" "+transform(info[4]));
        QString T="1#"+info[0]+" "+info[1]+" "+info[2]+" "+info[3]+" "+info[4];
        qDebug()<<T;
        choose.setsocket(&clients[0]);
     }
   else if(info[5]==transform("CA")){
        clients[1].write("1#"+info[0]+" "+info[1]+" "+info[2]+" "+info[3]+" "+transform(info[4]));
        QString T="1#"+info[0]+" "+info[1]+" "+info[2]+" "+info[3]+" "+info[4];
        qDebug()<<T;
        choose.setsocket(&clients[1]);
     }
   else if(info[5]==transform("MU")){
        clients[2].write("1#"+info[0]+" "+info[1]+" "+info[2]+" "+info[3]+" "+transform(info[4]));
        QString T="1#"+info[0]+" "+info[1]+" "+info[2]+" "+info[3]+" "+info[4];
        qDebug()<<T;
        choose.setsocket(&clients[2]);
     }



     choose.print(choosearry);

     choose.exec();

}


QByteArray MainWindow::transform(QByteArray q){
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


void MainWindow::on_search_clicked()
{
   // choose.exec();
    ui->listWidget->clear();
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

void MainWindow::on_refunding_2_clicked()
{
    refunding.setsocket(clients);
    refunding.exec();
}

void MainWindow::on_connectserver_clicked()
{
    clients[0].connectToHost("81.68.107.40",18103);//南航
    clients[1].connectToHost("81.68.107.40",18104);//国航
    clients[2].connectToHost("81.68.107.40",18105);//东航

}

void MainWindow::on_orderbumber_clicked()
{
    QFile file("D:/airplaneServer/order.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    ordering.exec();
}
