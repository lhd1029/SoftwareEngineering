#ifndef MANAGERCONTROLLER_H
#define MANAGERCONTROLLER_H
#include <QDate>
#include <QObject>
#include "report.h"
#include "tcpmanager.h"
#include "xlsxdocument.h"

class ManagerController : public QObject
{
    Q_OBJECT

public:
    ManagerController();
    void createReport(QDate start, QDate end);
    void downLoad();
    Report *report;

private:
    TcpManager *tcpManager;

signals:
    void sigGetReport();

public slots:
    void slotDealReturn(QByteArray msg);

};

#endif // MANAGERCONTROLLER_H
