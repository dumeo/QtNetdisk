#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef unsigned int uint ;
struct PDU{
    uint uiPDULen; //total legth of protocol data
    uint uiMsgType; //messege type
    char caData[64]; //file name etc
    uint uiMsgLen; //actual messege len
    int caMsg[];   //messege data
};

PDU* mkPDU(uint MsgLen);

#endif // PROTOCOL_H
