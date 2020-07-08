#pragma once
#include<mysql/jdbc.h>
#include<vector>
#include<string>
#include"general.h"
using namespace std;
namespace Linpop {
	int logIn(string username, string pwd);
	int signUp(string username, string pwd);
	vector<user>& getUsers(vector<user>& users,int userID);
	vector<group>& getGroups(vector<group>& groups,int userID);
	int createGroup(int userID, string groupname);
	int joinGroup(int userID, int groupID);
	int sendMessage(int senderID, int receiverID, string message, int sign, string date, string time);
	vector<chatmessage>& getChatMessage(vector<chatmessage>& messages, int senderID, int receiverID, int sign);

}