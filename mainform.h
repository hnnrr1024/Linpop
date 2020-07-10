#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QLabel>
class MainForm : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = 0);

signals:

public slots:
private:
    QLabel *tipLbl;
};

#endif // MAINFORM_H
