#pragma once
#include<string>
class user
{
public:
	int ID;
	std::string username;
	std::string nickname;
	std::string state;
	std::string IP;
};

class groupmember
{
public:
	int groupID;
	int userID;
	int type;
};

class group
{
public:
	int ID;
	std::string groupname;
};

class chatmessage
{
public:
	int senderID;
	int receiveID;
	int groupID;
	std::string date;
	std::string time;
	std::string message;
};

class filemessage
{
public:
	int senderID;
	int receiveID;
	int groupID;
	std::string date;
	std::string time;
	std::string filename;
};