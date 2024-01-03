#include "Database.h"
#include "MsgHandle.h"
#include "MsgPackage.h"

MsgHandle::MsgHandle(Database &_db):
    db(_db)
{

}

MsgHandle::~MsgHandle()
{

}

int MsgHandle::__checkUserExist(QString username)
{
    QSqlQuery qry;
    QString str = "select * from userinfo where name=:name";
    qry.prepare(str);
    qry.bindValue(":name", username);

    if(!qry.exec())
    {
        qDebug() << "Failed to check the table: " << qry.lastError().text();
        return ERROR_QUERY_FAIL;
    }
    else if(qry.first())
    {
        qDebug() << "Username already registered! ";
        return ERROR_USERNAME_ALREADY_REGISTER;
    }
    else
    {
        return SUCCESS;
    }
}

int MsgHandle::__checkUserStatus(QString username)
{
    QSqlQuery qry;
    QString str = "select status from userinfo where name=:name";
    qry.prepare(str);
    qry.bindValue(":name", username);

    if(!qry.exec())
    {
        qDebug() << "Failed to check the table: " << qry.lastError().text();
        return ERROR_QUERY_FAIL;
    }
    else if(qry.first())
    {
        return qry.value(0).toInt();
    }
    else
    {
        qDebug() << "User not exist! ";
        return ERROR_USER_NOT_EXIST;
    }
}

int MsgHandle::__checkUserPassword(QString username, QString password)
{
    QSqlQuery qry;
    QString str = "select * from userinfo where name=:name and\
                    password=:password";
    qry.prepare(str);
    qry.bindValue(":name", username);
    qry.bindValue(":password", password);

    if(!qry.exec())
    {
        qDebug() << "Failed to check the table: " << qry.lastError().text();
        return ERROR_QUERY_FAIL;
    }
    else if(qry.first())
    {
        return SUCCESS;
    }
    else
    {
        qDebug() << "Password wrong! ";
        return ERROR_USER_PWD_WRONG;
    }
}

/* not done*/
int MsgHandle::__messageForward(MessageInfo *info)
{
    return 1;
}



int MsgHandle::_register(RegisterInfo *info)
{
    int result = __checkUserExist(info->username);
    if(result != SUCCESS)
    {
        return result;
    }

    qDebug() << "Registering...";
    QSqlQuery qry;
    QString addUser = "insert into userinfo(\
                        name, \
                        password, \
                        secureQuestion, \
                        secureAnswer) values(\
                        :name, \
                        :password, \
                        :Q, \
                        :A)";
    qry.prepare(addUser);
    qry.bindValue(":name", info->username);
    qry.bindValue(":password", info->password);
    qry.bindValue(":Q", info->secureQues);
    qry.bindValue(":A", info->secureAns);

    if(!qry.exec())
    {
        qDebug() << "Failed to insert: " << qry.lastError().text();
        return ERROR_QUERY_FAIL;
    }

    return SUCCESS;
}

int MsgHandle::_login(LoginInfo *info)
{
    int result = __checkUserStatus(info->username);
    if(result < 0)
    {
        return result;
    }
    else if(result == 1)
    {
        qDebug() << "User already login!";
        return ERROR_USER_ALREADY_LOGIN;
    }

    result = __checkUserPassword(info->username, info->password);
    if(result != SUCCESS)
    {
        return result;
    }
    QSqlQuery qry;
    QString userLogin = "update userinfo set status=1,loginIP=:IP, loginPort=:port \
                        where name=:name";
    qry.prepare(userLogin);
    qry.bindValue(":IP", info->IP);
    qry.bindValue(":port", info->port);
    qry.bindValue(":name", info->username);

    if(!qry.exec())
    {
        qDebug() << "Failed to update: " << qry.lastError().text();
        return ERROR_QUERY_FAIL;
    }

    return SUCCESS;
}

int MsgHandle::_logout(LogoutInfo *info)
{
    int result = __checkUserStatus(info->username);
    if(result == 0)
    {
        return ERROR_USER_NOT_ONLINE;
    }
    else if(result < 0)
    {
        return result;
    }

    QSqlQuery qry;
    QString userLogin = "update userinfo set status=0,loginIP=NULL, loginPort=NULL \
                        where name=:name";
    qry.prepare(userLogin);
    qry.bindValue(":name", info->username);

    if(!qry.exec())
    {
        qDebug() << "Failed to update 'userinfo': " << qry.lastError().text();
        return ERROR_QUERY_FAIL;
    }

    return SUCCESS;
}

int MsgHandle::_message(MessageInfo *info)
{
    QSqlQuery qry;
    QString str = "insert into dialog (\
                    sendName, \
                    recvName, \
                    content, \
                    time) values(\
                    :sendName, \
                    :recvName, \
                    :content, \
                    :time)";

    qry.prepare(str);
    qry.bindValue(":sendName", info->sendName);
    qry.bindValue(":recvName", info->recvName);
    qry.bindValue(":content", info->content);
    qry.bindValue(":time", info->time);

    if(!qry.exec())
    {
        qDebug() << "Failed to insert 'dialog': " << qry.lastError().text();
        return ERROR_QUERY_FAIL;
    }


    if(__checkUserStatus(info->recvName) == 1)
    {
        str = "update dialog set status=1 where UID in (\
                select seq from sqlite_sequence where name='dialog') ";
        if(!qry.exec())
        {
            qDebug() << "Failed to update 'dialog': " << qry.lastError().text();
            return ERROR_QUERY_FAIL;
        }
        __messageForward(info);
    }
    return SUCCESS;
}
