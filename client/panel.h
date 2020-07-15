#ifndef PANEL_H
#define PANEL_H

#include <QMainWindow>
//#include"mainwindow.h"
#include <QListWidgetItem>
#include "mysocket.h"

namespace Ui {
class panel;
}

class panel : public QMainWindow
{
    Q_OBJECT

public:
    panel(QWidget *parent = 0);
    ~panel();
    void init();
private slots:
    void on_pushButton_clicked();

private:
    Ui::panel *ui;
    QString ip;
    QString port;
    QString id;
   // QUdpSocket *udpSocket;
   // QHash<QString,MainWindow *> chatFormHash;

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private slots:
    void recvMsg();
    void on_friendwidget_itemDoubleClicked(QListWidgetItem *item);
};

#endif // PANEL_H
