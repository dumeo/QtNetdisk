#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef unsigned int uint ;
#define   REGIST_OK "Register successfully!"
#define   REGIST_FAILED "Register failed! User name existed!"
enum ENUM_MSG_TYPE{
    ENUM_MSG_TYPE_MIN = 0,
    ENUM_MSG_TYPE_REGIST_REQUEST = 1,
    ENUM_MSG_TYPE_REGIST_RESPOND = 2,


    ENUM_MSG_TYPE_MAX = 0X00FFFFFF
};


struct PDU{
    uint uiPDULen; //total legth of protocol data
    uint uiMsgType; //messege type
    uint uiMsgLen; //actual messege len
    char caData[64]; //file name etc
    int caMsg[];   //messege data
};

PDU* mkPDU(uint MsgLen);

#endif // PROTOCOL_H
