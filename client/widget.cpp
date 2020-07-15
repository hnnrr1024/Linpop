#include "widget.h"
#include "ui_widget.h"

#include "QMessageBox"
#include "QDebug"
#include "QString"
#include "QDateTime"
#include "QTextCodec"

#include <QTableWidget>
#include <QTableWidgetItem>

extern user me;

Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(tr("NeuTalk"));

    QTableWidget *tableWidget = new QTableWidget(1,2);


    //socket = new QTcpSocket();
    //connect(socket, SIGNAL(readyRead()), this, SLOT(socket_Read_Date()));

    //my_connect();

}

Widget::~Widget()
{
    delete ui;
    //delete this->socket;
}

void Widget::setReceiver(user a)
{
    receiver = a;
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(receiver.username.c_str()));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(to_string(receiver.ID).c_str()));
    ui->label->setText(receiver.username.c_str());
}

void Widget::showMessage(QString username,QString idate,QString itime,QString message)
{
    ui->msg_Browser->append(username+ ":" + idate +" " + itime);
    ui->msg_Browser->append(message);
}

void Widget::on_Send_btn_clicked()
{
    QString timelist;
    QString idate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString itime = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString username(me.username.c_str());
    timelist = username+ ": " + idate+" "+itime;

    mysocket con;
    int err = con.Send(me.ID,receiver.ID, ui->msg_Edit->toPlainText().toStdString(),0,idate.toStdString(),itime.toStdString());

    ui->msg_Browser->append(timelist);
    ui->msg_Browser->append(ui->msg_Edit->toPlainText());
    ui->msg_Edit->clear() ;
}

void Widget::on_Exit_btn_clicked()
{
    this->close();
}
