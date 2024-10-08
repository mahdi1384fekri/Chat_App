#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupClient();

    ui->centralwidget->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupClient()
{
    _client = new ClientManager();
    connect(_client,&ClientManager::connected,[this] (){
        ui->centralwidget->setEnabled(true);
    });
    connect(_client,&ClientManager::disconnected,[this] (){
        ui->centralwidget->setEnabled(false);
    });
    connect(_client,&ClientManager::textMessageReceived,this,&MainWindow::dataRecieved);
    // connect(_client,&ClientManager::nameChanged,this,&MainWindow::setWindowTitle);
    connect(_client,&ClientManager::IsTyping,this,&MainWindow::onTyping);
    connect(_client,&ClientManager::initReceivingFile,this,&MainWindow::oninitReceivingFile);
    connect(_client,&ClientManager::rejectReceivingFile,this,&MainWindow::onrejectReceivingFile);

    connect(ui->lnMessage,&QLineEdit::textChanged,_client,&ClientManager::sendIsTyping);
    connect(_client,&ClientManager::connectionACK,this,&MainWindow::onConnectionACK);
    connect(_client,&ClientManager::newClientConnectedToServer,this,&MainWindow::onNewClientConnectedToServer);
    connect(_client,&ClientManager::clientDisconnected,this,&MainWindow::onClientDisconnected);
    connect(_client,&ClientManager::clientNameChanged,this,&MainWindow::onClientNameChanged);

}

void MainWindow::on_actionConnect_triggered()
{
     _client->connecteToServer();

}

void MainWindow::dataRecieved(QString message)
{
    //ui->lstMessages->addItem(data);
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMessages->addItem(listItemWidget);
    listItemWidget->setBackground(QColor(200, 200, 200));
    ui->lstMessages->setItemWidget(listItemWidget,chatWidget);
}


void MainWindow::on_btnSend_clicked()
{
    auto message =ui->lnMessage->text().trimmed();
    _client->sendMessage(message,ui->cmbDistination->currentText());
    //ui->lstMessages->addItem(message);
    ui->lnMessage->setText("");
     ui->lnMessage->setFocus();
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message,true);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMessages->addItem(listItemWidget);
    listItemWidget->setBackground(QColor(0, 255, 255));
    ui->lstMessages->setItemWidget(listItemWidget,chatWidget);
}


void MainWindow::on_lnClientName_editingFinished()
{
    auto name = ui->lnClientName->text().trimmed();
    _client->sendName(name);

}


void MainWindow::on_cmbStatus_currentIndexChanged(int index)
{
    auto status = (ChatProtocol::Status)index;
    _client->sendStatus(status);
}

void MainWindow::onTyping()
{
    statusBar()->showMessage("Server is typing...",750);
}


void MainWindow::on_btnSendFile_clicked()
{

   auto fileName =  QFileDialog::getOpenFileName(this,"Select a file","/home");
    _client->sendInitSendingFile(fileName);

}

void MainWindow::onrejectReceivingFile()
{
    QMessageBox::critical(this,"Sending File","Operation rejected..");
}

void MainWindow::oninitReceivingFile(QString clientname, QString filename, qint64 filesize)
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

void MainWindow::onConnectionACK(QString myName, QStringList clientsName)
{
    ui->cmbDistination->clear();
    clientsName.prepend("All");
    clientsName.prepend("Server");
    foreach (auto client, clientsName) {
        ui->cmbDistination->addItem(client);
    }
    setWindowTitle(myName);
}

void MainWindow::onNewClientConnectedToServer(QString clientName)
{
    ui->cmbDistination->addItem(clientName);
}

void MainWindow::onClientNameChanged(QString prevName, QString clientName)
{
    for (int i = 0; i < ui->cmbDistination->count(); ++i) {
        if(ui->cmbDistination->itemText(i) == prevName ){
            ui->cmbDistination->setItemText(i,clientName);
            return;
        }
    }
}

void MainWindow::onClientDisconnected(QString clientName)
{
    for (int i = 0; i < ui->cmbDistination->count(); ++i) {
        if(ui->cmbDistination->itemText(i) == clientName ){
            ui->cmbDistination->removeItem(i);
            return;
        }
    }
}

