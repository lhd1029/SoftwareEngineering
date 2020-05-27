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
};

#endif // RECEPTIONIST_H
