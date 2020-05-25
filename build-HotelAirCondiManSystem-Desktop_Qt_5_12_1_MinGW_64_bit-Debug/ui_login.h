/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QPushButton *pushButton_login;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_role_tag;
    QComboBox *comboBox_role;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_account_tag;
    QLineEdit *lineEdit_account;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QLabel *label_test;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(400, 300);
        pushButton_login = new QPushButton(Login);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(130, 250, 75, 23));
        layoutWidget = new QWidget(Login);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 60, 179, 80));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_role_tag = new QLabel(layoutWidget);
        label_role_tag->setObjectName(QString::fromUtf8("label_role_tag"));

        horizontalLayout->addWidget(label_role_tag);

        comboBox_role = new QComboBox(layoutWidget);
        comboBox_role->addItem(QString());
        comboBox_role->addItem(QString());
        comboBox_role->addItem(QString());
        comboBox_role->setObjectName(QString::fromUtf8("comboBox_role"));

        horizontalLayout->addWidget(comboBox_role);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_account_tag = new QLabel(layoutWidget);
        label_account_tag->setObjectName(QString::fromUtf8("label_account_tag"));

        horizontalLayout_2->addWidget(label_account_tag);

        lineEdit_account = new QLineEdit(layoutWidget);
        lineEdit_account->setObjectName(QString::fromUtf8("lineEdit_account"));

        horizontalLayout_2->addWidget(lineEdit_account);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_password = new QLabel(layoutWidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));

        horizontalLayout_3->addWidget(label_password);

        lineEdit_password = new QLineEdit(layoutWidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));

        horizontalLayout_3->addWidget(lineEdit_password);


        verticalLayout->addLayout(horizontalLayout_3);

        label_test = new QLabel(Login);
        label_test->setObjectName(QString::fromUtf8("label_test"));
        label_test->setGeometry(QRect(60, 180, 54, 12));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Dialog", nullptr));
        pushButton_login->setText(QApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        label_role_tag->setText(QApplication::translate("Login", "\350\247\222\350\211\262", nullptr));
        comboBox_role->setItemText(0, QApplication::translate("Login", "\347\273\217\347\220\206", nullptr));
        comboBox_role->setItemText(1, QApplication::translate("Login", "\345\211\215\345\217\260\346\234\215\345\212\241\345\221\230", nullptr));
        comboBox_role->setItemText(2, QApplication::translate("Login", "\347\256\241\347\220\206\345\221\230", nullptr));

        label_account_tag->setText(QApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_password->setText(QApplication::translate("Login", "\345\257\206\347\240\201  ", nullptr));
        label_test->setText(QApplication::translate("Login", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
