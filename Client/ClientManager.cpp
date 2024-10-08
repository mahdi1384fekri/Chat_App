#include "ClientManager.h"

ClientManager::ClientManager(QHostAddress ip ,ushort port  ,QObject *parent)
    : QObject{parent},
    _ip(ip),_port(port)
{

    _socket = new  QTcpSocket(this);
    connect(_socket,&QTcpSocket::connected,this,&ClientManager::connected);
    connect(_socket,&QTcpSocket::disconnected,this,&ClientManager::disconnected);
    connect(_socket,&QTcpSocket::readyRead,this,&ClientManager::readyRead);

}

void ClientManager::connecteToServer()
{
    _socket->connectToHost(_ip,_port);

}

void ClientManager::sendMessage(QString message, QString receiver)
{
    _socket->write(_protocol.TextMessage(message,receiver));

}

void ClientManager::sendName(QString name)
{
    _socket->write(_protocol.SetNameMessage(name));

}

void ClientManager::sendStatus(ChatProtocol::Status status)
{
    _socket->write(_protocol.SetStatusMessage(status));

}

void ClientManager::sendIsTyping()
{
    _socket->write(_protocol.IsTypingMessage());

}

void ClientManager::sendInitSendingFile(QString filename)
{
    _tmpFileName = filename;
    _socket->write(_protocol.SetInitSendingFileMessage(filename));

}

void ClientManager::sendAcceptFile()
{
    _socket->write(_protocol.SetAcceptFileMessage());

}

void ClientManager::sendRejectFile()
{
    _socket->write(_protocol.SetRejectFileMessage());

}

void ClientManager::sendFile()
{
    _socket->write(_protocol.SetFileMessage(_tmpFileName));

}

void ClientManager::readyRead()
{
    auto data = _socket->readAll();
   // emit dataReceived(data);
    _protocol.loadDate(data);
        switch (_protocol.type()) {
    case ChatProtocol::Text:
            emit textMessageReceived(_protocol.message());
        break;
    case ChatProtocol::SetName:
        emit nameChanged(_protocol.name());
        break;
    case ChatProtocol::SetStatus:
        emit statusChanged(_protocol.status());
        break;
    case ChatProtocol::IsTyping:
        emit IsTyping();
        break;
    case ChatProtocol::InitSendingFile:
        emit initReceivingFile(_protocol.name(),_protocol.filedata(),_protocol.filesize());
        break;
    case ChatProtocol::AcceptSendingFile:
         sendFile();
        break;
    case ChatProtocol::RejectSendingFile:
        emit rejectReceivingFile();
        break;
    case ChatProtocol::ConnectionACK:
        emit connectionACK(_protocol.myName(),_protocol.clientsNames());
        break;
    case ChatProtocol::NewClient:
        emit newClientConnectedToServer(_protocol.clientName());
        break;
    case ChatProtocol::ClientDisconnected:
        emit clientDisconnected(_protocol.clientName());
        break;
    case ChatProtocol::ClientName:
         emit clientNameChanged(_protocol.prevName(),_protocol.clientName());
         break;
    default:
        break;
    }

}
