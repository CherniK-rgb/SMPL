#ifndef MYSERVER_H
#define MYSERVER_H
#include <QUdpSocket>
#include <QTcpServer>
#include <QDebug>
#include <iostream>
#include <random>
#include <iostream>
class myserver: public QTcpServer
{
    Q_OBJECT
public:
    myserver();
    ~myserver();

    QUdpSocket* socket; // socket
    QString Data; // data that sending to client's
    quint16 port[3];
    quint16 serverPort;
    QHostAddress Clients[3];
    quint8 i=0;
public slots:
    void startServer(); // starting server with encrypt connection
    void sockReady(); // socket ready
    quint16 autoPort(); // autoport
};

#endif // MYSERVER_H

