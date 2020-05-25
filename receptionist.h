#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include <QMainWindow>

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

private slots:
    void checkIn();  // func: check in
    void checkOut();  // func: check out
    void showBill();  // func: show client's bill in the box
};

#endif // RECEPTIONIST_H
