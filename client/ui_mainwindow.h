/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Person_list_Btn;
    QPushButton *Group_list_Btn;
    QLabel *label_3;
    QLabel *label_ID;
    QLabel *label_2;
    QLabel *label_name;
    QListWidget *Person_list;
    QListWidget *Group_list;

    void setupUi(QDialog *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(281, 682);
        MainWindow->setMinimumSize(QSize(281, 682));
        MainWindow->setMaximumSize(QSize(281, 682));
        MainWindow->setWindowOpacity(0);
        MainWindow->setSizeGripEnabled(false);
        horizontalLayoutWidget = new QWidget(MainWindow);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 111, 106));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        label->setMinimumSize(QSize(80, 80));
        label->setMaximumSize(QSize(80, 80));
        label->setStyleSheet(QStringLiteral("image: url(:/img/app.ico);"));
        label->setTextFormat(Qt::AutoText);

        horizontalLayout->addWidget(label);

        horizontalLayoutWidget_2 = new QWidget(MainWindow);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 110, 281, 52));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Person_list_Btn = new QPushButton(horizontalLayoutWidget_2);
        Person_list_Btn->setObjectName(QStringLiteral("Person_list_Btn"));
        Person_list_Btn->setMaximumSize(QSize(110, 40));

        horizontalLayout_2->addWidget(Person_list_Btn);

        Group_list_Btn = new QPushButton(horizontalLayoutWidget_2);
        Group_list_Btn->setObjectName(QStringLiteral("Group_list_Btn"));
        Group_list_Btn->setMinimumSize(QSize(20, 20));
        Group_list_Btn->setMaximumSize(QSize(110, 40));
        Group_list_Btn->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(Group_list_Btn);

        label_3 = new QLabel(MainWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(120, 40, 41, 30));
        label_3->setMinimumSize(QSize(0, 30));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_ID = new QLabel(MainWindow);
        label_ID->setObjectName(QStringLiteral("label_ID"));
        label_ID->setGeometry(QRect(170, 40, 181, 31));
        label_2 = new QLabel(MainWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 10, 51, 31));
        label_2->setMinimumSize(QSize(0, 30));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_name = new QLabel(MainWindow);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setGeometry(QRect(170, 10, 189, 31));
        Person_list = new QListWidget(MainWindow);
        Person_list->setObjectName(QStringLiteral("Person_list"));
        Person_list->setGeometry(QRect(10, 181, 256, 491));
        Group_list = new QListWidget(MainWindow);
        Group_list->setObjectName(QStringLiteral("Group_list"));
        Group_list->setGeometry(QRect(10, 180, 256, 491));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QDialog *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\245\275\345\217\213\345\210\227\350\241\250", Q_NULLPTR));
        label->setText(QString());
        Person_list_Btn->setText(QApplication::translate("MainWindow", "\345\245\275\345\217\213", Q_NULLPTR));
        Group_list_Btn->setText(QApplication::translate("MainWindow", "\347\276\244\347\273\204", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "ID\357\274\232", Q_NULLPTR));
        label_ID->setText(QApplication::translate("MainWindow", "123456", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        label_name->setText(QApplication::translate("MainWindow", "\345\274\240\344\270\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
