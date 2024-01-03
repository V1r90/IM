#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QObject>

QTcpServer *Server = nullptr;
QList<QTcpSocket*> Sockets;

QString ip = "192.168.175.128";
int MYPORT = 8888;

void sentMSGwoskt(QTcpSocket *skt);
void new_clients();
void read_client_data(QTcpSocket *Sockets);



#endif // SERVERSOCKET_H
