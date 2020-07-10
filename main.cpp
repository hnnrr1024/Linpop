#include <QApplication>
#include "mainform.h"
#include "loginform.h"
#include "registerform.h"

int main(int argc,char** argv)
{
    QApplication app(argc,argv);


    LoginForm l;



    MainForm m;
    RegisterForm r;

   // QObject::connect(&l,SIGNAL(registeredshow()),&r,SLOT(receivelogin()));

    //l.show();
   // return app.exec();



    if (l.exec() == QDialog::Accepted)//调用l.exec()，阻塞主控制流，直到完成返回
    {
       m.show();
       return app.exec();
    }
    else return 0;





}
