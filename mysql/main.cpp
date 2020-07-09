
#include <stdlib.h>
#include <iostream>
#include<mysql/jdbc.h>
#include"SqlInterface.h"
using namespace std;

int main()
{
    //string str = "INSERT INTO user"\
    //    "(username, pwd, nickname) VALUES ('Tony', '123456','tonycat' );";
    cout << endl;
    cout << "正在执行";


        Linpop::sqlInterface con;
        //登录
        user a = con.logIn("hnr","hannairui");
        if (a.ID != 0)
        {
        cout << a.ID << ' ' << a.username << ' ' << a.nickname << endl;
        cout << "该用户已成功登录" << endl;
        }
       
        vector<user> users;
        if (con.getUsers(users, 1)) {
            for (auto i : users) {
                cout << i.ID << ' ' << i.username << ' ' << i.nickname << endl;
            }
        }

        cout<<con.sendMessage(1, 2, "韩乃瑞");

        vector<chatmessage> messages;
        if (con.getChatMessage(messages,1,2)) {
            for (auto i : messages) {
                cout << i.senderID << ' ' << i.receiveID << ' '
                    << i.date << ' ' << i.time << ' ' << i.message << endl;
            }
        }

    cout << endl;

    return EXIT_SUCCESS;
}

