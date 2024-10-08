#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H

#include "ClientManager.h"
#include <QDir>

#include <QWidget>
#include <QTcpSocket>
namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket* client ,QWidget *parent = nullptr);
    ~ClientChatWidget();
    void disconnect();

signals:
    void ClientNameChanged(QString prevName , QString name);
    void IsTyping(QString message);
    void statusChanged(ChatProtocol::Status status);
    void textForOtherClients(QString message,QString receiver , QString sender);

private slots:
   // void dataReceived();

    void on_btnSend_clicked();
    void clientDisconnected();
    void textMessageReceived(QString message, QString receiver);
    void onTyping();
    void on_lblOpenFolder_linkActivated(const QString &link);

    //void onrejectReceivingFile();
    void oninitReceivingFile(QString clientname, QString filename,qint64 filesize);
    void onfileSaved(QString path);

    void onClientNameChanged(QString prevName,QString name);
private:
    Ui::ClientChatWidget *ui;
    //QTcpSocket *_client;
    ClientManager *_client;
    QDir dir;
};

#endif // CLIENTCHATWIDGET_H
