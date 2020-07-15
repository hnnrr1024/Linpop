#include <QApplication>
#include "mainform.h"
#include "loginform.h"
#include "registerform.h"
#include "personlistbuddy.h"
#include "mainwindow.h"
#include "widget.h"

int main(int argc,char** argv)
{
    QApplication app(argc,argv);
    LoginForm l;
    l.show();
    return app.exec();


}
