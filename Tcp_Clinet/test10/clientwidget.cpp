#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{ 
    ui->setupUi(this);
    setWindowTitle("客户端 ");

    //初始化
    tcpSocket = new QTcpSocket(this);
    isHead = true;
    fileSizerec = 0;
    currentSize = 0;
    ui->progressBar->setValue(0);
    //未连接时设置为不可用
    ui->ButtonFile->setEnabled(false);
    ui->ButtonSend->setEnabled(false);


    //如果连接成功会触发QTcpSocket::connected()信号
    connect(tcpSocket, &QTcpSocket::connected, [=](){
        //连接时设置“选择文件”为可用
        ui->ButtonFile->setEnabled(true);
        ui->textBrowser->setText(QString("[%1:%2]: 成功与服务器连接，等待服务器传输文件...")
                                 .arg(ui->lineEditIP->text())
                                 .arg(ui->lineEdit_2->text().toInt()));
        //服务器write()会触发客户端QTcpSocket::readyRead()信号
        connect(tcpSocket, &QTcpSocket::readyRead, [=](){
            receive();

        });

    });

    //定时器处理
    connect(&timer, &QTimer::timeout, [=](){

        timer.stop();

        //发送文件
        sendFile();
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButton_clicked()
{
    //连接到服务器
    tcpSocket->connectToHost(QHostAddress(ui->lineEditIP->text()), ui->lineEdit_2->text().toInt());
    isHead = true;
    ui->progressBar->setValue(0);
}


void ClientWidget::receive()
{
    //取出接收的内容
    QByteArray content = tcpSocket->readAll();

    if(true == isHead)          //文件头处理
    {
        isHead = false;
        fileNamerec = QString(content).section("###", 0, 0);
        fileSizerec = QString(content).section("###", 1, 1).toInt();

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
        ui->textBrowser->append(str);

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

        if(currentSize == fileSizerec)   //文件传输完成的条件
        {
            ui->textBrowser->append("文件接收完成");
            tcpSocket->write("file done");
            QMessageBox::information(this, "完成", "文件传输完成");

            //传输完成,关闭文件且关闭连接
            filerec.close();
            tcpSocket->disconnectFromHost();
            tcpSocket->close();
        }
    }
}

void ClientWidget::on_ButtonFile_clicked()
{
    //初始化文件属性
    QString filePath = QFileDialog::getOpenFileName(this, "Open", "../");
    if(!filePath.isEmpty())
    {
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();
        //qDebug()<<fileName<<fileSize;

        file.setFileName(filePath);

        if(file.open(QIODevice::ReadOnly))
        {
            ui->textBrowser->append(QString("FileName:%1 \n\nFileSize:%2 KB").arg(fileName).arg(fileSize/1024));
            //连接时设置“选择文件”为不可用，“发送文件”可用
            ui->ButtonSend->setEnabled(true);
            ui->ButtonFile->setEnabled(false);
        }
        else {
            qDebug()<<"打开文件失败";
        }
    }
    else
    {
        qDebug()<<"文件路径出错";
    }


}

void ClientWidget::on_ButtonSend_clicked()
{
       QString fileHead = QString("%1###%2").arg(fileName).arg(fileSize);
       qint16 len = tcpSocket->write(fileHead.toUtf8());
       if(len > 0)
       {
           //让文件头与文件内容之间发送间隔相隔10ms
           timer.start(10);
       }
       else {
           //发送头部文件失败
           qDebug()<<"发送头部文件失败 ";
           file.close();
       }
}

void ClientWidget::sendFile()
{
    ui->textBrowser->append("正在发送文件...");
    qint64 len = 0;
    do{
        //每次发送4KB
        char buf[4*1024] = {0};
        len = 0;

        len = file.read(buf, sizeof(buf));
        len = tcpSocket->write(buf, len);
    }while (len > 0);

}

void ClientWidget::on_Buttonclose_clicked()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
