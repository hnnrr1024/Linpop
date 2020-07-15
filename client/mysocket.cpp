#include "mysocket.h"
#include <vector>
#include <mutex>


    mysocket::mysocket()
	{
		sockVersion = MAKEWORD(2, 2);
		err = WSAStartup(sockVersion, &initData);
		hostAddr.sin_family = AF_INET;
		hostAddr.sin_port = htons(SERVERPORT);
		//创建一个套接字，参数列表（地址族TCP、UDP；套接字协议类型TCP；套接字使用的特定协议0自动指定)
		SOCKET thissocket = socket(AF_INET, SOCK_STREAM, 0);
		if (thissocket == INVALID_SOCKET)
		{
			std::cout << "create socket failed!" << endl;
		}
		in_addr addr;
		inet_pton(AF_INET, SERVERIP, (void*)&addr);
		hostAddr.sin_addr = addr;
		char ip[1024] = { '\0' };
		inet_ntop(AF_INET, &addr, ip, 1024);
		//std::cout << "ip:" << ip << endl;
	}

	int mysocket::LogIn(string username, string pwd, user& me) {

		conSock = socket(AF_INET, SOCK_STREAM, 0);
		if (conSock == INVALID_SOCKET)
		{
			//std::cout << "conSock failed" << endl;
			return -1;
		}

		err = connect(conSock, (sockaddr*)&hostAddr, sizeof(sockaddr));
		if (err == INVALID_SOCKET)
		{
			//std::cout << "connect failed!" << endl;
			return -1;
		}
		//std::cout << "input data: ";
		string bufstr = "0 " + username + " " + pwd + " "+to_string(MYSERVERPORT);
		//std::cin >> bufstr;

		err = send(conSock, bufstr.c_str(), strlen(bufstr.c_str()), 0);
		//cout << bufstr;	
		if (err == SOCKET_ERROR)
		{
			//std::cout << "send failed!" << endl;
			return -1;
		}
		char buf[2048] = "\0";
		err = 0;
		err = recv(conSock, buf, 1024, 0);
		if (err == SOCKET_ERROR)
		{
			//std::cout << "rec reply failed!" << endl;
			return -1;
		}

		if (closesocket(conSock) != 0)
		{
			//std::cout << "closesocket failed!" << endl;
			//std::system("pause");
			return -1;
		}

		stringstream recStr;
		recStr << buf;
		int userID;
		recStr >> userID;
		string uname;;
		string nickname;

		if (userID == 0) {
			return 0;
		}
		recStr >> uname;
		recStr >> nickname;
		me.ID = userID;
		me.username = uname;
		me.nickname = nickname;
		return 1;
	}

	int mysocket::SignUp(string username, string pwd) {

		conSock = socket(AF_INET, SOCK_STREAM, 0);
		if (conSock == INVALID_SOCKET)
		{
			//std::cout << "conSock failed" << endl;
			return -1;
		}
		err = 0;
		err = connect(conSock, (sockaddr*)&hostAddr, sizeof(sockaddr));
		if (err == INVALID_SOCKET)
		{
			//std::cout << "connect failed!" << endl;
			return -1;
		}
		//std::cout << "input data: ";
		string bufstr = "-1 " + username + " " + pwd;
		//std::cin >> bufstr;

		err = send(conSock, bufstr.c_str(), strlen(bufstr.c_str()), 0);
		//cout << bufstr;	
		if (err == SOCKET_ERROR)
		{
			//std::cout << "send failed!" << endl;
			//std::system("pause");
			return -1;
		}
		char buf[2048] = "\0";
		err = 0;
		err = recv(conSock, buf, 1024, 0);
		if (err == SOCKET_ERROR)
		{
			//std::cout << "rec reply failed!" << endl;
			//std::system("pause");
			return -1;
		}

		//std::cout << "rec reply data" << buf << endl;
		if (closesocket(conSock) != 0)
		{
			//std::cout << "closesocket failed!" << endl;
			//std::system("pause");
			return -1;
		}

		stringstream recStr;
		recStr << buf;
		int res;
		recStr >> res;
		return res;
	}

	int mysocket::GetUsers(vector<user>& users, int userID) {
		conSock = socket(AF_INET, SOCK_STREAM, 0);
		if (conSock == INVALID_SOCKET)
		{
			//std::cout << "conSock failed" << endl;
			return -1;
		}
		err = 0;
		err = connect(conSock, (sockaddr*)&hostAddr, sizeof(sockaddr));
		if (err == INVALID_SOCKET)
		{
			//std::cout << "connect failed!" << endl;
			return -1;
		}
		//std::cout << "input data: ";
		string bufstr = "-2 "+to_string(userID);
		//std::cin >> bufstr;

		err = send(conSock, bufstr.c_str(), strlen(bufstr.c_str()), 0);
		//cout << bufstr;	
		if (err == SOCKET_ERROR)
		{
			//std::cout << "send failed!" << endl;
			//std::system("pause");
			return -1;
		}
		char buf[2048] = "\0";
		err = 0;
		err = recv(conSock, buf, 2048, 0);
		cout << buf;
		if (err == SOCKET_ERROR)
		{
			//std::cout << "rec reply failed!" << endl;
			//std::system("pause");
			return -1;
		}

		//std::cout << "rec reply data" << buf << endl;
		if (closesocket(conSock) != 0)
		{
			//std::cout << "closesocket failed!" << endl;
			//std::system("pause");
			return -1;
		}
		stringstream recStr;
		recStr << buf;
		int uID;
		string username;
		string nickname;
		string state;
		string IP;
		recStr >> uID;
		while (uID != 0)
		{
			//recStr >> username >> nickname >> state >> IP;
			recStr.get();
			getline(recStr, username);
			getline(recStr, nickname);
			getline(recStr, state);
			getline(recStr, IP);
			users.push_back(user{uID,username,nickname,state,IP});
			recStr >> uID;
		}
		return 1;
	}

	int mysocket::Send (int senderID, int receiverID ,string message, int sign,string idate,string itime) {
		conSock = socket(AF_INET, SOCK_STREAM, 0);
		if (conSock == INVALID_SOCKET)
		{
			//std::cout << "conSock failed" << endl;
			return -1;
		}
		err = 0;
		err = connect(conSock, (sockaddr*)&hostAddr, sizeof(sockaddr));
		if (err == INVALID_SOCKET)
		{
			//std::cout << "connect failed!" << endl;
			return -1;
		}
		//std::cout << "input data: ";
		string bufstr =to_string(senderID)+"\n"+to_string(receiverID)+"\n"+message+"\n"+to_string(sign) + "\n" + idate + "\n" + itime;
		//std::cin >> bufstr;

		err = send(conSock, bufstr.c_str(), strlen(bufstr.c_str()), 0);
		//cout << bufstr;	
		if (err == SOCKET_ERROR)
		{
			//std::cout << "send failed!" << endl;
			//std::system("pause");
			return -1;
		}
		//char buf[2048] = "\0";
		//err = 0;
		//err = recv(conSock, buf, 2048, 0);
		if (err == SOCKET_ERROR)
		{
			//std::cout << "rec reply failed!" << endl;
			//std::system("pause");
			return -1;
		}

		//std::cout << "rec reply data" << buf << endl;
		if (closesocket(conSock) != 0)
		{
			//std::cout << "closesocket failed!" << endl;
			//std::system("pause");
			return -1;
		}
		//stringstream recStr;
		//recStr << buf;
		//cout << buf;
		return 1;
	}