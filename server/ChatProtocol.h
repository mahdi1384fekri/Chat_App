#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QString>
#include <QByteArray>

class ChatProtocol
{
public:
    ChatProtocol();
    enum MessageType{
        Text,
        //File,
        IsTyping,
        SetName,
        SetStatus,
        InitSendingFile,
        AcceptSendingFile,
        RejectSendingFile,
        SendFile,
        ClientName,
        ConnectionACK,
        NewClient,
        ClientDisconnected
    };
    enum Status{
        None,
        Available,
        Busy,
        Away
    };

    QByteArray TextMessage(QString message,QString receiver);
    QByteArray IsTypingMessage();
    QByteArray SetNameMessage(QString Name);
    QByteArray SetStatusMessage(Status status);
    QByteArray SetInitSendingFileMessage(QString filename);
    QByteArray SetAcceptFileMessage();
    QByteArray SetRejectFileMessage();
    QByteArray SetFileMessage(QString filename);

    QByteArray setClientNameMessage(QString prevName,QString name);
    QByteArray setConnectionACKMessage(QString clientName,QStringList otherClient);
    QByteArray setNewClientMessage(QString clientName);
    QByteArray SetClientDisconnectedMessage(QString clientName);


    void loadDate(QByteArray data);


    QString message() const;

    QString name() const;

    Status status() const;

    MessageType type() const;

    QString filename() const;

    qint64 filesize() const;

    QByteArray filedata() const;

    QString receiver() const;

private:
    QByteArray getData(MessageType type,QString data);
    MessageType _type;
    QString _message;
    QString _name;
    Status _status;
    QString _filename;
    qint64 _filesize;
    QByteArray _filedata;
    QString _receiver;
};

#endif // CHATPROTOCOL_H
