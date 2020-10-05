#include "serverinterface.h"
#include "ui_dialog.h"

ServerInterface::ServerInterface(QWidget *parent, quint16 port)
    : QDialog(parent)
    , ui(new Ui::Server_Dialog)
{
    ui->setupUi(this);
    bridgeServer = new Server("Bridge Server", QWebSocketServer::SecureMode, this);
    bridgeServer->listen(QHostAddress::Any, port);
    connect(bridgeServer, SIGNAL(messageReceived(QString)),
            this, SLOT(messageReceived(QString)));
}

ServerInterface::~ServerInterface()
{
    delete ui;
}

void ServerInterface::messageReceived(const QString &message)
{
    ui->listWidget->addItem(message);
}
