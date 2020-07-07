#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

      //用户名Label
    userNameLbl = new QLabel(this);   //new一个标签对象
    userNameLbl->move(70,80);         //移动到(70,80)位置(Label左上角坐标，相对于父窗体)
    userNameLbl->setText("用户名:");  //设置标签文本

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
        RegisterBtn = new QPushButton(this);
        RegisterBtn->move(170,200);
        RegisterBtn->setText("注册");
    //槽函数
    connect(loginBtn,&QPushButton::clicked,this,&MainWindow::login);
    connect(RegisterBtn,&QPushButton::clicked,this,&MainWindow::Register);


}
void MainWindow::login()
{


}
void MainWindow::Register()
{


}


MainWindow::~MainWindow()
{
    delete ui;
}
