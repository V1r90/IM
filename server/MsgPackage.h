#ifndef MSGPACKAGE_H
#define MSGPACKAGE_H

#include "Database.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <iostream>

#include <QVector>
#include <QString>
#include <QDateTime>
#include <QTextCodec>

//QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

typedef enum
{
    OK = 0,
    ERROR = -1,
    AGAIN = -2,
    EXIT = -3
}STATUS;

typedef enum
{
    REGISTER,
    LOGIN,
    LOGOUT,
}COMMAND;

typedef enum
{
    SUCCESS = INT_MIN,
    ERROR_QUERY_FAIL,
    ERROR_USER_NOT_EXIST,
    ERROR_USERNAME_ALREADY_REGISTER,
    ERROR_USER_ALREADY_LOGIN,
    ERROR_USER_PWD_WRONG,
    ERROR_USER_NOT_ONLINE
}ERROR_CODE;

typedef struct packageHead
{
    QString IP;
    QString port;
    int length;
    //int mode;
    int error;
    int command;
}PackageHead;

typedef struct registerInfo
{
    QString username;
    QString password;
    QString secureQues;
    QString secureAns;
}RegisterInfo;

typedef struct loginInfo
{
    char username[20];
    char password[256];
    char IP[15];
    char port[5];
}LoginInfo;

typedef struct logoutInfo
{
    char username[20];
}LogoutInfo;

typedef struct messageInfo
{
    QString sendName;
    QString recvName;
    QString content;
    QString time; // yyyy-MM-dd hh:mm:ss
}MessageInfo;


class User
{
private:
    int UID;
    QString name;
    bool status;
    QString IP;
    QString port;



public:
    User(int _UID=-1,
         QString _name=NULL,
         bool _status=false,
         QString _IP=NULL,
         QString _port=NULL);
    ~User();

    friend std::ostream& operator<< (std::ostream&, const User&);
    friend QDataStream& operator<< (QDataStream &, const User &);
    friend QDebug operator<< (QDebug, const User&);

};

class UserList
{
private:
    QVector<int> uidList;

public:
    //User *list;

    QVector<User> list;
    Database &db;
    int type; // 0: offline, 1: online, -1: all

    UserList(Database &_db,int _type=-1);
    ~UserList();

    void printList();
    void updateList();
};

#endif // MSGPACKAGE_H
