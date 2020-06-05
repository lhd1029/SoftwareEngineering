#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include <receptionist_controller.h>
#include <QMainWindow>
#include <report.h>

namespace Ui {
class Receptionist;
}

class Receptionist : public QMainWindow
{
    Q_OBJECT

public:
    explicit Receptionist(QWidget *parent = nullptr);
    ~Receptionist();

private:
    Ui::Receptionist *ui;
    int workState;
    ReceptionistController rc;

private slots:
    /*
    void check_in();  // check in and find a non-occupied roomID
    void check_out();  // check out and free the roomID
    void show_bill();  // be called by check_out() to show the bill of certain room
    void close_window();  // click and close the window
    */

    void initUI();  // check the workstate and change the UI
    void check_in_msg();
    void check_out_msg();
    void show_bill();
};

#endif // RECEPTIONIST_H
