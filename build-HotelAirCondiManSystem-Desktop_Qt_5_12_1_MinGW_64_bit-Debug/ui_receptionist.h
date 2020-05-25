/********************************************************************************
** Form generated from reading UI file 'receptionist.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEPTIONIST_H
#define UI_RECEPTIONIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Receptionist
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QRadioButton *radioButton_checkout;
    QRadioButton *radioButton_checkin;
    QPushButton *pushButton_yes;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_receptionistID_tag;
    QLabel *label_receptionistID;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_roomID_tag;
    QLineEdit *lineEdit_roomID;
    QWidget *widget2;
    QVBoxLayout *verticalLayout;
    QLabel *label_bill_tag;
    QTextBrowser *textBrowser_bill;

    void setupUi(QMainWindow *Receptionist)
    {
        if (Receptionist->objectName().isEmpty())
            Receptionist->setObjectName(QString::fromUtf8("Receptionist"));
        Receptionist->resize(800, 600);
        centralwidget = new QWidget(Receptionist);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(40, 100, 120, 80));
        radioButton_checkout = new QRadioButton(groupBox);
        radioButton_checkout->setObjectName(QString::fromUtf8("radioButton_checkout"));
        radioButton_checkout->setGeometry(QRect(10, 50, 89, 16));
        radioButton_checkin = new QRadioButton(groupBox);
        radioButton_checkin->setObjectName(QString::fromUtf8("radioButton_checkin"));
        radioButton_checkin->setGeometry(QRect(10, 20, 89, 16));
        pushButton_yes = new QPushButton(centralwidget);
        pushButton_yes->setObjectName(QString::fromUtf8("pushButton_yes"));
        pushButton_yes->setGeometry(QRect(90, 440, 75, 23));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 50, 161, 21));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_receptionistID_tag = new QLabel(widget);
        label_receptionistID_tag->setObjectName(QString::fromUtf8("label_receptionistID_tag"));

        horizontalLayout->addWidget(label_receptionistID_tag);

        label_receptionistID = new QLabel(widget);
        label_receptionistID->setObjectName(QString::fromUtf8("label_receptionistID"));

        horizontalLayout->addWidget(label_receptionistID);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(50, 190, 189, 22));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_roomID_tag = new QLabel(widget1);
        label_roomID_tag->setObjectName(QString::fromUtf8("label_roomID_tag"));

        horizontalLayout_2->addWidget(label_roomID_tag);

        lineEdit_roomID = new QLineEdit(widget1);
        lineEdit_roomID->setObjectName(QString::fromUtf8("lineEdit_roomID"));

        horizontalLayout_2->addWidget(lineEdit_roomID);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(50, 220, 331, 211));
        verticalLayout = new QVBoxLayout(widget2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_bill_tag = new QLabel(widget2);
        label_bill_tag->setObjectName(QString::fromUtf8("label_bill_tag"));

        verticalLayout->addWidget(label_bill_tag);

        textBrowser_bill = new QTextBrowser(widget2);
        textBrowser_bill->setObjectName(QString::fromUtf8("textBrowser_bill"));

        verticalLayout->addWidget(textBrowser_bill);

        Receptionist->setCentralWidget(centralwidget);

        retranslateUi(Receptionist);

        QMetaObject::connectSlotsByName(Receptionist);
    } // setupUi

    void retranslateUi(QMainWindow *Receptionist)
    {
        Receptionist->setWindowTitle(QApplication::translate("Receptionist", "MainWindow", nullptr));
        groupBox->setTitle(QApplication::translate("Receptionist", "GroupBox", nullptr));
        radioButton_checkout->setText(QApplication::translate("Receptionist", "\345\212\236\347\220\206\351\200\200\346\210\277", nullptr));
        radioButton_checkin->setText(QApplication::translate("Receptionist", "\345\212\236\347\220\206\345\205\245\344\275\217", nullptr));
        pushButton_yes->setText(QApplication::translate("Receptionist", "\347\241\256\345\256\232", nullptr));
        label_receptionistID_tag->setText(QApplication::translate("Receptionist", "\345\211\215\345\217\260\346\234\215\345\212\241\345\221\230\357\274\232", nullptr));
        label_receptionistID->setText(QString());
        label_roomID_tag->setText(QApplication::translate("Receptionist", "\346\210\277\351\227\264\345\217\267\357\274\232", nullptr));
        label_bill_tag->setText(QApplication::translate("Receptionist", "\350\264\246\345\215\225\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Receptionist: public Ui_Receptionist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEPTIONIST_H
