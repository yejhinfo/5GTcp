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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myWidget
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEditRead;
    QTextEdit *textEdit_Write;
    QProgressBar *progressBar;
    QPushButton *ButtonSFile;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *ButtonSendFile;
    QPushButton *ButtonSend;
    QSpacerItem *horizontalSpacer;
    QPushButton *ButtonClose;

    void setupUi(QWidget *myWidget)
    {
        if (myWidget->objectName().isEmpty())
            myWidget->setObjectName(QStringLiteral("myWidget"));
        myWidget->resize(800, 600);
        gridLayout = new QGridLayout(myWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEditRead = new QTextEdit(myWidget);
        textEditRead->setObjectName(QStringLiteral("textEditRead"));
        textEditRead->setReadOnly(true);

        gridLayout->addWidget(textEditRead, 0, 0, 1, 2);

        textEdit_Write = new QTextEdit(myWidget);
        textEdit_Write->setObjectName(QStringLiteral("textEdit_Write"));

        gridLayout->addWidget(textEdit_Write, 1, 0, 1, 2);

        progressBar = new QProgressBar(myWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 2, 0, 1, 2);

        ButtonSFile = new QPushButton(myWidget);
        ButtonSFile->setObjectName(QStringLiteral("ButtonSFile"));

        gridLayout->addWidget(ButtonSFile, 3, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(563, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 1, 1, 1);

        ButtonSendFile = new QPushButton(myWidget);
        ButtonSendFile->setObjectName(QStringLiteral("ButtonSendFile"));

        gridLayout->addWidget(ButtonSendFile, 3, 2, 1, 1);

        ButtonSend = new QPushButton(myWidget);
        ButtonSend->setObjectName(QStringLiteral("ButtonSend"));

        gridLayout->addWidget(ButtonSend, 4, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(575, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 1, 1, 1);

        ButtonClose = new QPushButton(myWidget);
        ButtonClose->setObjectName(QStringLiteral("ButtonClose"));

        gridLayout->addWidget(ButtonClose, 4, 2, 1, 1);


        retranslateUi(myWidget);

        QMetaObject::connectSlotsByName(myWidget);
    } // setupUi

    void retranslateUi(QWidget *myWidget)
    {
        myWidget->setWindowTitle(QApplication::translate("myWidget", "myWidget", Q_NULLPTR));
        ButtonSFile->setText(QApplication::translate("myWidget", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        ButtonSendFile->setText(QApplication::translate("myWidget", "\345\217\221\351\200\201\346\226\207\344\273\266", Q_NULLPTR));
        ButtonSend->setText(QApplication::translate("myWidget", "send_message", Q_NULLPTR));
        ButtonClose->setText(QApplication::translate("myWidget", "close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class myWidget: public Ui_myWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDGET_H
