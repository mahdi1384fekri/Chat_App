#include "ClientChatWidget.h"
#include<QMessageBox>
#include "ui_ClientChatWidget.h"
#include<QDesktopServices>
ClientChatWidget::ClientChatWidget(QTcpSocket *client ,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientChatWidget)

{
    ui->setupUi(this);
    _client = new ClientManager(client, this);
    // connect(_client,&QTcpSocket::readyRead,this,&ClientChatWidget::dataReceived);
    // connect(_client,&QTcpSocket::disconnected,this,&ClientChatWidget::clientDisconnected);
    connect(_client,&ClientManager::disconnected,this,&ClientChatWidget::clientDisconnected);
    connect(_client,&ClientManager::textMessageReceived,this,&ClientChatWidget::textMessageReceived);
    connect(_client,&ClientManager::IsTyping,this,&ClientChatWidget::onTyping);
    connect(_client,&ClientManager::nameChanged,this,&ClientChatWidget::onClientNameChanged);
    connect(_client,&ClientManager::statusChanged,this,&ClientChatWidget::statusChanged);
    connect(_client,&ClientManager::initReceivingFile,this,&ClientChatWidget::oninitReceivingFile);
    //connect(_client,&ClientManager::rejectReceivingFile,this,&ClientChatWidget::onrejectReceivingFile);
    connect(_client,&ClientManager::fileSaved,this,&ClientChatWidget::onfileSaved);

    connect(ui->lnMessage,&QLineEdit::textChanged,_client,&ClientManager::sendIsTyping);

    dir.mkdir(_client->name());
    dir.setPath("./" +_client->name());
}

ClientChatWidget::~ClientChatWidget()
{
    delete ui;
}

void ClientChatWidget::disconnect()
{
    _client->disconnectFromHost();
}

// void ClientChatWidget::dataReceived()
// {
//     auto data = _client->readAll();
//     ui->lstMessages->addItem(data);
// }

void ClientChatWidget::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    //_client->write(ui->lnMessage->text().trimmed().toUtf8());//   به فرمت کیو بایت ارای به سکوت ارسال میکند
    _client->sendMessage(message);//
    ui->lnMessage->setText("");
    ui->lstMessages->addItem(message);
}

void ClientChatWidget::clientDisconnected()
{
    ui->wdgSend->setEnabled(false);
}

void ClientChatWidget::textMessageReceived(QString message,QString receiver)
{
    if(receiver == "Server"||receiver == "All"){
        ui->lstMessages->addItem(message);
    }
    if(receiver !="Server"){
        emit textForOtherClients(message,receiver,_client->name());
    }
}

void ClientChatWidget::onTyping()
{
    emit IsTyping(QString("%1 is typing...").arg(_client->name()));
}


void ClientChatWidget::on_lblOpenFolder_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(_client->name()));
}

void ClientChatWidget::oninitReceivingFile(QString clientname, QString filename, qint64 filesize)
{
    auto message = QString("Client(%1) wants to send a file. Do you want to accept it?\nFilename:%2\nFile Size:%3 bytes")
                       .arg(clientname,filename)
                       .arg(filesize);
    auto result = QMessageBox::question(this,"Recieving File",message);
    if(result==QMessageBox::Yes){
        _client->sendAcceptFile();

    }
    else{
        _client->sendRejectFile();
    }
}

void ClientChatWidget::onfileSaved(QString path)
{
    auto message = QString("file saved here:\n%1").arg(path);
    QMessageBox::information(this,"File saved",message);
}



void ClientChatWidget::onClientNameChanged(QString prevName,QString name)
{
    QFile::rename(dir.canonicalPath(),name);
    emit ClientNameChanged(prevName,name);
}

