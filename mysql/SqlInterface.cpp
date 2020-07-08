#include"SqlInterface.h"

int Linpop::logIn(string username, string pwd) {

	return 0;
}

int Linpop::signUp(string username, string pwd) {

	return 0;
}

vector<user>& Linpop::getUsers(vector<user>& users, int userID) {

	return users;
}

vector<group>& Linpop::getGroups(vector<group>& groups, int userID) {

	return groups;
}

int Linpop::createGroup(int userID, string groupname) {

	return 0;
}

int Linpop::joinGroup(int userID, int groupID) {

	return 0;
}

int Linpop::sendMessage(int senderID, int receiverID, string message, int sign = 0, string date = "", string time = "") {

	return 0;
}

vector<chatmessage>& Linpop::getChatMessage(vector<chatmessage>& messages, int senderID, int receiverID, int sign = 0) {

	return messages;
}