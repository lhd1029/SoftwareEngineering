#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include "tcpclient.h"
namespace Ui {
class client;
}

class client : public QMainWindow,public TcpClient
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();

private:
    Ui::client *ui;
};

#endif // CLIENT_H
