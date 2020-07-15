/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextBrowser *msg_Browser;
    QTextEdit *msg_Edit;
    QTableWidget *tableWidget;
    QToolButton *Send_btn;
    QPushButton *Exit_btn;
    QLabel *label;

    void setupUi(QDialog *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(640, 480);
        msg_Browser = new QTextBrowser(Widget);
        msg_Browser->setObjectName(QStringLiteral("msg_Browser"));
        msg_Browser->setGeometry(QRect(10, 40, 421, 221));
        msg_Edit = new QTextEdit(Widget);
        msg_Edit->setObjectName(QStringLiteral("msg_Edit"));
        msg_Edit->setGeometry(QRect(10, 290, 421, 171));
        tableWidget = new QTableWidget(Widget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(440, 40, 191, 371));
        Send_btn = new QToolButton(Widget);
        Send_btn->setObjectName(QStringLiteral("Send_btn"));
        Send_btn->setGeometry(QRect(340, 420, 71, 31));
        Exit_btn = new QPushButton(Widget);
        Exit_btn->setObjectName(QStringLiteral("Exit_btn"));
        Exit_btn->setGeometry(QRect(500, 420, 75, 31));
        Exit_btn->setLayoutDirection(Qt::LeftToRight);
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(270, 10, 81, 21));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QDialog *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\347\224\250\346\210\267", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Widget", "ID", Q_NULLPTR));
        Send_btn->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", Q_NULLPTR));
        Exit_btn->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\347\250\213\345\272\217\345\260\217\347\231\275", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
