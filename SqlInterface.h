#pragma once
#include<mysql/jdbc.h>
#include<vector>
#include<string>
#include<ctime>
#include"general.h"
using namespace std;
namespace Linpop {
	class sqlInterface {
	public:
		sqlInterface();
		~sqlInterface();
		sqlInterface(sqlInterface& a):driver(nullptr), con(nullptr), stmt(nullptr), res(nullptr) {};
		user logIn(string username, string pwd);
		int signUp(string username, string pwd, string nickname = "");
		int setNickname(int userID, string nickname);
		int getUsers(vector<user>& users, int userID);
		int getGroups(vector<group>& groups, int userID);
		int createGroup(int userID, string groupname);
		int joinGroup(int userID, int groupID);
		int sendMessage(int senderID, int receiverID, string message, int sign = 0, string date = "", string time = "");
		int getChatMessage(vector<chatmessage>& messages, int senderID, int receiverID, int sign = 0);
	private:
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;
	};
	
}