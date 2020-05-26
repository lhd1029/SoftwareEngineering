#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);

}

client::~client()
{
    qDebug()<<"调用了析构函数"<<endl;
    delete ui;
}
