#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>

#include <iostream>  
#include <string.h>  
#include <string>
#include <thread>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <atomic>

using namespace std;

#pragma comment(lib, "ws2_32.lib")          //add ws2_32.lib  

#include "SocketUtility.h"
#include "JsonUtility.h"

#define  DEFAULT_PORT  8000

class Server
{
public:
    Server() :_sockSrv(INVALID_SOCKET), _listening(false) {}

    int init()
    {
        WORD    wVersionRequested;
        WSADATA wsaData;
        int     err, iLen;
        wVersionRequested = MAKEWORD(2, 2);//create 16bit data  
        //(1)Load WinSock  
        err = WSAStartup(wVersionRequested, &wsaData); //load win socket  
        if (err != 0)
        {
            cout << "Load WinSock Failed!";
            return -1;
        }
        //(2)create socket  
        _sockSrv = socket(AF_INET, SOCK_STREAM, 0);
        if (_sockSrv == INVALID_SOCKET) {
            cout << "socket() fail:" << WSAGetLastError() << endl;
            return -2;
        }
        //(3)server IP  
        SOCKADDR_IN addrSrv;
        addrSrv.sin_family = AF_INET;
        addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);//Auto IP, byte sequence change  
        addrSrv.sin_port = htons(DEFAULT_PORT);
        //(4)bind  
        err = bind(_sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
        if (err != 0)
        {
            cout << "bind() fail" << WSAGetLastError() << endl;
            return -3;
        }
        //  
        //(5)listen  
        err = listen(_sockSrv, 5);
        if (err != 0)
        {

            cout << "listen() fail" << WSAGetLastError() << endl;
            return -4;
        }
        cout << "Server waitting...:" << endl;

        return 0;
    }

    // maybe sometimes later if the client have not login, then close.
    int login(SOCKET sockConn)
    {
        std::shared_ptr <Client> c(new Client(sockConn));

        while (1)
        {
            int type;
            string msg;
            int ret = c->recvMsg(type, msg);
            if (ret <= 0)
                break;

            if (type != MSG_LOGIN)
                continue;

            //获取用户信息
            Json::Value root;
            parse(msg, root);
            string usrId = root["user"].asString();
            c->setUserId(usrId);
            c->setServer(this);
            
            root.clear();
            root["sender"] = usrId;
            this->sendMsgToAllUser(MSG_LOGIN, root.toStyledString());
            //发送登录成功
            c->runHandler(); // run the client thread

            // add to client list
            std::unique_lock<std::mutex> lock(_mutex, std::defer_lock);
            lock.lock();
            _clients.insert(std::make_pair(usrId, c));
            lock.unlock();

            break;
        }

        return 0;
    }

    int listen_thread()
    {
        //(6)client ip  
        SOCKADDR_IN addrClt;
        int len = sizeof(SOCKADDR);

        while (_listening)
        {
            //(7)accept  
            SOCKET sockConn = accept(_sockSrv, (SOCKADDR*)&addrClt, &len);
            char infoBuf[1024], hostname[100];
            if (gethostname(hostname, 100) != 0)    //get host name  
                strcpy(hostname, "None");
            sprintf(infoBuf, "Welcome %s connected to %s(%d)!", inet_ntoa(addrClt.sin_addr), hostname, (int)sockConn);
            cout << infoBuf << endl;
            
            // run login logic thread
            std::thread loginTask(&Server::login, this, sockConn);
            loginTask.detach();
        }
        
        return 0;
    }

    int sendMsgToUser(const std::string & user, int type, const std::string & msg)
    {
        std::unique_lock<std::mutex> lock(_mutex, std::defer_lock);
        int ret = -1;
        lock.lock();
        if (_clients.find(user) != _clients.end())
        {
            ret = _clients[user]->sendMsg(MSG_MESSAGE, msg);
        }
        else {
            lock.unlock();
            return ret;
        }
        lock.unlock();
        return ret;
    }

    int sendMsgToAllUser(int type, const std::string& msg)
    {
        std::unique_lock<std::mutex> lock(_mutex);

        for (auto& p : _clients)
            p.second->sendMsg(type, msg);

        return 0;
    }

    void removeUser(std::string& user)
    {
        std::unique_lock<std::mutex> lock(_mutex);

        auto iter = _clients.find(user);
        if (iter != _clients.end())
        {
            iter->second->msg_handler_thread().detach();
            _clients.erase(user);
        }
    }

    int run()
    {
        _listening = true;
        _listenThread = std::thread(&Server::listen_thread, this);
        //_recvThread = std::thread(&Server::receive_thread, this);
        return 0;
    }

private:
    SOCKET _sockSrv;
    std::unordered_map<std::string, std::shared_ptr<Client>> _clients;
    std::thread _listenThread;
    std::thread _recvThread;
    std::mutex _mutex;
    std::atomic<bool> _listening;
};
