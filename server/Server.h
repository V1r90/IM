#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "Database.h"
#include "MsgHandle.h"
#include "MsgPackage.h"

class Server : public QObject
{
    Q_OBJECT
private:
    Database *db;
    MsgHandle *handler;
    UserList *allList;
    UserList *offlineList;
    UserList *onlineList;

    QString IP;
    QString port;

    void __setOffline();
    void __checkUnsentMsg();
    void __timerReset();
    void __dispatchCommand(const QString &);
    void __showHelp();
    void __showAllUserList();
    void __showIP();
    void __getLocalIP(QString &);

public:
    explicit Server(QObject *parent = nullptr);
    //~Server();

public slots:
    void _init();
    void _listenCommand();

signals:
    void _over();

};

#endif // SERVER_H
