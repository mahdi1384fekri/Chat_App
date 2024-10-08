/********************************************************************************
** Form generated from reading UI file 'ClientChatWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTCHATWIDGET_H
#define UI_CLIENTCHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientChatWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *lstMessages;
    QWidget *wdgSend;
    QHBoxLayout *horizontalLayout;
    QLabel *Messagelable;
    QLineEdit *lnMessage;
    QPushButton *btnSend;
    QLabel *lblOpenFolder;

    void setupUi(QWidget *ClientChatWidget)
    {
        if (ClientChatWidget->objectName().isEmpty())
            ClientChatWidget->setObjectName("ClientChatWidget");
        ClientChatWidget->resize(623, 454);
        verticalLayout_2 = new QVBoxLayout(ClientChatWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lstMessages = new QListWidget(ClientChatWidget);
        lstMessages->setObjectName("lstMessages");

        verticalLayout->addWidget(lstMessages);

        wdgSend = new QWidget(ClientChatWidget);
        wdgSend->setObjectName("wdgSend");
        horizontalLayout = new QHBoxLayout(wdgSend);
        horizontalLayout->setObjectName("horizontalLayout");
        Messagelable = new QLabel(wdgSend);
        Messagelable->setObjectName("Messagelable");

        horizontalLayout->addWidget(Messagelable);

        lnMessage = new QLineEdit(wdgSend);
        lnMessage->setObjectName("lnMessage");

        horizontalLayout->addWidget(lnMessage);

        btnSend = new QPushButton(wdgSend);
        btnSend->setObjectName("btnSend");

        horizontalLayout->addWidget(btnSend);

        lblOpenFolder = new QLabel(wdgSend);
        lblOpenFolder->setObjectName("lblOpenFolder");

        horizontalLayout->addWidget(lblOpenFolder);


        verticalLayout->addWidget(wdgSend);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ClientChatWidget);

        QMetaObject::connectSlotsByName(ClientChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ClientChatWidget)
    {
        ClientChatWidget->setWindowTitle(QCoreApplication::translate("ClientChatWidget", "Form", nullptr));
        Messagelable->setText(QCoreApplication::translate("ClientChatWidget", "Message:", nullptr));
        btnSend->setText(QCoreApplication::translate("ClientChatWidget", "Send", nullptr));
        lblOpenFolder->setText(QCoreApplication::translate("ClientChatWidget", "<html><head/><body><p><a href=\"#\"><span style=\" text-decoration: underline; color:#007af4;\">Open</span></a></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientChatWidget: public Ui_ClientChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTCHATWIDGET_H
