#include <QMessageBox>
#include "receptionist.h"
#include "ui_receptionist.h"

Receptionist::Receptionist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Receptionist)
{
    ui->setupUi(this);
    rc = new ReceptionistController();

    initUI();
    connect(ui->radioButton_checkin, SIGNAL(clicked()), this, SLOT(checkin_state()));
    connect(ui->radioButton_checkout, SIGNAL(clicked()), this, SLOT(checkout_state()));
    connect(ui->pushButton_Checkin, SIGNAL(clicked()), this, SLOT(req_check_in()));
    connect(ui->pushButton_Checkout, SIGNAL(clicked()), this, SLOT(req_check_out()));
    connect(ui->pushButton_Bill, SIGNAL(clicked()), this, SLOT(request_bill()));
    connect(ui->pushButton_List, SIGNAL(clicked()), this, SLOT(request_list()));

    connect(rc, SIGNAL(sig_get_bill()), this, SLOT(show_bill()));
    connect(rc, SIGNAL(sig_get_list()), this, SLOT(show_list()));
    connect(rc, SIGNAL(sig_get_checkin(int)), this, SLOT(show_check_in(int)));
    connect(rc, SIGNAL(sig_get_checkout(int)), this, SLOT(show_check_out(int)));
}

Receptionist::~Receptionist()
{
    delete ui;
}

void Receptionist:: initUI()
{
    ui->radioButton_checkin->setChecked(true);
    ui->radioButton_checkout->setChecked(false);
    ui->pushButton_Checkout->setVisible(false);
    ui->pushButton_Bill->setVisible(false);
    ui->pushButton_List->setVisible(false);
    ui->lineEdit_roomID->setText(nullptr);
    ui->textEdit->setText(nullptr);
    ui->lineEdit_roomID->setReadOnly(true);
    qDebug() << "Initialize Receptionist UI successfully!\n";
}

void Receptionist:: initMap()
{
    QVector<int> roomIdVec{101,102,103,104,105,106,107,108,109,110,201,202,203,204,205,206,207,208,209,210,301,302,303,304,305,306,307,308,309,310};

    for (auto i = 0; i < roomIdVec.size(); i++)
    {
        occupied_rooms.insert(roomIdVec[i], 0);  // initialize: not occupied
    }

}

void Receptionist:: req_check_in()
{
    ui->lineEdit_roomID->clear();
    ui->lineEdit_roomID->setPlaceholderText("Please wait a second.");

    // ask the server for a list of free roomID
    // choose one and show it in the box
    // server should change the status of the room to occupied

    int roomID = 101;
    this->rc->check_in();

    // below: show after get sig

}

void Receptionist::show_check_in(int roomID)
{
    ui->lineEdit_roomID->setText(QString::number(roomID));
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    QString str = "Welcome to our hotel, your room ID is " + QString::number(roomID);
    msg.setText(str);
    msg.exec();

    // update map
    occupied_rooms.insert(roomID, 1);
}

void Receptionist:: req_check_out()
{
    int roomID;

    roomID = ui->lineEdit_roomID->text().toInt();

    if (occupied_rooms.value(roomID) != 1)
    {
        ui->lineEdit_roomID->clear();
        QMessageBox msg;
        msg.setIcon(QMessageBox::Information);
        QString str = "Wrong roomID!";
        msg.setText(str);
        msg.exec();
    }
    else
    {
        rc->check_out(roomID);
    }


}

void Receptionist::show_check_out(int roomID)
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    QString str = QString::number(roomID) + " You've already check out!";
    msg.setText(str);
    msg.exec();

    // update map
    occupied_rooms.insert(roomID, 0);
}

void Receptionist:: request_bill()
{
    ui->textEdit->clear();
    rc->download_bill(ui->lineEdit_roomID->text().toInt());
}

void Receptionist:: show_bill()
{
    QString title("房间号\t入住时间\t\t离店时间\t\t应付金额\n");
    ui->textEdit->insertPlainText(title);
    QString info = QString::number(rc->bill.roomID) + "\t"
            + rc->bill.checkInTime.toString("yyyy-MM-dd") + "\t"
            + rc->bill.checkOutTime.toString("yyyy-MM-dd") + "\t"
            + QString::number(rc->bill.payment);
    ui->textEdit->insertPlainText(info);
}

void Receptionist:: request_list()
{
    ui->textEdit->clear();
    rc->download_list(ui->lineEdit_roomID->text().toInt());
}

void Receptionist:: show_list()
{
    QString title("房间号\t开始送风时间\t结束送风时间\t送风时长\t风速\t费率\t费用\n");
    ui->textEdit->insertPlainText(title);  // 暂用这个对话框
    List tmpList = rc->list;
    for (size_t i = 0; i < tmpList.fee.size(); i++)
    {
        QString info = QString::number(tmpList.roomID) + "\t"
                + tmpList.startTime[i].toString("yyyy-MM-dd") + "\t"
                + tmpList.endTime[i].toString("yyyy-MM-dd") + "\t"
                + QString::number(tmpList.duration[i]) + "\t"
                + QString::number(tmpList.windSpeed[i]) + "\t"
                + QString::number(tmpList.rate[i]) + "\t"
                + QString::number(tmpList.fee[i]);
        ui->textEdit->insertPlainText(info);
    }
}

void Receptionist::checkin_state()
{
    ui->lineEdit_roomID->setText(nullptr);
    ui->lineEdit_roomID->setReadOnly(true);
    ui->pushButton_Checkin->setVisible(true);
    ui->pushButton_Bill->setVisible(false);
    ui->pushButton_List->setVisible(false);
    ui->pushButton_Checkout->setVisible(false);


}

void Receptionist:: checkout_state()
{
    ui->lineEdit_roomID->setText(nullptr);
    ui->pushButton_Checkin->setVisible(false);
    ui->pushButton_Checkout->setVisible(true);
    ui->pushButton_Bill->setVisible(true);
    ui->pushButton_List->setVisible(true);

    ui->lineEdit_roomID->setReadOnly(false);
    ui->lineEdit_roomID->setPlaceholderText("Please input your room ID:");
}
