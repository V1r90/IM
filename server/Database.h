#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QCoreApplication>

class Database{
public:
    Database();
    ~Database();
    QSqlDatabase db;
};

#endif // DATABASE_H
