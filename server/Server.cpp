#include "Server.h"
#include "User.h"
#include "myclient.h"


#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include<QByteArray>
#include <QJsonArray>

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    users=new User;
    player1 = nullptr;
    player2 = nullptr;
}

void Server::startServer()
{
    int port = 1234;

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }

}

QByteArray Server::fetchDataFromServer(QString type)
{

    qDebug() << "get question";

    QString Request = "https://questionbank.liara.run/api/TW9oYW1tYWRoYWRpIG5hamFyaSwgTW9oYW1tYWQgc2FkZWdoIGphZmFyaSw4NjBOdGdDWncxMU8/question?type=" + type;
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl(Request));

    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec(); // This will block and wait until the request is finished

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error: " << reply->errorString();
        delete reply;
        return QByteArray();
    }

    QByteArray responseData = reply->readAll();

    delete reply;
    return responseData;
}

bool Server::addclient(Myclient* player)
{
    if(player1==nullptr){
        player1=player;
        connect(player1,&Myclient::change_statebutton,this,&Server::prosses_button);
        username1 = player1->get_username();
        player2 = nullptr;
        return true;
    }
    else if(player2==nullptr){
        player2=player;
        connect(player2,&Myclient::change_statebutton,this,&Server::prosses_button);
        username2 = player2->get_username();

        // Notify player1 to start the game
        QString modifiedMessage = "command start " + player1->get_username() + " " + player2->get_username() + " X " + player1->get_username() + " ";
        player1->send_string(modifiedMessage);
        modifiedMessage = "command start " + player1->get_username() + " " + player2->get_username() + " O " + player2->get_username() + " ";
        player2->send_string(modifiedMessage);

        return true;
    }
    else{
        player->send_string("command full ");
        qDebug()<<"add extra player";
        return false;
    }
}

void Server::Answer_question_request(Myclient *client,QString type)
{
    QByteArray data=fetchDataFromServer(type);
    client->send_data(data);
}

void Server::prosses_button(Myclient *player, QString command)
{

    if (command == "win") {
        if (player == player1) {
            player1->send_string("command win ");
            player2->send_string("command lose ");
            users->updateHistory(username1, username2);
        }
        else {
            player1->send_string("command lose ");
            player2->send_string("command win ");
            users->updateHistory(username2, username1);
        }
        disconnect(player1,&Myclient::change_statebutton,this,&Server::prosses_button);
        disconnect(player2,&Myclient::change_statebutton,this,&Server::prosses_button);
        player1 = nullptr;
        player2 = nullptr;

        // return;
    } else if (command == "lose") {
        if (player == player1) {
            player2->send_string("command win ");
            player1->send_string("command lose ");
            users->updateHistory(username2, username1);
        }
        else {
            player1->send_string("command win ");
            player2->send_string("command lose ");
            users->updateHistory(username1, username2);
        }
        disconnect(player1,&Myclient::change_statebutton,this,&Server::prosses_button);
        disconnect(player2,&Myclient::change_statebutton,this,&Server::prosses_button);
        player1 = nullptr;
        player2 = nullptr;
        // return;
    }

    else {
        qDebug()<<"enter prosses button";
        if (player == player1)
        {
            command += " ";
            qDebug()<<"player1 send to player 2";
            player2->send_string(command);
            qDebug()<<command;
        }
        else if (player == player2)
        {
            command += " ";
            qDebug()<<"player1 send to player 2";

            player1->send_string(command);
            qDebug()<<command;
        }
        else {
            qDebug()<<"erorr prosses_button";
        }
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    Myclient *thread = new Myclient(socketDescriptor,users, this);
    clients.append(thread);
    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(clientDisconnected()), this, SLOT(handleClientDisconnection()));
    connect(thread, &Myclient::sendStartSignal, this, &Server::addclient);
    connect(thread, &Myclient::Request_question, this, &Server::Answer_question_request);
    connect(thread, &Myclient::endGame, this, &Server::sendEndGame);
    thread->start();

}


Server::~Server()
{
    delete users;
}

void Server::handleClientDisconnection()
{
    Myclient* client = qobject_cast<Myclient*>(sender()); // Get the client object that emitted the signal
    if(client)
    {
        if(client == player1)
        {
            player1 = nullptr;

            player2->send_string("command win ");
            player2 = nullptr;
        }
        else if(client == player2)
        {
            player2 = nullptr;
            player1->send_string("command win ");
            player1 = nullptr;
        }

        clients.removeOne(client); // Remove the client from the list
        client->deleteLater(); // Delete the client object
        delete client;
    }
}

void Server::sendEndGame(Myclient* client)
{
    if (client == player1) {
        player2->send_string("command win ");
        users->updateHistory(player2->get_username(), player1->get_username());
        player1 = nullptr;
        player2 = nullptr;

    }
    else if (client == player2) {
        player1->send_string("command win ");
        users->updateHistory(player1->get_username(), player2->get_username());
        player1 = nullptr;
        player2 = nullptr;
    }
    else {
        qDebug() << "nothing";
    }
}
