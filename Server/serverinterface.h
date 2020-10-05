#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include <QDialog>
#include <server.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Server_Dialog; }
QT_END_NAMESPACE

//class Server;

class ServerInterface : public QDialog
{
    Q_OBJECT

public:
    ServerInterface(QWidget *parent = nullptr, quint16 port = 159);
    ~ServerInterface();

private slots:
    void messageReceived(const QString &message);

private:
    Ui::Server_Dialog *ui;
    Server* bridgeServer;

};

#endif // SERVERINTERFACE_H
