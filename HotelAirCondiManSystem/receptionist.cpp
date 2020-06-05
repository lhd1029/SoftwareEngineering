#include "receptionist.h"
#include "ui_receptionist.h"
#include <random>
#include <QMessageBox>

Receptionist::Receptionist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Receptionist)
{
    ui->setupUi(this);
    this->workState = 0;  // init: check in
}

Receptionist::~Receptionist()
{
    delete ui;
}

void Receptionist:: check_in_msg()
{
    ui->lineEdit_roomID->clear();
    ui->lineEdit_roomID->setPlaceholderText("Please wait a second.");

    // ask the server for a list of free roomID
    // (randomly) choose one and show it in the box
    // server should change the status of the room to occupied
    QString roomID = this->rc.check_in();
    ui->lineEdit_roomID->setText(roomID);
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    QString str = "Welcome to our hotel, your room ID is" + roomID;
    msg.setText(str);
}

void Receptionist:: check_out_msg()
{
    ui->lineEdit_roomID->setPlaceholderText("Please input your room ID:");
    ui->lineEdit_roomID->text();
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    QString str = "Please wait a second, calcualting your bill.";
    msg.setText(str);

    // ask the server for a report

    // decode the report and show it in the box

    this->show_bill();
}

void Receptionist:: show_bill()
{
    this->rc.get_bill();
}

