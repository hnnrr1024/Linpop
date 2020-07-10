#pragma once
#include<string>
class user
{
public:
	user():ID(0){};
	user(int id,std::string username,std::string nickname=""):ID(id),username(username),nickname(nickname){};
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
	chatmessage():senderID(0),receiveID(0),groupID(0) {};
	chatmessage(int sid, int rid,int gid, std::string date, std::string time, std::string mess)
		:senderID(sid),receiveID(rid),groupID(gid),date(date),time(time),message(mess) {}
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