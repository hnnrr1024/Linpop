//#include <QApplication>

#include "loginform.h"
#include <QMessageBox>
#include "registerform.h"
#include "SqlInterface.h"

LoginForm::LoginForm(QDialog *parent) :
    QDialog(parent)
{
    //设置窗体标题
    this->setWindowTitle(tr("登录界面"));

    //用户名Label
    userNameLbl = new QLabel(this);
    userNameLbl->move(70,80);//移动到(70,80)位置(Label左上角坐标，相对于父窗体)
    userNameLbl->setText("用户名:");

    //用户名输入框
    userNameLEd = new QLineEdit(this);
    userNameLEd->move(120,80);
    userNameLEd->setPlaceholderText(tr("请输入用户名!"));//占位符

    //密码Label
    pwdLbl = new QLabel(this);
    pwdLbl->move(80,130);
    pwdLbl->setText("密码:");

    //密码输入框
    pwdLEd = new QLineEdit(this);
    pwdLEd->move(120,130);
    pwdLEd->setPlaceholderText("请输入密码!");
    pwdLEd->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示

    //登录按钮
    loginBtn = new QPushButton(this);
    loginBtn->move(80,200);
    loginBtn->setText("登录");

    //退出按钮
    regisBtn = new QPushButton(this);
    regisBtn->move(170,200);
    regisBtn->setText("注册");

    //单击登录按钮时 执行 LoginForm::login 槽函数；//单击退出按钮时 执行 LoginForm::close 槽函数
    connect(loginBtn,&QPushButton::clicked,this,&LoginForm::login);
    connect(regisBtn,&QPushButton::clicked,this,&LoginForm::regis);


}

void LoginForm::login()
{
    //获得userNameLEd输入框的文本userNameLEd->text()；
    //trimmed()去掉前后空格
    //tr()函数，防止设置中文时乱码

    Linpop::sqlInterface con;
    string username = userNameLEd->text().trimmed().toStdString();
    string pwd = pwdLEd->text().toStdString();
    user me = con.logIn(username, pwd);

    if(me.ID!=0)
    {
       accept();//关闭窗体，并设置返回值为Accepted

    } else {
       QMessageBox::warning(this, tr("警告！"),
                   tr("用户名或密码错误！"),
                   QMessageBox::Yes);
       // 清空内容
       userNameLEd->clear();
       pwdLEd->clear();
       //定位光标
       userNameLEd->setFocus();
    }
}

void LoginForm::regis()//注册按钮槽函数，显示注册界面
{

   RegisterForm r;
   r.exec();

}
