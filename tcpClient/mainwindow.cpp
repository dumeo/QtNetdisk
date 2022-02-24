#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QByteArray>
#include<QDebug>
#include<QMessageBox>
#include<iostream>
#include<QHostAddress>
#include "protocol.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //loading config file
    loadConfig();
    connect(&m_tcpSocket, SIGNAL(connected()), this, SLOT(showConnect()));
    connect(&m_tcpSocket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
    connect(&m_tcpSocket, SIGNAL(disconnected()), this, SLOT(offline()));





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadConfig(){
    QFile file(":/client.conf");
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
        qDebug() << m_strIP << ", " << m_usPort;

        //connect to server
        m_tcpSocket.connectToHost(QHostAddress(m_strIP), m_usPort);
    }
    else {
        QMessageBox::critical(this, "open config", "Open config file failed");
    }
}


void MainWindow::showConnect(){
    ui->connectionStatus_lb->setText("Connected");
}

void MainWindow::recvMsg()
{
    uint uiPDULen = 0;
    m_tcpSocket.read((char*)&uiPDULen, sizeof(uint));
    PDU* pdu = mkPDU(uiPDULen - sizeof(PDU));
    m_tcpSocket.read((char*)pdu + sizeof(uint), uiPDULen - sizeof(uint));
    //this->read((char*)pdu, uiPDULen);
    qDebug() <<"client recieved:" << "msg type = " << pdu->uiMsgType;

    switch (pdu->uiMsgType) {
        case ENUM_MSG_TYPE_REGIST_RESPOND:{
            qDebug() << "Msg type = " << pdu->uiMsgType;
            char msg[64] = "";
            strcpy(msg, pdu->caData);
            if(!strcmp(msg, REGIST_FAILED))
                QMessageBox::critical(this, "warning", REGIST_FAILED);
            else
                QMessageBox::critical(this, "warning", REGIST_OK);

            break;
        }


    default:
                break;
    }


    free(pdu);
    pdu = NULL;
}

void MainWindow::offline()
{
    ui->connectionStatus_lb->setText("Disconnected");
}








void MainWindow::on_login_bt_clicked()
{

}


void MainWindow::on_regist_bt_clicked()
{
    QString strName = ui->name_le->text();
    QString strPwd = ui->pwd_le->text();
    if(strName.isEmpty() || strPwd.isEmpty()){
        QMessageBox::critical(this, "Erro", "Please enter unser name or Password");

    }
    else{
        PDU* pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_REGIST_REQUEST;
        strncpy(pdu->caData, strName.toStdString().c_str(), 32);
        strncpy(pdu->caData + 32, strPwd.toStdString().c_str(), 32);
        qDebug() << "client sent:" << pdu->caData;
        m_tcpSocket.write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;

    }
}


void MainWindow::on_cancel_bt_clicked()
{

}

