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
