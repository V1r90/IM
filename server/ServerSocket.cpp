#include"ServerSocket.h"



void new_clients()
{
    QTcpSocket *Socket = new QTcpSocket();

    qDebug()<<Socket;

    //Server与client连通进行通讯，返回socket
    Socket = Server->nextPendingConnection();

    QString ip = Socket->peerAddress().toString();
    qint16 port = Socket->peerPort();

    qDebug()<<"IP: "<<ip<<" Port: "<<port;
    QString tmp = QString("[%1:%2]:success connect").arg(ip).arg(port);

    //ui->textEdit_show->insertPlainText(tmp+"\n");

//    connect(Socket, &QTcpSocket::readyRead, NULL, [=](){
//        QByteArray msg = Socket->readAll();
//        QString str = msg.data();
//        qDebug()<<str;
//        Socket->write(msg);
//    });

//    connect(Socket, &QTcpSocket::disconnected, NULL, [=](){
//       Sockets.removeOne(Socket);
//       Socket->deleteLater();
//    });

    Sockets.append(Socket);

}

void read_client_data(QTcpSocket *Sockets)
{
    qDebug()<<Sockets;
}
