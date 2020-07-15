// serverDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<sstream>
#include <cstdlib>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "SqlInterface.h"

#include <mutex>
#include <thread>

#include <map>
#pragma comment(lib,"ws2_32.lib")
using  std::cout;
using  std::endl;
using  std::string;
using  std::stringstream;
#define SERVERIP "192.168.1.104"//IP地址
#define SERVERPORT 5050//端口号

std::mutex rwlock;
std::map<int, string> IPbyID;
std::map<int, short> PORTbyID;
std::vector<user> users;
std::map<int, string>statebyID;

DWORD WINAPI alive(LPVOID lpData)
{
	while (1)
	{
		//cout << statebyID.size()<<endl;
		Sleep(1000);
		rwlock.lock();
		for (auto i : statebyID)
		{
			if (i.second == "1")
			{

				//cout << i.first << " " << i.second << endl;
				int theID = i.first;
				for (auto i =users.begin();i!=users.end();i++)
				{
					if (i->ID == theID)
						i->state = "1",i->IP=IPbyID[theID];
				}
				WORD sockVersion = MAKEWORD(2, 2);
				WSADATA initData;
				int err = WSAStartup(sockVersion, &initData);
				sockaddr_in hostAddr;
				hostAddr.sin_family = AF_INET;
				hostAddr.sin_port = htons(PORTbyID[theID]);
				in_addr addr;
				inet_pton(AF_INET, IPbyID[theID].c_str(), (void*)&addr);
				hostAddr.sin_addr = addr;

				//inet_ntop(AF_INET, &addr, ip, 1024);
				//std::cout << "ip:" << ip << endl;
				SOCKET conSock = socket(AF_INET, SOCK_STREAM, 0);
				if (conSock == INVALID_SOCKET)
				{
					//std::cout << "conSock failed" << endl;
					statebyID[theID] = "0";
					for (auto i = users.begin(); i != users.end(); i++)
					{
						if (i->ID == theID)
							i->state = "0",i->IP="",cout << i->ID << " " << i->username << " " << i->state << endl;
					}
					continue;
				}

				err = connect(conSock, (sockaddr*)&hostAddr, sizeof(sockaddr));
				if (err == INVALID_SOCKET)
				{
					//std::cout << "connect failed!" << endl;
					statebyID[theID] = "0";
					for (auto i = users.begin(); i != users.end(); i++)
					{
						if (i->ID == theID)
							i->state = "0", cout << i->ID << " " << i->username << " " << i->state << endl;
					}
					continue;
				}

				string msg = "0";
				err = send(conSock, msg.c_str(), strlen(msg.c_str()), 0);
				char buf[1024] = { '\0' };
				err = recv(conSock, buf, 1024, 0);
				stringstream recStr;
				recStr << buf;
				recStr >> msg;
				//cout <<IPbyID[theID]<<" "<< msg << endl;
				if (msg == "1")
				{
					continue;
				}
				statebyID[theID] = "0";
				for (auto i : users)
				{
					if (i.ID == theID)
						i.state = "0", cout << i.ID << " " << i.username << " " << i.state << endl;
				}
			}
		}
		rwlock.unlock();
	}
}

int sendmsg(int senderID, int receiverID, string message, int sign, string idate, string itime)
{
	{
		Linpop::sqlInterface con;
		int err = con.sendMessage(senderID, receiverID, message, sign, idate, itime);


		int theID = receiverID;
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA initData;
		err = WSAStartup(sockVersion, &initData);
		sockaddr_in hostAddr;
		hostAddr.sin_family = AF_INET;
		hostAddr.sin_port = htons(PORTbyID[theID]);
		in_addr addr;
		inet_pton(AF_INET, IPbyID[theID].c_str(), (void*)&addr);
		hostAddr.sin_addr = addr;

		//inet_ntop(AF_INET, &addr, ip, 1024);
		//std::cout << "ip:" << ip << endl;
		SOCKET conSock = socket(AF_INET, SOCK_STREAM, 0);
		if (conSock == INVALID_SOCKET)
		{
			return -1;
		}

		err = connect(conSock, (sockaddr*)&hostAddr, sizeof(sockaddr));
		if (err == INVALID_SOCKET)
		{
			//std::cout << "connect failed!" << endl;
			return -1;

		}

		string msg = to_string(senderID) + " " + to_string(receiverID) + " " + idate + " " +
			itime + " " + message;
		err = send(conSock, msg.c_str(), strlen(msg.c_str()), 0);
		char buf[1024] = { '\0' };
		err = recv(conSock, buf, 1024, 0);
		stringstream recStr;
		recStr << buf;
		recStr >> msg;
		//cout <<IPbyID[theID]<<" "<< msg << endl;

		if (err == SOCKET_ERROR)
		{
			cout << "reply failed!" << endl;
			return -1;
		}

		err = shutdown(conSock, 2);
		if (err == SOCKET_ERROR)
		{
			cout << "shutdown failed!" << endl;
			return -1;
		}
		if (msg == "1")
		{
			Linpop::sqlInterface con;
			err = con.sendMessage(senderID,receiverID,message,sign,idate,itime);
			return err;
		}

		else
			return 0;
	}

}
int main()
{
	{
		Linpop::sqlInterface con;
		int res = con.getUsers(users, 0);
	}

	HANDLE hThread = CreateThread(NULL, NULL, alive, NULL, 0, NULL);//创建新线程
	CloseHandle(hThread);

	WORD verision = MAKEWORD(2, 2);
	WSADATA lpData;
	int intEr = WSAStartup(verision, &lpData);//指定winsock版本并初始化
	if (intEr != 0)
	{
		cout << "winsock init failed!" << endl;
		return 0;
	}
	else
		cout << "winsock init success!" << endl;

	//创建侦听socket
	SOCKET listenScok = socket(AF_INET, SOCK_STREAM, 0);
	if (listenScok == INVALID_SOCKET)
	{
		cout << "socket error" << endl;
		return 0;
	}
	else
		cout << "create socket success" << endl;

	sockaddr_in hostAddr;
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_port = htons(SERVERPORT);//转换成网络字节序
	//hostAddr.sin_addr.S_un.S_addr = inet_addr(SERVERIP);//转换成网络字节序
	//cout << "net IP:" << hostAddr.sin_addr.S_un.S_addr << endl;
	/*
	inet_addr()版本太低，被弃用使用inet_pton(协议族，字符串IP地址，void目标in_addr*)
	头文件：WS2tcpip.h
	*/
	in_addr addr;
	inet_pton(AF_INET, SERVERIP, (void*)&addr);
	hostAddr.sin_addr = addr;

	char ip[1024] = { '\0' };
	inet_ntop(AF_INET, &addr, ip, 1024);
	cout << "ip:" << ip << endl;


	//侦听套接字listenSock绑定本机地址信息
	int err = 0;
	err = bind(listenScok, (struct sockaddr*)&hostAddr, sizeof(sockaddr));
	if (err != 0)
	{
		cout << "hostAddr bind failed!" << endl;
		return 0;
	}

	err = listen(listenScok, 3);
	if (err != 0)
	{
		cout << "listen socket listen failed!" << endl;
		return 0;
	}
	cout << "listening..." << endl;

	int no = 1;
	while (true)
	{
		sockaddr_in clientAddr;
		int len = sizeof(struct sockaddr);//必须指定长度，否则会导致accept返回10014错误								  //accept会循环等待客户端连接 
		SOCKET clientSock = accept(listenScok, (struct sockaddr*)&clientAddr, &len);

		if (clientSock == INVALID_SOCKET)
		{
			cout << "accept failed!" << endl;
			cout << WSAGetLastError() << endl;
			system("pause");
			return 0;
		}

		SOCKADDR_IN   cliSockAddr;
		int   iLen = sizeof(cliSockAddr);
		getpeername(clientSock, (struct sockaddr*)&cliSockAddr, &iLen);
		char ip[1024] = { '\0' };
		inet_ntop(AF_INET, &(cliSockAddr.sin_addr), ip, 1024);
		int port = cliSockAddr.sin_port;
		string IP = ip;

		cout << "消息来自" << IP << ":" << port << endl;

		string replyStr;

		char buf[1024] = "\0";
		int buflen = recv(clientSock, buf, 1024, 0);
		if (buflen == SOCKET_ERROR)
		{
			cout << "recv failed!" << endl;
			return 0;
		}
		if (buflen == 0)
			continue;
		stringstream recStr;
		int receiverID;
		string  idate;
		string  itime;
		string username;
		string pwd;
		string nickname;
		string message;
		int sign;
		recStr << buf;
		int userID;
		recStr >> userID;
		//注册
		if (userID == -1)//注册
		{
			recStr >> username;
			recStr >> pwd;
			Linpop::sqlInterface con;
			int err = con.signUp(username, pwd);
			if (err == 0)
				replyStr = "0";
			else
				replyStr = "1";
			cout << "reply data" << no++ << ": " << replyStr << endl;
			err = send(clientSock, replyStr.c_str(), strlen(replyStr.c_str()), 0);
			if (err == SOCKET_ERROR)
			{
				cout << "reply failed!" << endl;
				return 0;
			}
			err = shutdown(clientSock, 2);
			if (err == SOCKET_ERROR)
			{
				cout << "shutdown failed!" << endl;
				return 0;
			}
			continue;

		}
		//登录
		else if (userID == 0)
		{
			recStr >> username;
			recStr >> pwd;
			Linpop::sqlInterface con;
			user me = con.logIn(username, pwd);
			if (me.ID == 0)
				replyStr = "0";
			else
			{
				replyStr = to_string(me.ID) + "\n" + me.username + "\n" + me.nickname + "\n";
				short port;
				recStr >> port;
				rwlock.lock();
				IPbyID[me.ID] = IP;
				PORTbyID[me.ID] = port;
				statebyID[me.ID] = "1";
				rwlock.unlock();
			}
			cout << "reply data" << no++ << ": " << replyStr << endl;
			err = send(clientSock, replyStr.c_str(), strlen(replyStr.c_str()), 0);
			if (err == SOCKET_ERROR)
			{
				cout << "reply failed!" << endl;
				return 0;
			}

			err = shutdown(clientSock, 2);
			if (err == SOCKET_ERROR)
			{
				cout << "shutdown failed!" << endl;
				return 0;
			}
			continue;
		}//登录
		//获取好友列表
		else if (userID == -2)
		{
			int iID;
			recStr >> iID;
			replyStr = "";
			rwlock.lock();
			for (auto i : users) {
				if (i.ID != iID)
				{
					replyStr += to_string(i.ID) + "\n";
					replyStr += i.username + "\n";
					replyStr += i.nickname + "\n";
					replyStr += i.state + "\n";
					replyStr += i.IP + "\n";
				}
			}
			rwlock.unlock();
			replyStr += "0";
			err = send(clientSock, replyStr.c_str(), strlen(replyStr.c_str()), 0);
			if (err == SOCKET_ERROR)
			{
				cout << "reply failed!" << endl;
				return 0;
			}

			err = shutdown(clientSock, 2);
			if (err == SOCKET_ERROR)
			{
				cout << "shutdown failed!" << endl;
				return 0;
			}
			continue;
		}
		else
		{
			string idate;
			string itime;
			recStr >> receiverID;
			recStr >> message;
			recStr >> sign;
			recStr >> idate;
			recStr >> itime;
			replyStr = "";
			rwlock.lock();
			if (statebyID[receiverID] != "1")
				replyStr = "0";

			rwlock.unlock();

			cout << userID << endl << receiverID << endl << message << endl << sign << endl << idate << endl << itime;
			err = sendmsg(userID, receiverID, message, sign, idate, itime);
			cout << "err" << err << endl;
			//cout << "recieve data" << no++ << ": " << buf << endl;
			if (err == 1)
				replyStr = "1";
			//string replyStr = "已收到来自用户" + IP + "的消息。";
		}
			
	}
	err = shutdown(listenScok, 2);
	if (err == SOCKET_ERROR)
	{
		cout << "shutdown failed!" << endl;
		return 0;
	}

	err = closesocket(listenScok);
	if (err == SOCKET_ERROR)
	{
		cout << "closesocket failed!" << endl;
		return 0;
	}

	if (WSACleanup() != 0)
	{
		cout << "WSACleanup failed!" << endl;
		return 0;
	}
	system("pause");
	return 0;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
