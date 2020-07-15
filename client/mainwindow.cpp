#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"

#include <QAction>
#include <QIcon>
#include "personlistbuddy.h"
#include "loginform.h"
extern user me;
extern vector<user> users;
extern mutex rwlock;
std::map<int, Widget*> WidbyID;

DWORD WINAPI listen(LPVOID lp) {
    WORD verision = MAKEWORD(2, 2);
    WSADATA lpData;
    int intEr = WSAStartup(verision, &lpData);//指定winsock版本并初始化
    if (intEr != 0)
    {
        cout << "winsock init failed!" << endl;
        return 0;
    }
    else
        cout << "winsock init success!" << endl;

    //创建侦听socket
    SOCKET listenScok = socket(AF_INET, SOCK_STREAM, 0);
    if (listenScok == INVALID_SOCKET)
    {
        cout << "socket error" << endl;
        return 0;
    }
    else
        cout << "create socket success" << endl;

    sockaddr_in hostAddr;
    hostAddr.sin_family = AF_INET;
    hostAddr.sin_port = htons(MYSERVERPORT);//转换成网络字节序
    //hostAddr.sin_addr.S_un.S_addr = inet_addr(SERVERIP);//转换成网络字节序
    //cout << "net IP:" << hostAddr.sin_addr.S_un.S_addr << endl;
    /*
    inet_addr()版本太低，被弃用使用inet_pton(协议族，字符串IP地址，void目标in_addr*)
    头文件：WS2tcpip.h
    */
    in_addr addr;
    inet_pton(AF_INET, SERVERIP, (void*)&addr);
    hostAddr.sin_addr = addr;

    char ip[1024] = { '\0' };
    inet_ntop(AF_INET, &addr, ip, 1024);
    cout << "ip:" << ip << endl;


    //侦听套接字listenSock绑定本机地址信息
    int err = 0;
    err = bind(listenScok, (struct sockaddr*)&hostAddr, sizeof(sockaddr));
    if (err != 0)
    {
        cout << "hostAddr bind failed!" << endl;
        return 0;
    }

    err = listen(listenScok, 3);
    if (err != 0)
    {
        cout << "listen socket listen failed!" << endl;
        return 0;
    }
    cout << "listening..." << endl;

    while (true)
    {
        sockaddr_in clientAddr;
        int len = sizeof(struct sockaddr);//必须指定长度，否则会导致accept返回10014错误								  //accept会循环等待客户端连接 
        SOCKET clientSock = accept(listenScok, (struct sockaddr*)&clientAddr, &len);

        if (clientSock == INVALID_SOCKET)
        {
            cout << "accept failed!" << endl;
            cout << WSAGetLastError() << endl;
            system("pause");
            return 0;
        }
        string replyStr;

        char buf[1024] = "\0";
        int buflen = recv(clientSock, buf, 1024, 0);
        if (buflen == SOCKET_ERROR)
        {
            cout << "recv failed!" << endl;
            return 0;
        }
        if (buflen == 0)
            continue;
        stringstream recStr;
        int receiverID;
        string message;
        string idate;
        string itime;
        recStr << buf;
        int useSign;
        recStr >> useSign;
        if (useSign == 0)
        {
            replyStr = "1";
            err = send(clientSock, replyStr.c_str(), strlen(replyStr.c_str()), 0);
        }
        else
        {
            recStr >> receiverID >> idate >> itime >> message;
            cout << useSign << receiverID << idate << itime << message << endl;
            string username;

            for (auto i : users)
            {
                if (i.ID == useSign)
                    username = i.username;
            }

            Widget* wid;
            if (WidbyID[useSign])
            {
                wid = WidbyID[useSign];
                user a = wid->receiver;
                wid->showMessage(username.c_str(), idate.c_str(), itime.c_str(), message.c_str());
            }
                
            replyStr = "1";
            err = send(clientSock, replyStr.c_str(), strlen(replyStr.c_str()), 0);
            cout << "err" << err << endl;
        }
    }
}


void MainWindow::initUserList() {
    rwlock.lock();
    int err;
    mysocket con;
    err = con.GetUsers(users, me.ID);
    rwlock.unlock();
}

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowOpacity(1.0);
    hThread = CreateThread(NULL, NULL, listen, NULL, 0, NULL);//创建新线程
    initUserList();

//设置用户信息
    //if(me.nickname!="")
    //    ui->label_name->setText(me.nickname.c_str());
    //else
        ui->label_name->setText(me.username.c_str());
    ui->label_ID->setText(to_string(me.ID).c_str());

//好友列表添加
    for (auto i : users)
    {
        if(i.state=="1")
            ui->Person_list->addItem(new QListWidgetItem(QIcon(":/img/User1.PNG"), tr(i.username.c_str())));
        else
            ui->Person_list->addItem(new QListWidgetItem(QIcon(":/img/User2.PNG"), tr(i.username.c_str())));
    }
    //ui->Person_list->addItem(new QListWidgetItem(QIcon(":/img/User1.PNG"),tr("张三")));
    //ui->Person_list->addItem(new QListWidgetItem(QIcon(":/img/User2.PNG"),tr("李四")));


//双击事件,打开聊天对话框
    connect(ui->Person_list,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(connectFri(QListWidgetItem *)));



//群组添加
    ui->Group_list->addItem(new QListWidgetItem(tr("朋友")));
    ui->Group_list->addItem(new QListWidgetItem(tr("同学")));
    ui->Group_list->addItem(new QListWidgetItem(tr("家人")));

    ui->Group_list->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}



//初始化菜单
/*
void personList::initMenu()
{
    //初始化：
    blankMenu = new QMenu();
    groupMenu = new QMenu();
    personMenu = new QMenu();
    groupNameEdit=new QLineEdit();
    QAction *addGroup = new QAction("添加分组", this);
    QAction *delGroup = new QAction("删除该组", this);
    QAction *rename = new QAction("重命名", this);
    QAction *addBuddy = new QAction("添加好友",this);
    QAction *delBuddy = new QAction("删除好友", this);
    //设置：
    groupNameEdit->setParent(this);  //设置父类
    groupNameEdit->hide(); //设置初始时隐藏
    groupNameEdit->setPlaceholderText("未命名");//设置初始时的内容
    //布局：
    blankMenu->addAction(addGroup);
    groupMenu->addAction(delGroup);
    groupMenu->addAction(rename);
    groupMenu->addAction(addBuddy);
    personMenu->addAction(delBuddy);
    //信息槽：
    connect(groupNameEdit,SIGNAL(editingFinished()),this,SLOT(slotRenameEditFshed()));
    connect(addGroup,SIGNAL(triggered()),this,SLOT(slotAddGroup()));
    connect(delGroup,SIGNAL(triggered()),this,SLOT(slotDelGroup()));
    connect(rename,SIGNAL(triggered()),this,SLOT(slotRename()));
    connect(addBuddy,SIGNAL(triggered()),this,SLOT(slotAddBuddy()));
    connect(delBuddy,SIGNAL(triggered()),this,SLOT(slotDelBuddy()));
}
//鼠标点击事件
void personList::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event); // 如果不调用基类mousePressEvent，item被select会半天不响应,调用父类，让QSS起效，因为QSS基于父类QListWidget，子类就是子窗口，就是最上层窗口，是覆盖在父窗口上的，所以先于父窗口捕获消息
    //防止一种特殊情况：给新item命名、点击其他item或空白处时，指向新item的currentItem被赋予其他item
    if(groupNameEdit->isVisible() && !(groupNameEdit->rect().contains(event->pos())))
    {
        if(groupNameEdit->text()!=NULL)
            currentItem->setText(groupNameEdit->text());
        groupNameEdit->setText("");
        groupNameEdit->hide();
    }
    currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));//鼠标位置的Item，不管右键左键都获取
    if(event->button()==Qt::LeftButton && currentItem!=NULL && currentItem==groupMap.value(currentItem))//如果点击的左键并且是点击的是组
    {
        if(isHideMap.value(currentItem))                                  //如果先前是隐藏，则显示
        {
            foreach(QListWidgetItem* subItem, groupMap.keys(currentItem))//遍历组的对应的项（包括自身和好友）
                if(subItem!=currentItem)                                 //如果是组的话不进行处理
                {
                    subItem->setHidden(false);                            //好友全部显示
                }
            isHideMap.insert(currentItem,false);                          //设置该组为显示状态
            currentItem->setIcon(QIcon(":/arrowDown"));
        }
        else                                                             //否则，先前是显示，则隐藏
        {
            foreach(QListWidgetItem* subItem, groupMap.keys(currentItem))//遍历组的对应的项（包括自身和好友）
                if(subItem!=currentItem)                                 //如果是组的话不进行处理
                {
                    subItem->setHidden(true);                            //好友全部隐藏
                }
             isHideMap.insert(currentItem,true);                          //设置该组为隐藏状态
             currentItem->setIcon(QIcon(":/arrowRight"));
        }
    }
}
//菜单事件，为了显示菜单，点击鼠标右键响应，鼠标点击事件mousePressEvent优先于contextMenuEvent
void personList::contextMenuEvent(QContextMenuEvent *event)
{
    QListWidget::contextMenuEvent(event);           //调用基类事件
    if(currentItem==NULL)                           //如果点击到的是空白处
    {
        blankMenu->exec(QCursor::pos());
        return;
    }
    if(currentItem==groupMap.value(currentItem))    // 如果点击到的是组
        groupMenu->exec(QCursor::pos());
    else                                            //否则点击到的是好友
        personMenu->exec(QCursor::pos());
}
//添加组
void personList::slotAddGroup()
{
    QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/arrowRight"),"未命名");    //创建一个Item
    newItem->setSizeHint(QSize(this->width(),25));//设置宽度、高度
    this->addItem(newItem);         //加到QListWidget中
    groupMap.insert(newItem,newItem);//加到容器groupMap里，key和value都为组
    isHideMap.insert(newItem,true);  //设置该组隐藏状态
    groupNameEdit->raise();
    groupNameEdit->setText(tr("未命名")); //设置默认内容
    groupNameEdit->selectAll();        //设置全选
    groupNameEdit->setGeometry(this->visualItemRect(newItem).left()+15,this->visualItemRect(newItem).top()+1,this->visualItemRect(newItem).width(),this->visualItemRect(newItem).height()-2);//出现的位置
    groupNameEdit->show();              //显示
    groupNameEdit->setFocus();          //获取焦点
    currentItem = newItem;	   // 因为要给group命名，所以当前的currentItem设为该group
}
//删除组
void personList::slotDelGroup()
{
    foreach(QListWidgetItem* item, groupMap.keys(currentItem))  //遍历该组的所有好友和自身的组
    {
        groupMap.remove(item);   //移除
        delete item;   //删除
    }
    isHideMap.remove(currentItem); //移除
}
//重命名
void personList::slotRename()
{
    groupNameEdit->raise();
    groupNameEdit->setGeometry(this->visualItemRect(currentItem).left()+15,this->visualItemRect(currentItem).top()+1,this->visualItemRect(currentItem).width(),this->visualItemRect(currentItem).height()-2);//出现的位置
    groupNameEdit->setText(currentItem->text());   //获取该组名内容
    groupNameEdit->show();                        //显示
    groupNameEdit->selectAll();                   //全选
    groupNameEdit->setFocus();                        //获取焦点
}
//添加好友，主要是为了测试功能，实际工程里可以改成动态读取数据库进行添加好友
void personList::slotAddBuddy()
{
    personListBuddy *buddy=new personListBuddy();   //创建一个自己定义的信息类
    buddy->headPath=":/head";                          //设置头像路径
    buddy->name->setText("逍遥圣帝");                  //设置用户名
    buddy->sign->setText("用通俗的语言，讲深刻的技术。");   //设置个性签名
    QList<QListWidgetItem*> tem = groupMap.keys(currentItem);//当前组对应的项（包括组本身和好友）复制给tem
    //关键代码
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
    this->insertItem(row(currentItem)+tem.count(),newItem); //将该newItem插入到后面
    this->setItemWidget(newItem, buddy); //将buddy赋给该newItem
    groupMap.insert(newItem,currentItem);   //加进容器，key为好友，value为组
    if(isHideMap.value(currentItem))          //如果该组是隐藏，则加进去的好友设置为隐藏
        newItem->setHidden(true);
    else                                      //否则，该好友设置为显示
        newItem->setHidden(false);
}
//删除好友
void personList::slotDelBuddy()
{
    groupMap.remove(currentItem);  //移除该好友
    delete currentItem;            //删除
}
//重命名完成
void personList::slotRenameEditFshed()
{
    if(groupNameEdit->text()!=NULL)      //如果重命名编辑框不为空
        currentItem->setText(groupNameEdit->text());  //更新组名
    groupNameEdit->setText("");
    groupNameEdit->hide();  //隐藏重命名编辑框
}
*/


void MainWindow::connectFri(QListWidgetItem *Item )//打开聊天对话框
{
    QString username = Item->text();
    user rec;
    rwlock.lock();
    for (auto i : users)
    {
        if (i.username == username.toStdString())
        {
            rec.ID = i.ID;
            rec.IP = i.IP;
            rec.nickname = i.nickname;
            rec.username = i.username;
        }
    }
    rwlock.unlock();
    
    Widget *wit;
    wit = new Widget();
    WidbyID[rec.ID] = wit;
    wit->setReceiver(rec);
    wit->show();

}

void MainWindow::on_Person_list_Btn_clicked()
{
    ui->Group_list->hide();
    ui->Person_list->show();
}

void MainWindow::on_Group_list_Btn_clicked()
{
    ui->Group_list->show();
    ui->Person_list->hide();
}
