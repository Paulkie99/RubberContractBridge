#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent, quint16 port)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    bridgeServer = new Server("Bridge Server", QWebSocketServer::SecureMode, this);
    bridgeServer->listen(QHostAddress::Any, port);
    connect(bridgeServer, SIGNAL(messageReceived(QString)),
            this, SLOT(messageReceived(QString)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::messageReceived(const QString &message)
{
    ui->listWidget->addItem(message);
}



