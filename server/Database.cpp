#include "Database.h"

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("server.db");

    //qDebug() << QCoreApplication::applicationDirPath();
    if(db.open())
    {
        qDebug() << "Database connected. ";
    }
    else
        qDebug() << "Failed to connect database: " << db.lastError().text();

    QSqlQuery qry(db);
    QString str = "create table if not exists userinfo( \
                    UID INTEGER PRIMARY KEY AUTOINCREMENT, \
                    name TEXT, \
                    password TEXT, \
                    status INTEGER DEFAULT 0, \
                    loginIP TEXT, \
                    loginPort, \
                    secureQuestion TEXT,\
                    secureAnswer TEXT)";

    if(!qry.exec(str))
    {
        qDebug() << "Failed to create table 'userinfo': " << qry.lastError().text();
    }
    else
    {
        qDebug() << "Table 'userinfo' created.";
    }

    str = "create table if not exists dialog( \
            UID INTEGER PRIMARY KEY AUTOINCREMENT, \
            sendName TEXT, \
            recvName TEXT, \
            content TEXT, \
            time TEXT, \
            status INTEGER DEFAULT 0)";
    if(!qry.exec(str))
    {
        qDebug() << "Failed to create table 'dialog': " << qry.lastError().text();
    }
    else
    {
        qDebug() << "Table 'dialog' created.";
    }
}

Database::~Database()
{
    db.close();
}
