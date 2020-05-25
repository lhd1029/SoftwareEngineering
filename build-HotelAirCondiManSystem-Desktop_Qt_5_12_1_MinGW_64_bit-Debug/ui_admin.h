/********************************************************************************
** Form generated from reading UI file 'admin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_H
#define UI_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Admin
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_switch_master_mach;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_adminID_tag;
    QLabel *label_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_roomID;
    QLineEdit *lineEdit_roomID;
    QPushButton *pushButton_check_state;
    QTextBrowser *textBrowser;

    void setupUi(QMainWindow *Admin)
    {
        if (Admin->objectName().isEmpty())
            Admin->setObjectName(QString::fromUtf8("Admin"));
        Admin->resize(800, 600);
        centralwidget = new QWidget(Admin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_switch_master_mach = new QPushButton(centralwidget);
        pushButton_switch_master_mach->setObjectName(QString::fromUtf8("pushButton_switch_master_mach"));
        pushButton_switch_master_mach->setGeometry(QRect(310, 20, 75, 23));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 20, 131, 16));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_adminID_tag = new QLabel(widget);
        label_adminID_tag->setObjectName(QString::fromUtf8("label_adminID_tag"));

        horizontalLayout_2->addWidget(label_adminID_tag);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(30, 50, 258, 253));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_roomID = new QLabel(widget1);
        label_roomID->setObjectName(QString::fromUtf8("label_roomID"));

        horizontalLayout->addWidget(label_roomID);

        lineEdit_roomID = new QLineEdit(widget1);
        lineEdit_roomID->setObjectName(QString::fromUtf8("lineEdit_roomID"));

        horizontalLayout->addWidget(lineEdit_roomID);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_check_state = new QPushButton(widget1);
        pushButton_check_state->setObjectName(QString::fromUtf8("pushButton_check_state"));

        verticalLayout->addWidget(pushButton_check_state);


        verticalLayout_2->addLayout(verticalLayout);

        textBrowser = new QTextBrowser(widget1);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);

        Admin->setCentralWidget(centralwidget);

        retranslateUi(Admin);

        QMetaObject::connectSlotsByName(Admin);
    } // setupUi

    void retranslateUi(QMainWindow *Admin)
    {
        Admin->setWindowTitle(QApplication::translate("Admin", "MainWindow", nullptr));
        pushButton_switch_master_mach->setText(QApplication::translate("Admin", "\345\274\200\345\205\263", nullptr));
        label_adminID_tag->setText(QApplication::translate("Admin", "\347\256\241\347\220\206\345\221\230\357\274\232", nullptr));
        label_2->setText(QString());
        label_roomID->setText(QApplication::translate("Admin", "\346\210\277\351\227\264\345\217\267", nullptr));
        pushButton_check_state->setText(QApplication::translate("Admin", "\346\237\245\347\234\213\347\212\266\346\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Admin: public Ui_Admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_H
