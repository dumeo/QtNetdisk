#include "mytcpsocket.h"
#include<QDebug>
#include "protocol.h"
MyTcpSocket::MyTcpSocket()
{
    connect(this, SIGNAL(readyRead()), this, SLOT(recvMsg()));
}

void MyTcpSocket::recvMsg()
{
    qDebug() << this->bytesAvailable();
    uint uiPDULen = 0;
    this->read((char*)&uiPDULen, sizeof(uint));
    PDU* pdu = mkPDU(uiPDULen - sizeof(PDU));
    this->read((char*)pdu + sizeof(uint), uiPDULen - sizeof(uint));
    //this->read((char*)pdu, uiPDULen);
    qDebug() << pdu->uiMsgType << ", " << (char*)pdu->caMsg;
    free(pdu);
}
