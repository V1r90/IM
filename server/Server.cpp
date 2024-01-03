#include <QTimer>
#include <iostream>
#include <QtNetwork>

#include "Server.h"



Server::Server(QObject *parent):
    QObject(parent),
    db(new Database),
    handler(new MsgHandle(*db)),
    allList(new UserList(*db)),
    offlineList(new UserList(*db, 0)),
    onlineList(new UserList(*db, 1))
{

}

/* 以下是私有成员函数 */

void Server::__setOffline()
{
    QSqlQuery qry;
    QString str = "update userinfo set status=0, loginIP=NULL, loginPort=NULL";
    if(!qry.exec(str))
    {
        qDebug() << "Failed to update status: " << qry.lastError().text();
    }
}

void Server::__checkUnsentMsg()
{

}

void Server::__timerReset()
{
    std::cout << "-----------------------------" << std::endl;
    QTimer::singleShot(0, this, SLOT(_listenCommand()));
}

void Server::__showHelp()
{
    std::cout << "Here is the command list: " << std::endl
              << "'alluser': Print all the user registered in the server. " << std::endl
              << "'help': Show the command list. " << std::endl
              << "'quit': Terminate the server. " << std::endl
              << "'showip': Show the Server IP. " << std::endl;
}

void Server::__showAllUserList()
{
    allList->updateList();
    allList->printList();
}

void Server::__showIP()
{
    std::cout << "Server's IP: " << IP.toStdString() << std::endl;
}

void Server::__dispatchCommand(const QString &cmd)
{
    if("quit" == cmd)
    {
        __setOffline();
        _over();
        return;
    }
    else if("help" == cmd)
    {
        __showHelp();
        __timerReset();
    }
    else if("alluser" == cmd)
    {
        __showAllUserList();
        __timerReset();
    }
    else if("showip" == cmd)
    {
        __showIP();
        __timerReset();
    }
    else
    {
        std::cout << "Invalid command. Please enter again. "\
                     "(enter 'help' for help)" << std::endl;
        __timerReset();
    }
}

void  Server::__getLocalIP(QString &_IP)
{
    QList<QHostAddress> hostList = QNetworkInterface::allAddresses();
    foreach(QHostAddress address, hostList)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            _IP = address.toString();
        }
    }
}

/* 以上是私有成员函数 */
/* ----------------*/
/* 以下是公共成员函数 */

void Server::_init()
{
    std::cout << "Please enter the IP of Server (Default local IP address): ";

    if(std::cin.get() == '\n')
    {
        __getLocalIP(IP);
    }
    else
    {
        std::string _IP;
        std::cin >> _IP;
        IP = _IP.c_str();
    }
    std::cout << "Server initialized. " << std::endl;

    _listenCommand();
}

void Server::_listenCommand()
{
    std::cout << "Please enter the command: ";
    std::string cmd;
    std::cin >> cmd;

    __dispatchCommand(QString(cmd.c_str()));

}

/* 以上是公共成员函数 */
