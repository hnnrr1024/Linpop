#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "mainform.h"
#include "registerform.h"
#include "panel.h"
class LoginForm : public QDialog
{
    Q_OBJECT
public:
    explicit LoginForm(QDialog *parent = 0);



signals:
    void registeredshow();

public slots:
    void login();
    void regis();
private:
    QLabel *userNameLbl;
    QLabel *pwdLbl;
    QLineEdit *userNameLEd;
    QLineEdit *pwdLEd;
    QPushButton *loginBtn;
    QPushButton *regisBtn;

    MainForm *mainf;
    RegisterForm *Regist;
    panel *pan;
};

#endif // LOGINFORM_H
