#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include"User.h"
#include"myclient.h"
#include<QList>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();
    void startServer();
    QByteArray fetchDataFromServer(QString type);

signals:
    void send_clinet_togamemanager(Myclient* client, QString username);

public slots:
    bool addclient(Myclient* client);
    void Answer_question_request(Myclient* client, QString type);
    void prosses_button(Myclient* player, QString command);
    void handleClientDisconnection();
    void sendEndGame(Myclient* client);

protected:
    void incomingConnection(qintptr socketDescriptor);    
private:
    User *users;
    QList<Myclient*> clients;
    Myclient* player1;
    Myclient* player2;
    void updateHistory(QString name1, QString name2);

    QString username1;
    QString username2;

};

#endif // SERVER_H
