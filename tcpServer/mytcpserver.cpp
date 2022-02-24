#include "mytcpserver.h"
#include "opedb.h"
#include<QDebug>

MyTcpServer::MyTcpServer()
{
    OpeDB db;
    db.getInstance().init();
}

MyTcpServer &MyTcpServer::getInstance()
{
    static MyTcpServer instance;
    return instance;
}

void MyTcpServer::incomingConnection(qintptr socketDescription)
{
    qDebug() << "client connected";
    MyTcpSocket* clientSocket = new MyTcpSocket();
    clientSocket->setSocketDescriptor(socketDescription);
    clientSocketList.append(clientSocket);
}
