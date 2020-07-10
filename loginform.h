#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


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
};

#endif // LOGINFORM_H
