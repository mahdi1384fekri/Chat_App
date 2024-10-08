#include "ClientChatWidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newClientConnected(QTcpSocket *client)
{

    auto id = client->property("id").toInt();
    ui->lstClients->addItem(QString("New Client added: %1").arg(id));
    auto chatWidget = new ClientChatWidget(client);
    ui->tbChats->addTab(chatWidget,QString("Client(%1)").arg(id));

    connect(chatWidget,&ClientChatWidget::ClientNameChanged,this,&MainWindow::setClientName);
    connect(chatWidget,&ClientChatWidget::statusChanged,this,&MainWindow::setClientStatus);
    connect(chatWidget,&ClientChatWidget::IsTyping,[this](QString name){
        this->statusBar()->showMessage(name,750);
    });

    connect(chatWidget,&ClientChatWidget::textForOtherClients,_server , &ServerManager::ontextForOtherClients);



}

void MainWindow::clientDisconnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    ui->lstClients->addItem(QString(" Client Disconnected: %1").arg(id));

}

void MainWindow::setClientName(QString prevName, QString name)
{
    auto widget = qobject_cast<QWidget*>(sender());
    auto index = ui->tbChats->indexOf(widget);
    ui->tbChats->setTabText(index,name);
    _server->notifyOtherClients(prevName,name);
}

void MainWindow::setClientStatus(ChatProtocol::Status status)
{
    auto widget = qobject_cast<QWidget*>(sender());
    auto index = ui->tbChats->indexOf(widget);
    QString iconame = ":/image/";
    switch (status) {
    case ChatProtocol::Available:
        iconame.append("available.png");
        break;
    case ChatProtocol::Away:
        iconame.append("away.png");

        break;
    case ChatProtocol::Busy:
        iconame.append("busy.png");

        break;
    default:
        iconame = "";
        break;
    }
    auto icon = QIcon(iconame);
    ui->tbChats->setTabIcon(index,icon);


}

void MainWindow::setupServer()
{

    _server = new ServerManager();
     connect(_server,&ServerManager::newClientConnected,this,&MainWindow::newClientConnected);
    connect(_server,&ServerManager::clientDisconnected,this,&MainWindow::clientDisconnected);



}
//این اسلات همان دکمه بستن یک ویجت را انجا میدهد
//یعنی همان دکمه بستن
void MainWindow::on_tbChats_tabCloseRequested(int index)
{
    auto chatWidget =qobject_cast<ClientChatWidget *>( ui->tbChats->widget(index));
    chatWidget->disconnect();
    ui->tbChats->removeTab(index);
}

