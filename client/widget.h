#ifndef WIDGET_H
#define WIDGET_H

#include <QDialog>
//#include <QTcpServer>
//#include <QTcpSocket>

#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>
#include "mysocket.h"

namespace Ui {
class Widget;
}

class Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setReceiver(user a); 
    void showMessage(QString, QString, QString, QString);
    user receiver;
private slots:
    void on_Send_btn_clicked();
    void on_Exit_btn_clicked();
   
   
    //void socket_Read_Date();
    



private:
    Ui::Widget *ui;
    //QTcpSocket *socket;
    

    void my_connect();

};

#endif // WIDGET_H
