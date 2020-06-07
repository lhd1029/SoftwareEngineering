#ifndef RECEPTIONISTCONTROLLER_H
#define RECEPTIONISTCONTROLLER_H
#include <QString>

class ReceptionistController
{
public:
    ReceptionistController();
    QString check_in();
    void check_out();
    void get_bill();  // undefined return value


};

#endif // RECEPTIONISTCONTROLLER_H
