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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_welcome_2;
    QLabel *label_customer_name_3;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_RoomID_tag_2;
    QLabel *label_roomID;
    QSpacerItem *horizontalSpacer_6;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_payment_tag_2;
    QLabel *label_payment_2;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *pushButton_temperature_up_2;
    QPushButton *pushButton_temperature_down_2;
    QPushButton *pushButton_switch_2;
    QPushButton *pushButton_speed_up_2;
    QPushButton *pushButton_speed_down_2;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_current_temperature_2;
    QLCDNumber *lcdNumber_current_temperature_2;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label__target_temperature_2;
    QLCDNumber *lcdNumber_target_temperature_2;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_current_speed_tag_2;
    QLabel *label_current_speed_2;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_target_speed_tag_2;
    QLabel *label_target_speed_2;
    QSpacerItem *horizontalSpacer_8;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_ACState_tag_3;
    QLabel *label_ACstate_3;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(555, 343);
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(40, 30, 501, 42));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_welcome_2 = new QLabel(layoutWidget_2);
        label_welcome_2->setObjectName(QString::fromUtf8("label_welcome_2"));

        horizontalLayout_12->addWidget(label_welcome_2);

        label_customer_name_3 = new QLabel(layoutWidget_2);
        label_customer_name_3->setObjectName(QString::fromUtf8("label_customer_name_3"));

        horizontalLayout_12->addWidget(label_customer_name_3);


        verticalLayout_3->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_RoomID_tag_2 = new QLabel(layoutWidget_2);
        label_RoomID_tag_2->setObjectName(QString::fromUtf8("label_RoomID_tag_2"));

        horizontalLayout_13->addWidget(label_RoomID_tag_2);

        label_roomID = new QLabel(layoutWidget_2);
        label_roomID->setObjectName(QString::fromUtf8("label_roomID"));
        label_roomID->setMinimumSize(QSize(50, 0));

        horizontalLayout_13->addWidget(label_roomID);


        verticalLayout_3->addLayout(horizontalLayout_13);


        horizontalLayout_11->addLayout(verticalLayout_3);

        horizontalSpacer_6 = new QSpacerItem(420, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 210, 151, 21));
        horizontalLayout_14 = new QHBoxLayout(layoutWidget);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_payment_tag_2 = new QLabel(layoutWidget);
        label_payment_tag_2->setObjectName(QString::fromUtf8("label_payment_tag_2"));

        horizontalLayout_14->addWidget(label_payment_tag_2);

        label_payment_2 = new QLabel(layoutWidget);
        label_payment_2->setObjectName(QString::fromUtf8("label_payment_2"));

        horizontalLayout_14->addWidget(label_payment_2);

        layoutWidget_3 = new QWidget(centralwidget);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(80, 280, 418, 25));
        horizontalLayout_15 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        pushButton_temperature_up_2 = new QPushButton(layoutWidget_3);
        pushButton_temperature_up_2->setObjectName(QString::fromUtf8("pushButton_temperature_up_2"));

        horizontalLayout_15->addWidget(pushButton_temperature_up_2);

        pushButton_temperature_down_2 = new QPushButton(layoutWidget_3);
        pushButton_temperature_down_2->setObjectName(QString::fromUtf8("pushButton_temperature_down_2"));

        horizontalLayout_15->addWidget(pushButton_temperature_down_2);

        pushButton_switch_2 = new QPushButton(layoutWidget_3);
        pushButton_switch_2->setObjectName(QString::fromUtf8("pushButton_switch_2"));

        horizontalLayout_15->addWidget(pushButton_switch_2);

        pushButton_speed_up_2 = new QPushButton(layoutWidget_3);
        pushButton_speed_up_2->setObjectName(QString::fromUtf8("pushButton_speed_up_2"));

        horizontalLayout_15->addWidget(pushButton_speed_up_2);

        pushButton_speed_down_2 = new QPushButton(layoutWidget_3);
        pushButton_speed_down_2->setObjectName(QString::fromUtf8("pushButton_speed_down_2"));

        horizontalLayout_15->addWidget(pushButton_speed_down_2);

        layoutWidget_4 = new QWidget(centralwidget);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(40, 80, 481, 111));
        horizontalLayout_16 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_7);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_current_temperature_2 = new QLabel(layoutWidget_4);
        label_current_temperature_2->setObjectName(QString::fromUtf8("label_current_temperature_2"));

        horizontalLayout_17->addWidget(label_current_temperature_2);

        lcdNumber_current_temperature_2 = new QLCDNumber(layoutWidget_4);
        lcdNumber_current_temperature_2->setObjectName(QString::fromUtf8("lcdNumber_current_temperature_2"));

        horizontalLayout_17->addWidget(lcdNumber_current_temperature_2);


        verticalLayout_4->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label__target_temperature_2 = new QLabel(layoutWidget_4);
        label__target_temperature_2->setObjectName(QString::fromUtf8("label__target_temperature_2"));

        horizontalLayout_18->addWidget(label__target_temperature_2);

        lcdNumber_target_temperature_2 = new QLCDNumber(layoutWidget_4);
        lcdNumber_target_temperature_2->setObjectName(QString::fromUtf8("lcdNumber_target_temperature_2"));

        horizontalLayout_18->addWidget(lcdNumber_target_temperature_2);


        verticalLayout_4->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_current_speed_tag_2 = new QLabel(layoutWidget_4);
        label_current_speed_tag_2->setObjectName(QString::fromUtf8("label_current_speed_tag_2"));

        horizontalLayout_19->addWidget(label_current_speed_tag_2);

        label_current_speed_2 = new QLabel(layoutWidget_4);
        label_current_speed_2->setObjectName(QString::fromUtf8("label_current_speed_2"));

        horizontalLayout_19->addWidget(label_current_speed_2);


        verticalLayout_4->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_target_speed_tag_2 = new QLabel(layoutWidget_4);
        label_target_speed_tag_2->setObjectName(QString::fromUtf8("label_target_speed_tag_2"));

        horizontalLayout_20->addWidget(label_target_speed_tag_2);

        label_target_speed_2 = new QLabel(layoutWidget_4);
        label_target_speed_2->setObjectName(QString::fromUtf8("label_target_speed_2"));

        horizontalLayout_20->addWidget(label_target_speed_2);


        verticalLayout_4->addLayout(horizontalLayout_20);


        horizontalLayout_16->addLayout(verticalLayout_4);

        horizontalSpacer_8 = new QSpacerItem(408, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_8);

        layoutWidget_5 = new QWidget(centralwidget);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(260, 210, 151, 21));
        horizontalLayout_21 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_21->setContentsMargins(0, 0, 0, 0);
        label_ACState_tag_3 = new QLabel(layoutWidget_5);
        label_ACState_tag_3->setObjectName(QString::fromUtf8("label_ACState_tag_3"));

        horizontalLayout_21->addWidget(label_ACState_tag_3);

        label_ACstate_3 = new QLabel(layoutWidget_5);
        label_ACstate_3->setObjectName(QString::fromUtf8("label_ACstate_3"));

        horizontalLayout_21->addWidget(label_ACstate_3);

        Client->setCentralWidget(centralwidget);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "MainWindow", nullptr));
        label_welcome_2->setText(QApplication::translate("Client", "\346\254\242\350\277\216\357\274\232", nullptr));
        label_customer_name_3->setText(QString());
        label_RoomID_tag_2->setText(QApplication::translate("Client", "\346\210\277\351\227\264\345\217\267\357\274\232", nullptr));
        label_roomID->setText(QString());
        label_payment_tag_2->setText(QApplication::translate("Client", "\345\275\223\345\211\215\345\272\224\344\273\230\351\207\221\351\242\235", nullptr));
        label_payment_2->setText(QString());
        pushButton_temperature_up_2->setText(QApplication::translate("Client", "\342\206\221\346\270\251\345\272\246", nullptr));
        pushButton_temperature_down_2->setText(QApplication::translate("Client", "\342\206\223\346\270\251\345\272\246", nullptr));
        pushButton_switch_2->setText(QApplication::translate("Client", "\345\274\200\345\205\263", nullptr));
        pushButton_speed_up_2->setText(QApplication::translate("Client", "\342\206\221\351\243\216\351\200\237", nullptr));
        pushButton_speed_down_2->setText(QApplication::translate("Client", "\342\206\223\351\243\216\351\200\237", nullptr));
        label_current_temperature_2->setText(QApplication::translate("Client", "\345\275\223\345\211\215\346\270\251\345\272\246", nullptr));
        label__target_temperature_2->setText(QApplication::translate("Client", "\350\256\276\345\256\232\346\270\251\345\272\246", nullptr));
        label_current_speed_tag_2->setText(QApplication::translate("Client", "\345\275\223\345\211\215\351\243\216\351\200\237", nullptr));
        label_current_speed_2->setText(QString());
        label_target_speed_tag_2->setText(QApplication::translate("Client", "\350\256\276\345\256\232\351\243\216\351\200\237", nullptr));
        label_target_speed_2->setText(QString());
        label_ACState_tag_3->setText(QApplication::translate("Client", "\345\275\223\345\211\215\347\251\272\350\260\203\347\212\266\346\200\201", nullptr));
        label_ACstate_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
