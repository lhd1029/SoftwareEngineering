#include "receptionist.h"
#include "ui_receptionist.h"
#include <random>
#include <QMessageBox>

Receptionist::Receptionist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Receptionist)
{
    ui->setupUi(this);
    this->roomID = "";  // NULL
    connect(ui->radioButton_checkin, SIGNAL(clicked()), this, SLOT(check_in()));
    connect(ui->radioButton_checkout, SIGNAL(clicked()), this, SLOT(check_out()));
}

Receptionist::~Receptionist()
{
    delete ui;
}

void Receptionist:: check_in()
{
    ui->lineEdit_roomID->clear();
    ui->lineEdit_roomID->setPlaceholderText("Please wait a second.");

    // ask the server for a list of free roomID
    // (randomly) choose one and show it in the box
    // server should change the status of the room to occupied

    ui->lineEdit_roomID->setText(this->roomID);
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    QString str = "Welcome to our hotel, your room ID is" + this->roomID;
    msg.setText(str);
}

void Receptionist:: check_out()
{
    ui->lineEdit_roomID->setPlaceholderText("Please input your room ID:");
    ui->lineEdit_roomID->text();
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    QString str = "Please wait a second, calcualting your bill.";
    msg.setText(str)


    // ask the server for a report

    // decode the report and show it in the box

    this->show_bill();
}

void Receptionist:: show_bill()
{

}

