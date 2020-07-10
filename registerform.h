#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>



class RegisterForm : public QDialog
{
    Q_OBJECT
public:
    explicit RegisterForm(QDialog *parent = 0);

signals:
    void mainwindowshow();

public slots:
    void regis();
    void exit();
    void receivelogin();//显示主窗口槽函数
private:
    QLabel *userNameLbl;
    QLabel *pwdLbl;
    QLineEdit *userNameLEd;
    QLineEdit *pwdLEd;
    QPushButton *regisBtn;
    QPushButton *exitBtn;
};

#endif // REGISTERFORM_H
