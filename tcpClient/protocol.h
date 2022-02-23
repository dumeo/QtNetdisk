#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef unsigned int uint ;
enum ENUM_MSG_TYPE{
    ENUM_MSG_TYPE_MIN = 0,
    ENUM_MSG_TYPE_REGIST_REQUEST,
    ENUM_MSG_TYPE_REGIST_RESPOND,


    ENUM_MSG_TYPE_MAX = 0X00FFFFFF
};


struct PDU{
    uint uiPDULen; //total legth of protocol data
    uint uiMsgType; //messege type
    char caData[64]; //file name etc
    uint uiMsgLen; //actual messege len
    int caMsg[];   //messege data
};

PDU* mkPDU(uint MsgLen);

#endif // PROTOCOL_H
