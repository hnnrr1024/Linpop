#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "mysocket.h"


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

private:
    QLabel *userNameLbl;
    QLabel* pwdLbl1;
    QLabel* pwdLbl2;
    QLineEdit* userNameLEd;
    QLineEdit* pwdLEd1;
    QLineEdit* pwdLEd2;
    QPushButton *regisBtn;
    QPushButton *exitBtn;
};

#endif // REGISTERFORM_H
