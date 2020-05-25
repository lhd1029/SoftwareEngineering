#include "receptionist.h"
#include "ui_receptionist.h"

Receptionist::Receptionist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Receptionist)
{
    ui->setupUi(this);
}

Receptionist::~Receptionist()
{
    delete ui;
}

void Receptionist:: checkIn()
{
    // TODO: decide paras
}

void Receptionist:: checkOut()
{
    // function: check if the client choose to check out and free the slave_machine and change its status
    // TODO: decide paras
}

void Receptionist:: showBill()
{
    // TODO: decide paras
}

