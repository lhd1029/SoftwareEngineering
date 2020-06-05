#ifndef RECEPTIONIST_CONTROLLER_H
#define RECEPTIONIST_CONTROLLER_H
#include <QString>

class ReceptionistController
{
public:
    ReceptionistController();
    QString check_in();
    void check_out();
    void get_bill();  // undefined return value


};

#endif // RECEPTIONIST_CONTROLLER_H
