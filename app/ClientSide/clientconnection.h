//Code used to implement the client side for the bridge game of EPE321
//Author: Jacques Human 18223916
//Last update: 05/10/2020
#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>




/*
 This header file shows the creation of the clientconnection class. This class servers as the medium through which the
 GUI and client side logic will communicate with the server. This class contains a constructor, private variables such as the
 connection url of the server, a websocket and a bollean value that enables a debug mode that prints messages.
 The class also contains important functions such as onConnected and onTextMessageReceived which is used to connect and
 communicate with the server.
 */

class clientconnection : public QObject
{
     Q_OBJECT
public:
    explicit clientconnection(const QUrl &url, bool debug = false, QObject *parent = nullptr);
    friend class TestServer;

private:
    QWebSocket* clientSocket;
    QUrl ConnectUrl;
    bool debugOn;
    int id;
    void SendMessageToServer(QString msg);
    QString GenerateMessage(QString type);
    QJsonObject CreateJObject(QString value);
    QString CreateJString(QJsonObject &jobj);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void closed();

signals:
    void messageReceived(QString message);
};

#endif // CLIENTCONNECTION_H
