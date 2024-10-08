#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "ChatProtocol.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
class ClientManager : public QObject
{
    Q_OBJECT
public:
    explicit ClientManager(QHostAddress ip = QHostAddress::LocalHost,ushort port = 4500 ,QObject *parent = nullptr);
    void connecteToServer();
    void sendMessage(QString message , QString receiver);
    void sendName(QString name);
    void sendStatus(ChatProtocol::Status status);
    void sendIsTyping();

    void sendInitSendingFile(QString filename);
    void sendAcceptFile();
    void sendRejectFile();

signals:
    void connected();
    void disconnected();
   //void dataReceived(QByteArray data);
    void textMessageReceived(QString message);
    void IsTyping();
    void nameChanged(QString name);
    void statusChanged(ChatProtocol::Status status);
    void initReceivingFile(QString clientname, QString filename,qint64 filesize);
    void rejectReceivingFile();

    void connectionACK(QString myName,QStringList clientsName);
    void newClientConnectedToServer(QString clientName);
    void clientNameChanged(QString prevName,QString clientName);
    void clientDisconnected(QString clientName);

private://fields
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    ChatProtocol _protocol;
    QString _tmpFileName;
private://methods
    void sendFile();
private slots:
    void readyRead();

};

#endif // CLIENTMANAGER_H
