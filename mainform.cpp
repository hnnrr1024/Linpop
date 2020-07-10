#include "mainform.h"

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent)
{
    //MainForm *main = new MainForm();
    this->setWindowTitle("欢迎界面");

    tipLbl = new QLabel(this);
    tipLbl->setText(tr("欢迎登录"));
}

