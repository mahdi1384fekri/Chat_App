#include "ChatProtocol.h"
#include <QDataStream>
#include <QFileInfo>
#include <QIODevice>
#include <Qfile>
ChatProtocol::ChatProtocol()
{

}

QByteArray ChatProtocol::TextMessage(QString message,QString receiver)
{

    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);//برای خواندن و نوشتن به صورت باینری استفاده میوشد
    out.setVersion(QDataStream::Qt_6_0);
    out<<Text<<receiver<<message;

    return ba;
}

QByteArray ChatProtocol::IsTypingMessage()
{
    return getData(IsTyping,"");
}

QByteArray ChatProtocol::SetNameMessage(QString Name)
{
    return getData(SetName,Name);
}

QByteArray ChatProtocol::SetStatusMessage(Status status)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);//برای خواندن و نوشتن به صورت باینری استفاده میوشد
    out.setVersion(QDataStream::Qt_6_0);
    out<<SetStatus<<status;

    return ba;
}

QByteArray ChatProtocol::SetInitSendingFileMessage(QString filename)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);//برای خواندن و نوشتن به صورت باینری استفاده میوشد
    out.setVersion(QDataStream::Qt_6_0);
    QFileInfo info(filename);
    out<<InitSendingFile<<info.fileName()<<info.size();

    return ba;
}

QByteArray ChatProtocol::SetAcceptFileMessage()
{
    return getData(AcceptSendingFile,"");

}

QByteArray ChatProtocol::SetRejectFileMessage()
{
    return getData(RejectSendingFile,"");

}

QByteArray ChatProtocol::SetFileMessage(QString filename)
{
    QByteArray ba;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)){
        QDataStream out(&ba, QIODevice::WriteOnly);//برای خواندن و نوشتن به صورت باینری استفاده میوشد
        out.setVersion(QDataStream::Qt_6_0);
        QFileInfo info(filename);
        out<<SendFile<<info.fileName()<<info.size()<<file.readAll();
        file.close();
    }

    return ba;
}

void ChatProtocol::loadDate(QByteArray data)
{
    QDataStream in(&data,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);
    in>>_type;
    switch (_type) {
    case Text:
        in >>_receiver>> _message;
        break;
    case SetName:
        in >>_name;
        break;
    case SetStatus:
        in >> _status;
        break;

    case InitSendingFile:
        in >> _filename>>_filesize;
        break;
    case SendFile:
        in >> _filename>>_filesize>>_filedata;
        break;
    case ClientName:
        in>>_prevName>>_clientName;
        break;
        case NewClient:
    case ClientDisconnected:
        in >> _clientName;
        break;
    case ConnectionACK:
        in>>_myName>>_clientsNames;
        break;
    default:
        break;
    }

}

QByteArray ChatProtocol::getData(MessageType type, QString data)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out<<type<<data;

    return ba;
}

QStringList ChatProtocol::clientsNames() const
{
    return _clientsNames;
}

QString ChatProtocol::prevName() const
{
    return _prevName;
}

QString ChatProtocol::clientName() const
{
    return _clientName;
}

QString ChatProtocol::myName() const
{
    return _myName;
}

QString ChatProtocol::receiver() const
{
    return _receiver;
}

QByteArray ChatProtocol::filedata() const
{
    return _filedata;
}

qint64 ChatProtocol::filesize() const
{
    return _filesize;
}

QString ChatProtocol::filename() const
{
    return _filename;
}

ChatProtocol::MessageType ChatProtocol::type() const
{
    return _type;
}

ChatProtocol::Status ChatProtocol::status() const
{
    return _status;
}

QString ChatProtocol::name() const
{
    return _name;
}

QString ChatProtocol::message() const
{
    return _message;
}


