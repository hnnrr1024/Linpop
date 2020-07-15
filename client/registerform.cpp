
#include "registerform.h"
#include <QMessageBox>
#include "loginform.h"


RegisterForm::RegisterForm(QDialog *parent) :
    QDialog(parent)
{
    //设置窗体标题
    this->setWindowTitle(tr("注册界面"));

    //用户名Label
    userNameLbl = new QLabel(this);
    userNameLbl->move(70,80);//移动到(70,80)位置(Label左上角坐标，相对于父窗体)
    userNameLbl->setText("用户名:");

    //用户名输入框
    userNameLEd = new QLineEdit(this);
    userNameLEd->move(120,80);
    userNameLEd->setPlaceholderText(tr("请输入用户名!"));//占位符

 //密码Label
    pwdLbl1 = new QLabel(this);
    pwdLbl1->move(80, 130);
    pwdLbl1->setText("密码:");

    //密码输入框
    pwdLEd1 = new QLineEdit(this);
    pwdLEd1->move(120, 125);
    pwdLEd1->setPlaceholderText("请输入密码!");
    pwdLEd1->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示

        //重复密码Label
    pwdLbl2 = new QLabel(this);
    pwdLbl2->move(40, 180);
    pwdLbl2->setText("再次输入密码:");

    //重复密码输入框
    pwdLEd2 = new QLineEdit(this);
    pwdLEd2->move(120, 175);
    pwdLEd2->setPlaceholderText("请再次输入密码!");
    pwdLEd2->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示
    //注册按钮
    regisBtn = new QPushButton(this);
    regisBtn->move(80,200);
    regisBtn->setText("注册新用户");

    //退出按钮
    exitBtn = new QPushButton(this);
    exitBtn->move(170,200);
    exitBtn->setText("返回登录");

    //单击登录按钮时 执行 LoginForm::login 槽函数；//单击退出按钮时 执行 LoginForm::close 槽函数
    connect(regisBtn,&QPushButton::clicked,this,&RegisterForm::regis);
    connect(exitBtn,&QPushButton::clicked,this,&RegisterForm::exit);


}

void RegisterForm::regis()//注册新用户槽函数
{
    string username = userNameLEd->text().trimmed().toStdString();
    string pwd = pwdLEd1->text().toStdString();
    string pwd2 = pwdLEd2->text().toStdString();
    mysocket con;
    if (pwd != pwd2)
    {
        QMessageBox::warning(this, tr("警告！"),
            tr("两次密码输入不一致，请重新输入！"),
            QMessageBox::Yes);
        userNameLEd->clear();
        pwdLEd1->clear();
        pwdLEd2->clear();
        return;
    }
    if (con.SignUp(username, pwd))
    {
        QMessageBox::warning(this, tr("恭喜！"),
            tr("注册成功！点击确定返回登录界面！"),
            QMessageBox::Yes);
        accept();//关闭窗体，并设置返回值为Accepted
    }
    else {
        QMessageBox::warning(this, tr("警告！"),
            tr("注册失败,用户名已存在！"),
            QMessageBox::Yes);
        // 清空内容
        userNameLEd->clear();
        pwdLEd1->clear();
        pwdLEd2->clear();
        //定位光标
        userNameLEd->setFocus();
    }
}

void RegisterForm::exit()//返回登录，关闭注册界面
{
    close();
}
