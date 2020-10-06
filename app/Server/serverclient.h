//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the server for the bridge game of EPE321
//Author: Paul Claasen 18006885
//Last update: 06/10/2020 Revision 3

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
