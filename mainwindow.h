#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void login();//点击登录按钮是执行的槽函数
    void Register();
private:
    Ui::MainWindow *ui;
    QLabel *userNameLbl;         //"用户名"标签
    QLabel *pwdLbl;              //"密码"标签
    QLineEdit *userNameLEd;      //用户名编辑行
    QLineEdit *pwdLEd;           //密码编辑行
    QPushButton *loginBtn;       //登录按钮
    QPushButton *RegisterBtn;        //注册按钮


};

#endif // MAINWINDOW_H
