#include "SocketUtility.h"

#include <iostream>
#include <string>
#include "Server.h"
#include "CharacterCodes.h"

#include "json/json.h"

int sendEx(SOCKET s, const char* buf, int len, int flags)
{
    int sendSize = 0;
    int ret = 0;
    while (sendSize < len)
    {
        if ((ret = send(s, buf + sendSize, len - sendSize, flags)) <= 0)
            return ret;
        sendSize += ret;
    }
    return sendSize;
}

int recvEx(SOCKET s, char* buf, int len, int flags)
{
    int recvSize = 0;
    int ret = 0;
    while (recvSize < len)
    {
        if ((ret = recv(s, buf + recvSize, len - recvSize, flags)) <= 0)
            return ret;
        recvSize += ret;
    }
    return recvSize;
}


//int recvHdr(Client* pClient, PHdr pHdr) {
//    int nRecvSize = recvEx(pClient->clientSocket, (char*)pHdr, sizeof(Hdr), 0);
//    return (nRecvSize == sizeof(Hdr)) ? 1 : -1;
//}
//
//int recvBody(Client* pClient, char* pBuffer, int bufSize) {
//
//    int recvSize = 0;
//
//    while (recvSize < bufSize) {
//        int left = bufSize - recvSize;
//        int tryRecv = left > MAXBUFFERSIZE ? MAXBUFFERSIZE : left;
//        int ret = recvEx(pClient->clientSocket, pBuffer + recvSize, tryRecv, 0);
//        if (ret < 0 || ret != tryRecv)
//            return -1;
//        recvSize += tryRecv;
//    }
//
//    assert(recvSize == bufSize);
//    return recvSize;
//}

int Client::sendMsg(int type, const std::string& msg)
{
    MsgHeader hdr;
    int ret;
    int sended = 0;
    hdr.type = type;
    hdr.size = msg.size()+1; // '\0'

    ret = sendEx(_socket, (char*)&hdr, sizeof(MsgHeader), 0);

    if (ret != sizeof(MsgHeader))
    {
        printf("Send head error!\n");
        return SOCKET_ERROR;
    }

    while (sended < hdr.size)
    {
        int left = hdr.size - sended;
        int trySend = left > MAXBUFFERSIZE ? MAXBUFFERSIZE : left;
        ret = sendEx(_socket, &msg[0] + sended, trySend, 0);
        if (ret != trySend)
        {
            printf("Send body error!\n");
            return SOCKET_ERROR;
        }
        sended += trySend;
    }

    return 0;
}

int Client::recvMsg(int & type, std::string& msg)
{
    MsgHeader hdr;
    int nRecvSize = recvEx(_socket, (char*)&hdr, sizeof(MsgHeader), 0);
    if (nRecvSize != sizeof(MsgHeader))
    {
        if (0 == nRecvSize)
            return 0;
        return SOCKET_ERROR;
    }
    type = hdr.type;

    msg.resize(hdr.size);

    int recvSize = 0;

    while (recvSize < hdr.size) {
        int left = hdr.size - recvSize;
        int tryRecv = left > MAXBUFFERSIZE ? MAXBUFFERSIZE : left;
        int ret = recvEx(_socket, &msg[0] + recvSize, tryRecv, 0);
        if (ret < 0 || ret != tryRecv)
            return -1;
        recvSize += tryRecv;
    }

    return 1;
}

int Client::msg_handler()
{
    while (1)
    {
        std::string msg;
        int type;
        int ret = this->recvMsg(type, msg);

        if (ret < 0)
        {
            cout << "client closed" << endl;
            break;
        }

        switch (type)
        {
        case MSG_MESSAGE:
            this->handle_message(msg);
            break;
        case MSG_LOGIN:
            this->handle_login_message(msg);
            break;
        default:
            break;
        }
    }

    closesocket(_socket);
    _server->removeUser(_usrId); // the client object will be deleted

    return 0;
}

int Client::handle_message(const std::string& msg)
{
    bool res;
    std::string errs;
    Json::Value root;
    Json::CharReaderBuilder readerBuilder;

    const std::unique_ptr<Json::CharReader> jsonReader(readerBuilder.newCharReader());
    res = jsonReader->parse(msg.c_str(), msg.c_str() + msg.length(), &root, &errs);
    if (!res || !errs.empty()) {
        std::cout << "parseJson err. " << errs << std::endl;
        return -1;
    }
    else
    {
        std::string sender = MBytes(root["sender"].asString());
        std::string recvicer = MBytes(root["recvicer"].asString());
        std::string message = MBytes(root["message"].asString());
        std::cout << sender << "->" << recvicer << ":" << message << std::endl;

        // just transfer
        this->_server->sendMsgToUser(recvicer, MSG_MESSAGE, msg);
    }
    return 0;
}

int Client::handle_login_message(const std::string& msg)
{
    bool res;
    std::string errs;
    Json::Value root;
    Json::CharReaderBuilder readerBuilder;

    const std::unique_ptr<Json::CharReader> jsonReader(readerBuilder.newCharReader());
    res = jsonReader->parse(msg.c_str(), msg.c_str() + msg.length(), &root, &errs);
    if (!res || !errs.empty()) {
        std::cout << "parseJson err. " << errs << std::endl;
        return -1;
    }
    else
    {
        std::string sender = root["sender"].asString();
        //std::string recvicer = root["recvicer"].asString();
        //std::string message = root["message"].asString();
        std::cout << sender << " log in" << endl;
    }
    return 0;
}

/*
The server only transfer the message, need not do any parse or decorate
*/