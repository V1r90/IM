#include "MsgPackage.h"
#include "Database.h"


User::User(int _UID,
           QString _name,
           bool _status,
           QString _IP,
           QString _port):
    UID(_UID),
    name(_name),
    status(_status),
    IP(_IP),
    port(_port)
{

}

User::~User()
{

}

std::ostream& operator<< (std::ostream &out, const User &user)
{
    std::string _IP = "";
    if(!user.IP.isEmpty())
    {
        _IP = user.IP.toStdString() + ":" + user.port.toStdString();
    }

    out << "UID: " << user.UID << std::endl
        << "name: " << user.name.toStdString() << std::endl
        << "online status: " << user.status << std::endl
        << "IP: " << _IP << std::endl;

    return out;
}

QDebug operator<< (QDebug out, const User &user)
{
    QString _IP = "";
    if(!user.IP.isEmpty())
    {
        _IP = user.IP + ":" + user.port;
    }

    out << "UID: " << user.UID << endl
        << "name: " << qPrintable(user.name) << endl
        << "online status: " << user.status << endl
        << "IP: " << qPrintable(_IP) << endl;

    return out;
}

UserList::UserList(Database &_db, int _type):
    db(_db),
    type(_type)
{
    updateList();
}

UserList::~UserList()
{

}

void UserList::printList()
{
    switch(type)
    {
    case 0:
        std::cout << "Printing offline user list: "
                 << "\n------------------------------\n";
        break;
    case 1:
        std::cout << "Printing online user list: "
                 << "\n------------------------------\n";
        break;
    case -1:
        std::cout << "Printing all user list: "
                 << "\n------------------------------\n";
        break;
    }

    for(int i=0; i<list.size(); i++)
    {
        /*
        qDebug() << "UID: " << list[i].UID << "\n"
                 << "name: " << list[i].username << "\n"
                 << "online status: " << list[i].status << "\n"
                 << "IP: " << list[i].IP
                 << ":" << list[i].port
                 << "\n------------------------------\n";
        */
        std::cout << list[i]
                    << "\n------------------------------\n";
    }
}

void UserList::updateList(){
    QSqlQuery qry;
    QString str = "select UID,name,status,loginIP,loginPort from userinfo";
    if(!qry.exec(str))
    {
        qDebug() << "Failed to check the table to update: " << qry.lastError().text();
    }

    while(qry.next())
    {
        /*
        UserInfo tmp = {qry.value(0).toInt(),
                       qry.value(1).toChar(),
                       qry.value(2).toBool(),
                       qry.value(3).toChar(),
                       qry.value(4).toChar()};
        */
        int uid = qry.value(0).toInt();
        User tmp(qry.value(0).toInt(),
                 qry.value(1).toString(),
                 qry.value(2).toBool(),
                 qry.value(3).toString(),
                 qry.value(4).toString());
        if(uidList.indexOf(uid) == -1 && (type == -1 || qry.value(2).toInt() == type))
        {
            list.append(tmp);
            uidList.append(uid);
        }
    }
}
