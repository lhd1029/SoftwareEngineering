#ifndef ADMIN_H
#define ADMIN_H
#include <admincontroller.h>
#include <QMainWindow>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private:
    Ui::Admin *ui;
    AdminController adminController;
    void initConnect();
    void initACPara();
private slots:
    void checkState();
    void changeAirconState();
    void shutDown();
};

#endif // ADMIN_H
