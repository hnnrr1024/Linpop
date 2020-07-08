#pragma once

#include <winsock2.h>
#include <string>
#include <thread>
#include <string>

#define MAXBUFFERSIZE (1024*4)

struct MsgHeader
{
	unsigned char type;
	unsigned short size;
};

#define MSG_REGISTER (1)
#define MSG_LOGIN    (2)
#define MSG_USERLIST (3)
#define MSG_MESSAGE  (4)
#define MSG_USERLIST (5)

class Server;

class Client
{
public:
	Client(SOCKET socket):_socket(socket), _server(nullptr) {}
	int sendMsg(int type, const std::string& msg);
	int recvMsg(int & type, std::string& msg);
	int runHandler() 
	{ 
		_handler = std::thread(&Client::msg_handler, this);
		return 0; 
	}
	int msg_handler();
	std::thread& msg_handler_thread() { return _handler; }
	const std::string& getUserId() { return _usrId; }
	void setUserId(const std::string& usrId) { _usrId = usrId; }
	
	void setServer(Server* server) { _server = server; }

public:
	// msg handler
	virtual int handle_message(const std::string& msg);
	virtual int handle_login_message(const std::string& msg);

//protected:
	std::string _usrId;
	SOCKET _socket;
	std::thread _handler;

	Server* _server;
};
