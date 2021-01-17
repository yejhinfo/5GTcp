#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>
#include <QTimer>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

    void sendFile();
    //接收文件
    void receive();

private slots:
    void on_pushButton_clicked();

    void on_ButtonFile_clicked();

    void on_ButtonSend_clicked();

    void on_Buttonclose_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket  *tcpSocket;

    QFile file;     //需要发送的文件对象
    QString fileName;
    int fileSize;
    QTimer timer;   //定时器


    QFile filerec;         //需要接收的文件对象
    QString fileNamerec;
    int fileSizerec;

    int currentSize;    //当前已接收的文件大小

    bool isHead;        //标志位，是否是文件头
};

#endif // CLIENTWIDGET_H
