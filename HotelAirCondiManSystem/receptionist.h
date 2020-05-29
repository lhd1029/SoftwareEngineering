#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

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
    QString roomID;
    //Report report;  // undefined: depends on what kind of report we choose

private slots:
    void check_in();  // check in and find a non-occupied roomID
    void check_out();  // check out and free the roomID
    void show_bill();  // be called by check_out() to show the bill of certain room
    void close_window();  // click and close the window

};

#endif // RECEPTIONIST_H
