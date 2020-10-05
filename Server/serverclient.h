#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QObject>
#include <QWebSocket>

class ServerClient : public QObject
{
public:
    ServerClient();
    ServerClient(const ServerClient &client) : QObject() {clientSocket = client.clientSocket; isAuthenticated = client.isAuthenticated; id = client.id;}
    QWebSocket* clientSocket = NULL;
    bool isAuthenticated = false;
    int id = 100;
};

#endif // SERVERCLIENT_H
