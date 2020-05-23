#include "login.h"
#include "ui_login.h"
#include "databasestatus.h"
#include <iostream>
using namespace std;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    DatabaseStatus d;
    int ret = d.connect();
    cout << d.check_state("1");
    ui->setupUi(this);
    ui->label_test->setNum(ret);
}

Login::~Login()
{
    delete ui;
}
