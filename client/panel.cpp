#include "panel.h"
#include "ui_panel.h"
#include <QMessageBox>
panel::panel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::panel)
{
    this->ip = ip;
    this->port = port;
    this->id = id;
    this->init();
    ui->setupUi(this);
}

panel::~panel()
{
    delete ui;
}
//绑定6666端口作为服务器和客户端的通信端口，初始化的时候发送MSG_NEW_CONN消息

void panel::init()
{
   /* udpSocket = new QUdpSocket(this);
    udpSocket->bind(6666);
    QString msgType = "MSG_CLIENT_NEW_CONN";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << (quint16)0 << msgType << id;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    udpSocket->writeDatagram(block.data(), block.size(), QHostAddress(ip), (quint16)port.toUInt()+1);
    connect(this->udpSocket,SIGNAL(readyRead()),this,SLOT(recvMsg()));*/
}

void panel::on_pushButton_clicked()
{
    /*QString msgType = "MSG_USER_LOGOUT";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out << (quint16)0 << msgType << id;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    if (!udpSocket->writeDatagram(block.data(), block.size(), QHostAddress(ip), (quint16)port.toUInt()+1))
    {
        QMessageBox::warning(NULL, tr("udpSocket"), tr("writeDatagram."));
    }
    this->close();*/
}


void panel::on_friendwidget_itemDoubleClicked(QListWidgetItem *item)
{
   /* item=item;
    QString nameStr = ui->friendwidget->currentItem()->text();

    nameStr.replace("\n","");
    QString tempstr(nameStr);
    MainWindow *c = chatFormHash.value(nameStr);//根据名称到HASH表当中寻找已经创建的窗口。否则重新创建窗口
    if(c == 0)
    {
        c = new MainWindow(this->id,this->ip,this->port,udpSocket);
        c->setWindowTitle("chatting with " + nameStr + ".");
        chatFormHash.insert(nameStr,c);
    }
    c->show();*/
}

void panel::closeEvent(QCloseEvent *e)
{
    /*e=e;
    panel::on_pushButton_clicked();*/
}

void panel::changeEvent(QEvent *e)
{
    /*QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }*/
}

void panel::recvMsg()
{
    /*QByteArray block;
    QString msgType;
    QStringList idList;
    QStringList nameList;
    quint16 size;
    QHostAddress peerIp;
    quint16 peerPort;
    block.resize(udpSocket->pendingDatagramSize());
    this->udpSocket->readDatagram(block.data(),block.size(),&peerIp,&peerPort);
    QDataStream in(&block,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_2);
    in>>size>>msgType;
    if("MSG_ALL_USER_ONLINE" == msgType)
    {
        in>>idList>>nameList;
        for(int i = 0; i < idList.count(); i++)
        {
            QString itemString;
            itemString = nameList.at(i) +"("+ idList.at(i)+")";
            ui->friendwidget->addItem(itemString);
        }
        ui->count->setText(QString::number(ui->friendwidget->count()) + " user online");
    }
    if("MSG_CLIENT_CHAT" == msgType)
    {
        QString peerName;
        QString peerId;
        QString msg;
        in>>peerName>>peerId>>msg;

        QString valueHash;
        valueHash.append(peerName + "(" + peerId + ")");
        MainWindow *c;
        if(chatFormHash.contains(valueHash))
        {
            c = chatFormHash.value(valueHash);
        }
        else
        {
            c = new MainWindow(this->id,this->ip,this->port,this->udpSocket);
            c->setWindowTitle("chatting with " + peerName + "(" + peerId + ").");
            chatFormHash.insert(valueHash,c);
        }
        c->show();
        c->displayText(peerName,peerId,msg);
    }
    if("MSG_SERVER_INFO" == msgType)
    {
        QString msg;
        in>>msg;
        ui->msgwidget->addItem("server : " + msg);
    }
    if("MSG_NEW_USER_LOGIN" == msgType)
    {
        QString peerName;
        QString peerId;
        QString user;
        in>>peerId>>peerName;
        if(this->id != peerId)
        {
            user.append(peerName + "(" + peerId + ")");
            for(int i = 0; i < ui->friendwidget->count(); i++)
            {
                if(ui->friendwidget->item(i)->text() == user)
                {
                    delete ui->friendwidget->takeItem(i);
                }
            }
            ui->friendwidget->addItem(user);
            ui->msgwidget->addItem(user + " login.");
            ui->count->setText(QString::number(ui->friendwidget->count()) + " user online");
        }
    }
    if("MSG_CLIENT_LOGOUT" == msgType)
    {
        QString peerName;
        QString peerId;
        QString userStr;
        in>>peerId>>peerName;
        userStr.append(peerName + "(" + peerId + ")");
        for(int i = 0; i < ui->friendwidget->count(); i++)
        {
            if(ui->friendwidget->item(i)->text() == userStr)
            {
                delete ui->friendwidget->takeItem(i);
            }
        }
        MainWindow *c = chatFormHash.value(userStr);
        if(c != 0)
        {
            c->close();
            chatFormHash.remove(userStr);
        }
        ui->msgwidget->addItem(userStr + " logout.");
        ui->count->setText(QString::number(ui->friendwidget->count()) + " user online");
    }*/
}

