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
    QMessageBox::critical(this, "connect to server", "Connect to server successfully");
}








void MainWindow::on_login_bt_clicked()
{

}


void MainWindow::on_regist_bt_clicked()
{

}


void MainWindow::on_cancel_bt_clicked()
{

}

