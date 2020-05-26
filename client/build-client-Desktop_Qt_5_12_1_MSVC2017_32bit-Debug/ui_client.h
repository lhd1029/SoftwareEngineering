/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_client
{
public:
    QWidget *centralWidget;
    QListView *contentListView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *client)
    {
        if (client->objectName().isEmpty())
            client->setObjectName(QString::fromUtf8("client"));
        client->resize(630, 481);
        centralWidget = new QWidget(client);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        contentListView = new QListView(centralWidget);
        contentListView->setObjectName(QString::fromUtf8("contentListView"));
        contentListView->setGeometry(QRect(130, 80, 341, 301));
        client->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(client);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 630, 26));
        client->setMenuBar(menuBar);
        mainToolBar = new QToolBar(client);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        client->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(client);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        client->setStatusBar(statusBar);

        retranslateUi(client);

        QMetaObject::connectSlotsByName(client);
    } // setupUi

    void retranslateUi(QMainWindow *client)
    {
        client->setWindowTitle(QApplication::translate("client", "client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class client: public Ui_client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
