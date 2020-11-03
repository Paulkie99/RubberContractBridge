/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement a server interface
 * Author: Paul Claasen 18006885
 * Last update: 06/10/2020 Revision 3*/

#include "serverinterface.h"
#include "ui_dialog.h"

/*
 * Constructor for server interface, a port may be specified, default port is 159. Can also be specified whether the created server should shuffle its deck on creation.
 * */
ServerInterface::ServerInterface(QWidget *parent, quint16 port, bool secure)
    : QDialog(parent)
    , ui(new Ui::Server_Dialog)
{
    ui->setupUi(this);
    bridgeServer = new Server("Bridge Server", secure ? QWebSocketServer::SecureMode : QWebSocketServer::NonSecureMode, this);
    if(secure)
    {
        QSslConfiguration conf;
        QSslKey key;
        QSslCertificate cert;
        QFile certFile(QStringLiteral(":/localhost.cert"));
        QFile keyFile(QStringLiteral(":/localhost.key"));
        certFile.open(QIODevice::ReadOnly);
        keyFile.open(QIODevice::ReadOnly);
        cert = QSslCertificate(&certFile, QSsl::Pem);
        key = QSslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
        certFile.close();
        keyFile.close();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1_0);
        conf.setLocalCertificate(cert);
        conf.setPrivateKey(key);
        bridgeServer->setSslConfiguration(conf);
    }
    if(bridgeServer->listen(QHostAddress::Any, port))
    {
        connect(bridgeServer, SIGNAL(messageReceived(QString)),
                this, SLOT(messageReceived(QString)));
        connect(bridgeServer, SIGNAL(messageSent(QString)),
                this, SLOT(messageSent(QString)));
        connect(bridgeServer, SIGNAL(Info(QString)),
                this, SLOT(Info(QString)));
        Info("Server listening on port: " + QString::number(port));
    }
}

/*
 * Destructor for server interface, only ui needs to be deleted
 * */
ServerInterface::~ServerInterface()
{
    delete ui;
}

/*
 * Slot connected to the server object's messageReceived signal, which passes a message received from the client to the interface
 * */
void ServerInterface::messageReceived(const QString &message)
{
    ui->listWidget->addItem("Message received: " + message); // add an item to the list widget so that the message may be displayed
}

void ServerInterface::messageSent(const QString &message)
{
    ui->listWidget->addItem("Message sent: " + message); // add an item to the list widget so that the message may be displayed
}

void ServerInterface::Info(const QString &message)
{
    ui->listWidget->addItem("Info: " + message); // add an item to the list widget so that the message may be displayed
}
