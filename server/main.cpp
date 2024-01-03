#include <QCoreApplication>
#include <QTimer>


#include "Database.h"
#include "MsgPackage.h"
#include "MsgHandle.h"
<<<<<<< HEAD
#include "ServerSocket.h"
=======
#include "Server.h"
>>>>>>> 41f8a5972cbd57d0b1a15843c04e8327d493d2b0

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
/*
    Database db;
    MsgHandle handler(db);

    LoginInfo info2 = {"Virgo", "test", "127.0.0.1", "1113"};
    if(handler._login(&info2) == SUCCESS)
        qDebug() << "User 'Virgo' Login success!";
    MessageInfo msg = {"Virgo", "test1", "nishi?", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")};

    qDebug() << msg.time;
    if(handler._message(&msg) == SUCCESS)
        qDebug() << "Message sent!";

    RegisterInfo info1 = {"test2", "test", "nishi?", "woshi"};
    if(handler._register(&info1) == SUCCESS)
        qDebug() << "Register success!";



<<<<<<< HEAD
    //创建QTcpServer，开启监听
    Server = new QTcpServer();
    Server->listen(QHostAddress::AnyIPv4, MYPORT);

    qDebug()<<"success";

    //connect函数接受newConnection信号
    //登陆成功界面需要发送该信号
    connect(Server, SIGNAL(newConnection()), this, SLOT(new_clients()));



    RegisterInfo info1 = {"Virgo", "test", "nishi?", "woshi"};
    LoginInfo info2 = {"Virgo", "test", "127.0.0.1", "1111"};
    LogoutInfo info3 = {"Virgo"};
=======
>>>>>>> 41f8a5972cbd57d0b1a15843c04e8327d493d2b0

    LogoutInfo info3 = {"Virgo"};
    if(handler._logout(&info3) == 0)
        qDebug() <<"Logout success!";

    UserList allList(db), offlineList(db, 0), onlineList(db, 1);
    allList.printList();
    offlineList.printList();
    onlineList.printList();
    */

    Server *server = new Server(&a);

    QObject::connect(server, SIGNAL(_over()), &a, SLOT(quit()));

    QTimer::singleShot(0, server, SLOT(_init()));



    return a.exec();
}
