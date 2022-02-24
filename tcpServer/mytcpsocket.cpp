#include "mytcpsocket.h"
#include<QDebug>
#include "protocol.h"
#include "opedb.h"


MyTcpSocket::MyTcpSocket()
{
    connect(this, SIGNAL(readyRead()), this, SLOT(recvMsg()));
}

void MyTcpSocket::recvMsg()
{
    uint uiPDULen = 0;
    this->read((char*)&uiPDULen, sizeof(uint));
    PDU* pdu = mkPDU(uiPDULen - sizeof(PDU));
    this->read((char*)pdu + sizeof(uint), uiPDULen - sizeof(uint));
    //this->read((char*)pdu, uiPDULen);
    qDebug() << "Msg type:" << pdu->uiMsgType;

    switch (pdu->uiMsgType) {
        case ENUM_MSG_TYPE_REGIST_REQUEST:{
            qDebug() << "Msg type = " << pdu->uiMsgType;
            char name[32] = "";
            char pwd[32] = "";
            strncpy(name, pdu->caData, 32);
            strncpy(pwd, pdu->caData + 32, 32);
            qDebug() << "name = " << name << "\npwd = " << pwd;

            //store user info into database
            bool ret = OpeDB::getInstance().handleRegist(name, pwd);

           PDU* respdu = mkPDU(0);
            if(ret){
                strcpy(respdu->caData, REGIST_OK);
            }
            else {
                strcpy(respdu->caData, REGIST_FAILED);
            }

            respdu->uiMsgType = ENUM_MSG_TYPE_REGIST_RESPOND;
            this->write((char*)respdu, respdu->uiPDULen);

            free(respdu);
            respdu = NULL;

            break;
        }


    default:
                break;
    }


    free(pdu);
    pdu = NULL;
}
