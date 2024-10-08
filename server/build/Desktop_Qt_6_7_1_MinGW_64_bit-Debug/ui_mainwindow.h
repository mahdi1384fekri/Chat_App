/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *grpChats;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tbChats;
    QGroupBox *grpclients;
    QVBoxLayout *verticalLayout;
    QListWidget *lstClients;
    QPushButton *btnDisconnctAll;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        grpChats = new QGroupBox(centralwidget);
        grpChats->setObjectName("grpChats");
        verticalLayout_2 = new QVBoxLayout(grpChats);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tbChats = new QTabWidget(grpChats);
        tbChats->setObjectName("tbChats");
        tbChats->setTabsClosable(true);

        verticalLayout_2->addWidget(tbChats);


        horizontalLayout->addWidget(grpChats);

        grpclients = new QGroupBox(centralwidget);
        grpclients->setObjectName("grpclients");
        verticalLayout = new QVBoxLayout(grpclients);
        verticalLayout->setObjectName("verticalLayout");
        lstClients = new QListWidget(grpclients);
        lstClients->setObjectName("lstClients");

        verticalLayout->addWidget(lstClients);

        btnDisconnctAll = new QPushButton(grpclients);
        btnDisconnctAll->setObjectName("btnDisconnctAll");

        verticalLayout->addWidget(btnDisconnctAll);


        horizontalLayout->addWidget(grpclients);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tbChats->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Server", nullptr));
        grpChats->setWindowTitle(QCoreApplication::translate("MainWindow", "Server", nullptr));
        grpChats->setTitle(QCoreApplication::translate("MainWindow", "Chats", nullptr));
        grpclients->setTitle(QCoreApplication::translate("MainWindow", "Clients", nullptr));
        btnDisconnctAll->setText(QCoreApplication::translate("MainWindow", "Disconnect All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
