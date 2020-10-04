//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the server for the bridge game of EPE321
//Author: Paul Claasen 18006885
//Last update: 04/10/2020 Revision 1

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <map>

class AI;
class Card;
struct GS
{

};

class Server : public QWebSocketServer
{
    Q_OBJECT
public:
    explicit Server(const QString &serverName, SslMode secureMode, QObject *parent);

signals:
    void messageReceived(QString);

private:
    QWebSocket** ConnectedClients = NULL;
    AI* AI_Instances;
    Card** Player_Hands;
    Card* Deck;
    GS  GameState;
    int connectedClients;
    std::map<std::string, int> message_types;

    QString GenerateMessage(QString);
    QJsonObject Convert_Message_To_Json(QString);
    bool Authenticate(QString username, QString password);

private slots:
    void acceptConnection();
    void ValidateInput(QString message);
};

#endif // SERVER_H
