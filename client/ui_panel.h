/********************************************************************************
** Form generated from reading UI file 'panel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_H
#define UI_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_panel
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QListWidget *friendwidget;
    QLabel *count;
    QGroupBox *groupBox_2;
    QListWidget *msgwidget;
    QMenuBar *menubar;

    void setupUi(QMainWindow *panel)
    {
        if (panel->objectName().isEmpty())
            panel->setObjectName(QStringLiteral("panel"));
        panel->resize(357, 621);
        centralwidget = new QWidget(panel);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(250, 570, 75, 23));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 341, 291));
        friendwidget = new QListWidget(groupBox);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/img/head.PNG"), QSize(), QIcon::Normal, QIcon::On);
        icon.addFile(QStringLiteral(":/img/app.ico"), QSize(), QIcon::Selected, QIcon::Off);
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::NoBrush);
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(friendwidget);
        __qlistwidgetitem->setFont(font);
        __qlistwidgetitem->setBackground(brush);
        __qlistwidgetitem->setIcon(icon);
        new QListWidgetItem(friendwidget);
        friendwidget->setObjectName(QStringLiteral("friendwidget"));
        friendwidget->setGeometry(QRect(10, 40, 321, 231));
        count = new QLabel(groupBox);
        count->setObjectName(QStringLiteral("count"));
        count->setGeometry(QRect(30, 20, 81, 16));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 320, 341, 241));
        msgwidget = new QListWidget(groupBox_2);
        new QListWidgetItem(msgwidget);
        new QListWidgetItem(msgwidget);
        msgwidget->setObjectName(QStringLiteral("msgwidget"));
        msgwidget->setGeometry(QRect(10, 20, 321, 211));
        panel->setCentralWidget(centralwidget);
        menubar = new QMenuBar(panel);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 357, 23));
        panel->setMenuBar(menubar);

        retranslateUi(panel);

        QMetaObject::connectSlotsByName(panel);
    } // setupUi

    void retranslateUi(QMainWindow *panel)
    {
        panel->setWindowTitle(QApplication::translate("panel", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("panel", "quit", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("panel", "friend list", Q_NULLPTR));

        const bool __sortingEnabled = friendwidget->isSortingEnabled();
        friendwidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = friendwidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("panel", "\345\245\275\345\217\2131", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        ___qlistwidgetitem->setWhatsThis(QApplication::translate("panel", "<html><head/><body><p><span style=\" vertical-align:sub;\">\351\241\272\350\276\276\351\241\272\350\276\276</span></p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        QListWidgetItem *___qlistwidgetitem1 = friendwidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("panel", "\345\245\275\345\217\2132", Q_NULLPTR));
        friendwidget->setSortingEnabled(__sortingEnabled);

        count->setText(QApplication::translate("panel", "frined count", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("panel", "server msg", Q_NULLPTR));

        const bool __sortingEnabled1 = msgwidget->isSortingEnabled();
        msgwidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem2 = msgwidget->item(0);
        ___qlistwidgetitem2->setText(QApplication::translate("panel", "li4", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem3 = msgwidget->item(1);
        ___qlistwidgetitem3->setText(QApplication::translate("panel", "zhang3", Q_NULLPTR));
        msgwidget->setSortingEnabled(__sortingEnabled1);

    } // retranslateUi

};

namespace Ui {
    class panel: public Ui_panel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_H
