#ifndef MSGHANDLE_H
#define MSGHANDLE_H

#include "Database.h"
#include "MsgPackage.h"

class MsgHandle
{
public:
    explicit MsgHandle(Database &);
    ~MsgHandle();

   int _register(RegisterInfo *info);
   int _login(LoginInfo *info);
   int _logout(LogoutInfo *info);
   int _message(MessageInfo *info);

    Database &db;
    PackageHead *head;

private:
    int __checkUserExist(QString username);
    int __checkUserStatus(QString username);
    int __checkUserPassword(QString username, QString password);
    int __messageForward(MessageInfo *info);
};


#endif // MSGHANDLE_H
