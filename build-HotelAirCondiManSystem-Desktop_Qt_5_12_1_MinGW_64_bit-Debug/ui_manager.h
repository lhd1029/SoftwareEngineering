/********************************************************************************
** Form generated from reading UI file 'manager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Manager
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_managerID_tag;
    QLabel *label_managerID;
    QPushButton *pushButton_checkreport;
    QTextBrowser *textBrowser;

    void setupUi(QMainWindow *Manager)
    {
        if (Manager->objectName().isEmpty())
            Manager->setObjectName(QString::fromUtf8("Manager"));
        Manager->resize(800, 600);
        centralwidget = new QWidget(Manager);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 22, 258, 251));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_managerID_tag = new QLabel(widget);
        label_managerID_tag->setObjectName(QString::fromUtf8("label_managerID_tag"));

        horizontalLayout->addWidget(label_managerID_tag);

        label_managerID = new QLabel(widget);
        label_managerID->setObjectName(QString::fromUtf8("label_managerID"));

        horizontalLayout->addWidget(label_managerID);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_checkreport = new QPushButton(widget);
        pushButton_checkreport->setObjectName(QString::fromUtf8("pushButton_checkreport"));

        verticalLayout->addWidget(pushButton_checkreport);

        textBrowser = new QTextBrowser(widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        Manager->setCentralWidget(centralwidget);

        retranslateUi(Manager);

        QMetaObject::connectSlotsByName(Manager);
    } // setupUi

    void retranslateUi(QMainWindow *Manager)
    {
        Manager->setWindowTitle(QApplication::translate("Manager", "MainWindow", nullptr));
        label_managerID_tag->setText(QApplication::translate("Manager", "\347\273\217\347\220\206\357\274\232", nullptr));
        label_managerID->setText(QString());
        pushButton_checkreport->setText(QApplication::translate("Manager", "\346\237\245\347\234\213\346\212\245\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Manager: public Ui_Manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGER_H
