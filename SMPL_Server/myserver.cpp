#include <myserver.h>
#include <QDataStream>
myserver::myserver(){}
myserver::~myserver(){}
void myserver::startServer() //start server encrypted
{
    serverPort = autoPort(); // move to port value of function autoPort
    if(this->listen(QHostAddress::Any,serverPort)) // if server listening at current ip and port
    {
        qDebug()<<"Listening";
        qDebug()<<"Server's port = " << serverPort;
    }
    else // if server not listening
    {
        qDebug()<<"Not Listening";
    }
    this->setMaxPendingConnections(4); // set limit to connection to host
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any,serverPort);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
}
void myserver :: sockReady() // function if socket is ready
{
    if(socket->hasPendingDatagrams())
    {
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(buffer.data(),buffer.size(),&sender,&senderPort);
        if(buffer == "\n")
        {
            Clients[i] = sender;
            port[i] = senderPort;
            qDebug() << "Client " << i+1 << "connected to server:)" ;
            socket->writeDatagram(buffer,1,Clients[i],port[i]);
            i++;
        }
        else
            if(buffer == "Code:1234")
            {
                qDebug() << "Client disconnected:(";
                for(int k=0;k<i;k++)
                {
                    if(Clients[k]==sender && port[k]==senderPort )
                    {
                        while(k<i)
                        {
                            Clients[k]=Clients[k+1];
                            port[k]=port[k+1];
                            k+=2;
                        }
                        i--;
                        break;
                    }
                }
            }
                else
                for(int k=0;k<i;k++)
                socket->writeDatagram(buffer,Clients[k],port[k]);
    }
}

quint16 myserver::autoPort() // function to autoport in interval 49152-65535
{
    std::random_device rd;
    std::mt19937 e{rd()};
    std::uniform_int_distribution<uint16_t> dist{49152, 65535};
    return(dist(e));
}
