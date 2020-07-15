#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

#include <QListWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QStringListModel>
#include "mysocket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QListWidget *listWidget;
    QStandardItemModel *ItemModel;
    QStringListModel *Model;
    QListWidgetItem * Item;
    void initUserList();
    HANDLE hThread;


private slots:
    //void itemClicked(QModelIndex index);
    void on_Person_list_Btn_clicked();
    void on_Group_list_Btn_clicked();

    void connectFri(QListWidgetItem *);

};



#endif // MAINWINDOW_H
