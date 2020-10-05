#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QObject>
#include <QWebSocket>

class ServerClient : public QObject
{
    Q_OBJECT
public:
    ServerClient();
    ServerClient(const ServerClient &client) : QObject() {clientSocket = client.clientSocket; isAuthenticated = client.isAuthenticated; id = client.id;}

    QWebSocket* clientSocket = nullptr;
    bool isAuthenticated = false;
    int id = 100;

signals:
    void socketDisconnect(int);


private slots:
    void onDisconnect();

};

#endif // SERVERCLIENT_H
