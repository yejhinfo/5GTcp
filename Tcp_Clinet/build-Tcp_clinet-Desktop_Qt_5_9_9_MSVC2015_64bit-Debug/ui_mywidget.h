/********************************************************************************
** Form generated from reading UI file 'mywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIDGET_H
#define UI_MYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEditPort;
    QLabel *label_2;
    QLineEdit *lineEditip;
    QTextEdit *textEditRead;
    QTextEdit *textEditWrite;
    QPushButton *ButtonSend;
    QSpacerItem *horizontalSpacer;
    QPushButton *ButtonClose;
    QPushButton *ButtonConnect;

    void setupUi(QWidget *myWidget)
    {
        if (myWidget->objectName().isEmpty())
            myWidget->setObjectName(QStringLiteral("myWidget"));
        myWidget->resize(800, 600);
        gridLayout = new QGridLayout(myWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(myWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 2, 2);

        lineEditPort = new QLineEdit(myWidget);
        lineEditPort->setObjectName(QStringLiteral("lineEditPort"));

        gridLayout->addWidget(lineEditPort, 1, 1, 1, 2);

        label_2 = new QLabel(myWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 2, 2);

        lineEditip = new QLineEdit(myWidget);
        lineEditip->setObjectName(QStringLiteral("lineEditip"));

        gridLayout->addWidget(lineEditip, 3, 1, 1, 2);

        textEditRead = new QTextEdit(myWidget);
        textEditRead->setObjectName(QStringLiteral("textEditRead"));
        textEditRead->setReadOnly(true);

        gridLayout->addWidget(textEditRead, 4, 0, 1, 4);

        textEditWrite = new QTextEdit(myWidget);
        textEditWrite->setObjectName(QStringLiteral("textEditWrite"));

        gridLayout->addWidget(textEditWrite, 5, 0, 1, 4);

        ButtonSend = new QPushButton(myWidget);
        ButtonSend->setObjectName(QStringLiteral("ButtonSend"));

        gridLayout->addWidget(ButtonSend, 6, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(575, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 6, 2, 1, 1);

        ButtonClose = new QPushButton(myWidget);
        ButtonClose->setObjectName(QStringLiteral("ButtonClose"));

        gridLayout->addWidget(ButtonClose, 6, 3, 1, 1);

        ButtonConnect = new QPushButton(myWidget);
        ButtonConnect->setObjectName(QStringLiteral("ButtonConnect"));

        gridLayout->addWidget(ButtonConnect, 2, 3, 1, 1);


        retranslateUi(myWidget);

        QMetaObject::connectSlotsByName(myWidget);
    } // setupUi

    void retranslateUi(QWidget *myWidget)
    {
        myWidget->setWindowTitle(QApplication::translate("myWidget", "myWidget", Q_NULLPTR));
        label->setText(QApplication::translate("myWidget", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243", Q_NULLPTR));
        lineEditPort->setText(QApplication::translate("myWidget", "27783", Q_NULLPTR));
        label_2->setText(QApplication::translate("myWidget", "\346\234\215\345\212\241\345\231\250ip", Q_NULLPTR));
        lineEditip->setText(QApplication::translate("myWidget", "103.46.128.45", Q_NULLPTR));
        ButtonSend->setText(QApplication::translate("myWidget", "send", Q_NULLPTR));
        ButtonClose->setText(QApplication::translate("myWidget", "close", Q_NULLPTR));
        ButtonConnect->setText(QApplication::translate("myWidget", "connect", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class myWidget: public Ui_myWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDGET_H
