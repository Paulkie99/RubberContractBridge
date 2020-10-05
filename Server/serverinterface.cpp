#include "serverinterface.h"
#include "ui_dialog.h"

/*
 * Constructor for server interface, a port may be specified, default port is 159
 * */
ServerInterface::ServerInterface(QWidget *parent, quint16 port)
    : QDialog(parent)
    , ui(new Ui::Server_Dialog)
{
    ui->setupUi(this);
    bridgeServer = new Server("Bridge Server", QWebSocketServer::NonSecureMode, this);
    bridgeServer->listen(QHostAddress::Any, port);
    connect(bridgeServer, SIGNAL(messageReceived(QString)),
            this, SLOT(messageReceived(QString)));
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
