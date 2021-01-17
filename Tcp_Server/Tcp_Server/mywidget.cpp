#include "mywidget.h"
#include "ui_mywidget.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myWidget)
{
    ui->setupUi(this);
    tcpServer = NULL;
    tcpSocket = NULL;
    isHead = true;
    fileSizerec = 0;
    currentSize = 0;


    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any,8080);
    setWindowTitle("服务器：8080");
    ui->ButtonSFile->setEnabled(false);
    ui->ButtonSendFile->setEnabled(false);
    ui->progressBar->setValue(0);
    //建立链接后会触发newConnection
    connect(tcpServer, &QTcpServer::newConnection,
            [=]()
            {
                ui->progressBar->setValue(0);
                //取出建立好链接的套接字
                tcpSocket = tcpServer->nextPendingConnection();

                //获取对方的ip和端口
                QString ip = tcpSocket->peerAddress().toString();
                qint16 port = tcpSocket->peerPort();
                QString temp = QString("[%1:%2] : success").arg(ip).arg(port);
                ui->ButtonSFile->setEnabled(true);
                ui->textEditRead->setText(temp);
                //接受数据会触发readyRead
                connect(tcpSocket,&QTcpSocket::readyRead,
                        [=]()
                        {
                           //qDebug()<<"fileNamerec"<<endl;
                           receive();
                        }
                        );
             }
            );

    connect(&timer,&QTimer::timeout,
            [=](){
                  //关定时器
                  timer.stop();
                  setData();
             }
                );

}

myWidget::~myWidget()
{
    delete ui;
}


void myWidget::on_ButtonSend_clicked()
{
    if(!tcpSocket) return;
    //获取编辑区内容
    QString str = ui->textEdit_Write->toPlainText();
    tcpSocket->write(str.toUtf8().data());

}


void myWidget::on_ButtonClose_clicked()
{
     if(!tcpSocket) return;
    //主动和客户端断开链接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket=NULL;
}

void myWidget::on_ButtonSFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"opne","../");
    if(filePath.isEmpty()==false){
        //获取文件信息，只读打开
        fileName.clear();
        fileSize = 0;
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();
        sendSize = 0;

        file.setFileName(filePath);

        bool isOk = file.open(QIODevice::ReadOnly);
        if(!isOk) qDebug() <<"只读方式打开失败";

        ui->ButtonSFile->setEnabled(false);
        ui->ButtonSendFile->setEnabled(true);


    }
    else{
        qDebug()<<"文件路径出错";
    }

}

void myWidget::on_ButtonSendFile_clicked()
{
    //发送文件头信息
    QString fileHead = QString("%1###%2").arg(fileName).arg(fileSize);
    qint16 len = tcpSocket->write(fileHead.toUtf8());
    if(len > 0)
    {
        //让文件头与文件内容之间发送间隔相隔10ms
        timer.start(10);
    }
    else{

        qDebug()<<"头部发送失败 ";
        file.close();
        ui->ButtonSFile->setEnabled(true);
        ui->ButtonSendFile->setEnabled(false);

    }
}
void myWidget::setData(){
      qint64 len = 0;
      do{
          char buf[4*1024] = {0};
          len = 0;
          len = file.read(buf,sizeof(buf));

          len = tcpSocket->write(buf,len);

          sendSize += len;
      }while(len>0);

      if(sendSize == fileSize){
          ui->textEditRead->append("文件发送完毕 ");
          file.close();
          //断开客户端
          tcpSocket->disconnectFromHost();
          tcpSocket->close();
      }
}


void myWidget::receive()
{
     //取出接收的内容
    QByteArray content = tcpSocket->readAll();
    if(true == isHead)          //文件头处理
    {
        isHead = false;
        fileNamerec = QString(content).section("###", 0, 0);
        fileSizerec = QString(content).section("###", 1, 1).toInt();
        qDebug()<<"fileNamerec"<<fileNamerec<<endl;
        qDebug()<<"fileSizerec"<<fileSizerec<<endl;
        //重置已接收大小
        currentSize = 0;
        ui->progressBar->setMaximum(fileSizerec/1024);
        ui->progressBar->setMinimum(0);
        ui->progressBar->setValue(0);


        filerec.setFileName(fileNamerec);
        //以只写方式打开文件
        if(!filerec.open(QIODevice::WriteOnly))
        {
            qDebug()<<"以只写方式打开文件失败";
            tcpSocket->disconnectFromHost();
            tcpSocket->close();
            return ;
        }
        QString str = QString("接收的文件: [%1: %2 KB]").arg(fileNamerec).arg(fileSizerec/1024);

    }
    else                        //文件内容处理
    {
        qint64 len = filerec.write(content);
        //每次写入的大小累加
        if(len > 0)
        {
            currentSize += len;
        }
         ui->progressBar->setValue(currentSize/1024);
         QString temp = QString("[%1: %2 M/s]").arg("speed").arg(len/1024);
         ui->textEditRead->setText(temp);

        if(currentSize == fileSizerec)   //文件传输完成的条件
        {
           // tcpSocket->write("file done");
            QMessageBox::information(this, "完成", "文件传输完成");

            //传输完成,关闭文件且关闭连接
            filerec.close();
            tcpSocket->disconnectFromHost();
            tcpSocket->close();
        }
    }
}
