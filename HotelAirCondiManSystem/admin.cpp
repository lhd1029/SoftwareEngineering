#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    ui->defaultdegree->setValue(26);
    ui->feerate->setValue(1);
    initConnect();
}

Admin::~Admin()
{
    delete ui;
}

void Admin::initConnect()
{
    connect(ui->pushButton_check_state, SIGNAL(clicked()), this, SLOT(checkState()));
    connect(ui->pushButton_changeAircon, SIGNAL(clicked()), this, SLOT(changeAirconState()));
    connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(shutDown()));
}

void Admin::checkState()
{
    
}

void Admin::changeAirconState()
{
    if(ui->checkBox_aricon->isChecked())
    {
        initACPara();
    }
}

void Admin::shutDown()
{

}

void Admin::initACPara()
{
    int warmCool;
    if(ui->degreepattern->currentIndex()==1) warmCool = 1;
    else warmCool = 0;
    adminController.setParam(warmCool, ui->defaultdegree->value(), ui->feerate->value());
}
