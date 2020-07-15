#pragma once
#include<mysql/jdbc.h>
#include<vector>
#include<string>
#include<ctime>
#include"general.h"
using std::string;
using std::vector;
using  std::cout;
using  std::endl;
using std::exception;
using std::to_string;

//extern user me;
//extern  std::vector<user> users;
//extern  std::vector<group> groups;
namespace Linpop {

	class sqlInterface {
	public:
		sqlInterface();
		~sqlInterface();
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