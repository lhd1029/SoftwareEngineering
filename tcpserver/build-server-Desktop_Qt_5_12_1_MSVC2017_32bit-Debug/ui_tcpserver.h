/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpServer
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *mainLayout;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QPushButton *createBtn;
    QListWidget *contentListWidget;

    void setupUi(QDialog *TcpServer)
    {
        if (TcpServer->objectName().isEmpty())
            TcpServer->setObjectName(QString::fromUtf8("TcpServer"));
        TcpServer->resize(625, 489);
        gridLayoutWidget = new QWidget(TcpServer);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(60, 40, 531, 401));
        mainLayout = new QGridLayout(gridLayoutWidget);
        mainLayout->setSpacing(6);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        portLabel = new QLabel(gridLayoutWidget);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));

        mainLayout->addWidget(portLabel, 1, 0, 1, 1);

        portLineEdit = new QLineEdit(gridLayoutWidget);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));

        mainLayout->addWidget(portLineEdit, 1, 1, 1, 1);

        createBtn = new QPushButton(gridLayoutWidget);
        createBtn->setObjectName(QString::fromUtf8("createBtn"));

        mainLayout->addWidget(createBtn, 2, 0, 1, 2);

        contentListWidget = new QListWidget(gridLayoutWidget);
        contentListWidget->setObjectName(QString::fromUtf8("contentListWidget"));

        mainLayout->addWidget(contentListWidget, 0, 0, 1, 2);


        retranslateUi(TcpServer);

        QMetaObject::connectSlotsByName(TcpServer);
    } // setupUi

    void retranslateUi(QDialog *TcpServer)
    {
        TcpServer->setWindowTitle(QApplication::translate("TcpServer", "TcpServer", nullptr));
        portLabel->setText(QApplication::translate("TcpServer", "\347\253\257\345\217\243\357\274\232", nullptr));
        portLineEdit->setText(QApplication::translate("TcpServer", "8010", nullptr));
        createBtn->setText(QApplication::translate("TcpServer", "\345\210\233\345\273\272\350\201\212\345\244\251\345\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpServer: public Ui_TcpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
