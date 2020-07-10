#include"SqlInterface.h"

Linpop::sqlInterface::sqlInterface() :driver(nullptr), con(nullptr), stmt(nullptr), res(nullptr) {
	driver = get_driver_instance();
	con = driver->connect("tcp://47.94.104.82:3306", "Neusoft", "123456"); 
	con->setSchema("Linpop");
	stmt = con->createStatement();
	stmt->execute("set names 'utf8'");
	
}

Linpop::sqlInterface::~sqlInterface() {
	if (con != nullptr)
		delete con;
	if (stmt != nullptr)
		delete stmt;
	if (res != nullptr)
		delete res;

}

user Linpop::sqlInterface::logIn(string username, string pwd) {
	user a;
	string sqlstr = "SELECT * FROM user WHERE username = '" + username + "';";
	try {
		res = stmt->executeQuery(sqlstr);
		cout << sqlstr << endl;
		res->next();
		if (res->getString("pwd") == pwd)
			a = user{ res->getInt("ID"),res->getString("username"),res->getString("nickname") };
		

	}
	catch (exception e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		//cout << " (MySQL error code: " << e.getErrorCode();
		//cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return user{ 0,"","" };
	}
	return a;
}

int Linpop::sqlInterface::signUp(string username, string pwd, string nickname) {
	string sqlstr = "INSERT INTO user(username, pwd, nickname)"\
		" VALUES('" + username + "', '" + pwd + "', '" + nickname + "');";
	cout << sqlstr << endl;
	try {
		stmt->executeUpdate(sqlstr);
		stmt->getUpdateCount();
		//res = stmt->executeQuery("SELECT * FROM user WHERE ID = (SELECT max(ID)FROM user)");
		return 1;
	}
	catch (exception e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		//cout << " (MySQL error code: " << e.getErrorCode();
		//cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return 0;
	}
	return 0;
}

int Linpop::sqlInterface::setNickname(int userID, string nickname) {
	string sqlstr = " UPDATE user SET nickname='" + nickname + "' WHERE ID=" + to_string(userID) + ";";
	try {
		stmt->executeUpdate(sqlstr);
		stmt->getUpdateCount();
		//res = stmt->executeQuery("SELECT * FROM user WHERE ID = (SELECT max(ID)FROM user)");
		return 1;
	}
	catch (exception e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		//cout << " (MySQL error code: " << e.getErrorCode();
		//cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return 2;
	}
	return 0;
}

int Linpop::sqlInterface::getUsers(vector<user>& users, int userID) {
	string sqlstr = "SELECT * from user WHERE ID != " + to_string(userID) + ";";
	cout << sqlstr << endl;
	try {
		res = stmt->executeQuery(sqlstr);
		while (res->next()) {
			users.emplace_back(user{ res->getInt("ID"),
				res->getString("username"),
				res->getString("nickname") });
		}
		//res = stmt->executeQuery("SELECT * FROM user WHERE ID = (SELECT max(ID)FROM user)");
		return 1;
	}
	catch (exception e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		//cout << " (MySQL error code: " << e.getErrorCode();
		//cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return 0;
	}
	return 0;
}

int Linpop::sqlInterface::getGroups(vector<group>& groups, int userID) {

	return 0;
}

int Linpop::sqlInterface::createGroup(int userID, string groupname) {

	return 0;
}

int Linpop::sqlInterface::joinGroup(int userID, int groupID) {

	return 0;
}

int Linpop::sqlInterface::sendMessage(int senderID, int receiverID, string message, int sign, string idate, string itime) {
	string sqlstr;
	time_t it = time(NULL);
	struct tm p;
	localtime_s(&p, &it);
	if (idate == "")
		idate = to_string(p.tm_year + 1900) + "/" + to_string(p.tm_mon + 1) + "/" + to_string(p.tm_mday);
	if (itime == "")
		itime = to_string(p.tm_hour) + ":" + to_string(p.tm_min) + ":" + to_string(p.tm_sec);
	if (sign == 0)
	{
		sqlstr = "INSERT INTO chatmessage(senderID, receiverID,date,time,message)"\
			" VALUES(" + to_string(senderID) + "," + to_string(receiverID) + ",'"
			+ idate + "', '" + itime + "', '" + message + "');";
		cout << sqlstr << endl;
	}
	else
	{
		sqlstr = "INSERT INTO chatmessage(senderID, groupID,date,time,message)"\
			" VALUES(" + to_string(senderID) + "," + to_string(receiverID) + ",'"
			+ idate + "', '" + itime + "', '" + message + "');";
		cout << sqlstr << endl;
	}
	try {
		stmt->executeUpdate(sqlstr);
		if (stmt->getUpdateCount() == 0)
			return 0;
		//res = stmt->executeQuery("SELECT * FROM user WHERE ID = (SELECT max(ID)FROM user)");
		return 1;
	}
	catch (sql::SQLException e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return 0;
	}
	return 0;
}

int Linpop::sqlInterface::getChatMessage(vector<chatmessage>& messages, int senderID, int receiverID, int sign) {
	string sqlstr;
	if (sign == 0)
	{
		sqlstr = "SELECT * from chatmessage WHERE"\
			" senderID=" + to_string(senderID) + "&&receiverID=" + to_string(receiverID) + ";";
		cout << sqlstr << endl;
	}
	else
	{
		sqlstr = "SELECT * from chatmessage WHERE"\
			" groupID=" + to_string(receiverID) + ";";
		cout << sqlstr << endl;
	}
	try {
		res=stmt->executeQuery(sqlstr);
		while (res->next())
		{
			if(sign==0)
				messages.emplace_back(chatmessage{res->getInt("senderID"),
					res->getInt("receiverID"),
					0,
					res->getString("date"),
					res->getString("time"),
					res->getString("message")});
			else if(sign ==1)
				messages.emplace_back(chatmessage{ res->getInt("senderID"),
					0,
					res->getInt("receiverID"),
					res->getString("date"),
					res->getString("time"),
					res->getString("message") });
		}
		//res = stmt->executeQuery("SELECT * FROM user WHERE ID = (SELECT max(ID)FROM user)");
		return 1;
	}
	catch (exception e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		//cout << " (MySQL error code: " << e.getErrorCode();
		//cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return 0;
	}

	return 0;
}