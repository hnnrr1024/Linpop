#pragma once
#include <iostream>
#include <cstdlib>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include<sstream>
#include<vector>
#include<mutex>
#include "general.h"
#pragma comment(lib,"ws2_32.lib")
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::mutex;
using std::stringstream;

#define SERVERIP "192.168.1.104"
#define SERVERPORT 5050

#define MYSERVERPORT 5054//端口号

class mysocket
{
private:
	WORD sockVersion;
	WSADATA initData;
	int err;
	SOCKET conSock;
	sockaddr_in hostAddr;
public:
	mysocket();
	int LogIn(string, string, user&);
	int SignUp(string, string);
	int GetUsers(vector<user>&,int);
	int Send(int,int,string, int sign = 0,string idate="",string itime="");

};