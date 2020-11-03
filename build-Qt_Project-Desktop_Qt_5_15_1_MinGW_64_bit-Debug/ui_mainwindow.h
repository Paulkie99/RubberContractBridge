/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *HomeScreen;
    QPushButton *pushButton_Join;
    QLabel *lblHeading;
    QPushButton *pushButton_Create;
    QLabel *lblUsername;
    QLineEdit *leditUsername;
    QWidget *JoinGame;
    QLabel *lblHostIP;
    QLabel *lblPort;
    QPushButton *pushButton_JoinServer;
    QSpinBox *sbPort;
    QLineEdit *leditHostIP;
    QCheckBox *cbShowPassword;
    QLineEdit *leditPassword;
    QLabel *lblPassword;
    QLabel *lblBackJoin;
    QPushButton *pushButton_BackJoin;
    QCheckBox *cbAI;
    QWidget *ConfigureServer;
    QLineEdit *leditCreatePassword;
    QLabel *lblCreatePassword;
    QLabel *lblAI;
    QSpinBox *sbAI;
    QLabel *label;
    QPushButton *pushButton_CreateConf;
    QLabel *lblBackConf;
    QPushButton *pushButton_BackConf;
    QMenuBar *menubar;
    QMenu *menuBridge;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(645, 474);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 0, 621, 411));
        HomeScreen = new QWidget();
        HomeScreen->setObjectName(QString::fromUtf8("HomeScreen"));
        pushButton_Join = new QPushButton(HomeScreen);
        pushButton_Join->setObjectName(QString::fromUtf8("pushButton_Join"));
        pushButton_Join->setGeometry(QRect(250, 190, 131, 51));
        QFont font;
        font.setPointSize(12);
        pushButton_Join->setFont(font);
        lblHeading = new QLabel(HomeScreen);
        lblHeading->setObjectName(QString::fromUtf8("lblHeading"));
        lblHeading->setGeometry(QRect(0, 20, 651, 81));
        QFont font1;
        font1.setPointSize(36);
        lblHeading->setFont(font1);
        pushButton_Create = new QPushButton(HomeScreen);
        pushButton_Create->setObjectName(QString::fromUtf8("pushButton_Create"));
        pushButton_Create->setGeometry(QRect(250, 240, 131, 51));
        pushButton_Create->setFont(font);
        lblUsername = new QLabel(HomeScreen);
        lblUsername->setObjectName(QString::fromUtf8("lblUsername"));
        lblUsername->setGeometry(QRect(0, 370, 130, 31));
        QFont font2;
        font2.setPointSize(14);
        lblUsername->setFont(font2);
        lblUsername->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        leditUsername = new QLineEdit(HomeScreen);
        leditUsername->setObjectName(QString::fromUtf8("leditUsername"));
        leditUsername->setGeometry(QRect(110, 378, 131, 31));
        stackedWidget->addWidget(HomeScreen);
        JoinGame = new QWidget();
        JoinGame->setObjectName(QString::fromUtf8("JoinGame"));
        lblHostIP = new QLabel(JoinGame);
        lblHostIP->setObjectName(QString::fromUtf8("lblHostIP"));
        lblHostIP->setGeometry(QRect(68, 129, 141, 41));
        QFont font3;
        font3.setPointSize(24);
        lblHostIP->setFont(font3);
        lblHostIP->setCursor(QCursor(Qt::ArrowCursor));
        lblPort = new QLabel(JoinGame);
        lblPort->setObjectName(QString::fromUtf8("lblPort"));
        lblPort->setGeometry(QRect(70, 160, 89, 41));
        lblPort->setFont(font3);
        lblPort->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_JoinServer = new QPushButton(JoinGame);
        pushButton_JoinServer->setObjectName(QString::fromUtf8("pushButton_JoinServer"));
        pushButton_JoinServer->setGeometry(QRect(200, 330, 171, 71));
        pushButton_JoinServer->setFont(font);
        sbPort = new QSpinBox(JoinGame);
        sbPort->setObjectName(QString::fromUtf8("sbPort"));
        sbPort->setGeometry(QRect(490, 170, 71, 31));
        QFont font4;
        font4.setPointSize(10);
        sbPort->setFont(font4);
        sbPort->setMaximum(10000);
        leditHostIP = new QLineEdit(JoinGame);
        leditHostIP->setObjectName(QString::fromUtf8("leditHostIP"));
        leditHostIP->setGeometry(QRect(410, 140, 151, 31));
        leditHostIP->setFont(font4);
        cbShowPassword = new QCheckBox(JoinGame);
        cbShowPassword->setObjectName(QString::fromUtf8("cbShowPassword"));
        cbShowPassword->setGeometry(QRect(70, 230, 141, 22));
        cbShowPassword->setFont(font4);
        leditPassword = new QLineEdit(JoinGame);
        leditPassword->setObjectName(QString::fromUtf8("leditPassword"));
        leditPassword->setGeometry(QRect(411, 200, 151, 29));
        leditPassword->setFont(font4);
        lblPassword = new QLabel(JoinGame);
        lblPassword->setObjectName(QString::fromUtf8("lblPassword"));
        lblPassword->setGeometry(QRect(70, 191, 301, 40));
        lblPassword->setFont(font3);
        lblPassword->setCursor(QCursor(Qt::ArrowCursor));
        lblBackJoin = new QLabel(JoinGame);
        lblBackJoin->setObjectName(QString::fromUtf8("lblBackJoin"));
        lblBackJoin->setGeometry(QRect(20, 10, 211, 21));
        QFont font5;
        font5.setPointSize(11);
        lblBackJoin->setFont(font5);
        lblBackJoin->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        pushButton_BackJoin = new QPushButton(JoinGame);
        pushButton_BackJoin->setObjectName(QString::fromUtf8("pushButton_BackJoin"));
        pushButton_BackJoin->setGeometry(QRect(0, 10, 31, 31));
        pushButton_BackJoin->setFont(font5);
        cbAI = new QCheckBox(JoinGame);
        cbAI->setObjectName(QString::fromUtf8("cbAI"));
        cbAI->setGeometry(QRect(70, 260, 141, 22));
        cbAI->setFont(font4);
        stackedWidget->addWidget(JoinGame);
        ConfigureServer = new QWidget();
        ConfigureServer->setObjectName(QString::fromUtf8("ConfigureServer"));
        leditCreatePassword = new QLineEdit(ConfigureServer);
        leditCreatePassword->setObjectName(QString::fromUtf8("leditCreatePassword"));
        leditCreatePassword->setGeometry(QRect(440, 160, 151, 31));
        leditCreatePassword->setFont(font4);
        lblCreatePassword = new QLabel(ConfigureServer);
        lblCreatePassword->setObjectName(QString::fromUtf8("lblCreatePassword"));
        lblCreatePassword->setGeometry(QRect(29, 140, 191, 61));
        lblCreatePassword->setFont(font3);
        lblCreatePassword->setCursor(QCursor(Qt::ArrowCursor));
        lblAI = new QLabel(ConfigureServer);
        lblAI->setObjectName(QString::fromUtf8("lblAI"));
        lblAI->setGeometry(QRect(30, 100, 401, 41));
        lblAI->setFont(font3);
        lblAI->setCursor(QCursor(Qt::ArrowCursor));
        sbAI = new QSpinBox(ConfigureServer);
        sbAI->setObjectName(QString::fromUtf8("sbAI"));
        sbAI->setGeometry(QRect(520, 110, 71, 31));
        sbAI->setFont(font4);
        sbAI->setMaximum(4);
        label = new QLabel(ConfigureServer);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 220, 431, 101));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        pushButton_CreateConf = new QPushButton(ConfigureServer);
        pushButton_CreateConf->setObjectName(QString::fromUtf8("pushButton_CreateConf"));
        pushButton_CreateConf->setGeometry(QRect(210, 330, 171, 71));
        pushButton_CreateConf->setFont(font);
        lblBackConf = new QLabel(ConfigureServer);
        lblBackConf->setObjectName(QString::fromUtf8("lblBackConf"));
        lblBackConf->setGeometry(QRect(20, 10, 211, 21));
        lblBackConf->setFont(font5);
        lblBackConf->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        pushButton_BackConf = new QPushButton(ConfigureServer);
        pushButton_BackConf->setObjectName(QString::fromUtf8("pushButton_BackConf"));
        pushButton_BackConf->setGeometry(QRect(0, 10, 31, 31));
        pushButton_BackConf->setFont(font5);
        stackedWidget->addWidget(ConfigureServer);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 645, 30));
        menuBridge = new QMenu(menubar);
        menuBridge->setObjectName(QString::fromUtf8("menuBridge"));
        menuBridge->setEnabled(true);
        menuBridge->setCursor(QCursor(Qt::BlankCursor));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuBridge->menuAction());

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Rubber Contract Bridge", nullptr));
        pushButton_Join->setText(QCoreApplication::translate("MainWindow", "Join Game", nullptr));
        lblHeading->setText(QCoreApplication::translate("MainWindow", "Rubber Contract Bridge", nullptr));
        pushButton_Create->setText(QCoreApplication::translate("MainWindow", "Create Game", nullptr));
        lblUsername->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        lblHostIP->setText(QCoreApplication::translate("MainWindow", "Host IP:", nullptr));
        lblPort->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        pushButton_JoinServer->setText(QCoreApplication::translate("MainWindow", "Join Game", nullptr));
        cbShowPassword->setText(QCoreApplication::translate("MainWindow", "Show Password", nullptr));
        lblPassword->setText(QCoreApplication::translate("MainWindow", "Server Password:", nullptr));
        lblBackJoin->setText(QCoreApplication::translate("MainWindow", "Back To Home Screen", nullptr));
        pushButton_BackJoin->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        cbAI->setText(QCoreApplication::translate("MainWindow", "AI only", nullptr));
        lblCreatePassword->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        lblAI->setText(QCoreApplication::translate("MainWindow", "Number of AI Players:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "To allow others to join, give them your IP address, port number & password (available on the next screen)", nullptr));
        pushButton_CreateConf->setText(QCoreApplication::translate("MainWindow", "Create Server", nullptr));
        lblBackConf->setText(QCoreApplication::translate("MainWindow", "Back To Home Screen", nullptr));
        pushButton_BackConf->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        menuBridge->setTitle(QCoreApplication::translate("MainWindow", "Home Screen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
