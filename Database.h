#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Database: public QSqlDatabase{
    Q_OBJECT
public:
    explicit Database();
};

#endif // DATABASE_H
