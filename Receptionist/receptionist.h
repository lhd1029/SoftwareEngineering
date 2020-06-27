#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include <QMainWindow>
#include <QMap>
#include "receptionistcontroller.h"

namespace Ui {
class Receptionist;
}

class Receptionist : public QMainWindow
{
    Q_OBJECT

public:
    explicit Receptionist(QWidget *parent = nullptr);
    ~Receptionist();

    ReceptionistController *rc;

private:
    Ui::Receptionist *ui;
    QMap<int, int> occupied_rooms;
    int workState;  // 0 for check in, 1 for check out

    void initUI();  // init UI and workState
    void initMap();

private slots:
    void req_check_in();  // request check in msg
    void req_check_out();  // request check out msg

    void show_check_in(int roomID);  // show check in msg
    void show_check_out(int roomID);  // show check out msg

    void request_bill();  // request bill when sig(clicked)
    void request_list();  // request list when sig

    void show_bill();  // show the bill
    void show_list();  // show the list

    void checkin_state();  // check in state and ui
    void checkout_state();  // check out state and ui



};

#endif // RECEPTIONIST_H
