#ifndef MANAGERCONTROLLER_H
#define MANAGERCONTROLLER_H
#include "report.h"
#include "QDate"


class ManagerController
{
public:
    ManagerController();
    void createReport(QDate start, QDate end);
    void downLoad();
    Report report;
};

#endif // MANAGERCONTROLLER_H
