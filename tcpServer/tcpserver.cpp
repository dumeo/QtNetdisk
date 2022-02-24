#include "tcpserver.h"
#include "ui_tcpserver.h"
#include "mytcpserver.h"
#include<QFile>
#include<QMessageBox>
#include<QDebug>
#include<QByteArray>
TcpServer::TcpServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    loadConfig();

    MyTcpServer::getInstance().listen(QHostAddress(m_strIP), m_usPort);

}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::loadConfig()
{
    QFile file(":/server.conf");
    if(file.open(QIODevice::ReadOnly)){
        QByteArray data = file.readAll();
        QString strData = data.toStdString().c_str();
        qDebug() << strData;
        file.close();
        QStringList strList = strData.split('\n');
//        for(int i = 0;i < strList.size(); i++){
//            qDebug() << strList[i] << "->";
//        }
        m_strIP = strList.at(0);
        m_usPort = strList.at(1).toUShort();
        qDebug() << m_strIP << ":" << m_usPort;


    }
    else {
        QMessageBox::critical(this, "open config", "Open config file failed");
    }
}

