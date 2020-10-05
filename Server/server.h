//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the server for the bridge game of EPE321
//Author: Paul Claasen 18006885
//Last update: 06/10/2020 Revision 3

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <card.h>       // for Deckk and Player_Hands
#include <random>       // std::default_random_engine
#include <serverclient.h>

class AI;               // AI Class to be integrated
struct GS{};            // Gamestate to be finalized
const int deck_size = 52;   // standard deck size
const int num_players = 4;  // bridge players
const int hand_size = deck_size/num_players;   // bridge hand size

enum players
{
    North,
    South,
    East,
    West
};

class Server : public QWebSocketServer
{
    Q_OBJECT
public:
    explicit Server(const QString &serverName = "Bridge Server", SslMode secureMode = SecureMode, QObject *parent = NULL);

signals:
    void messageReceived(QString); //signal to the server-interface that a message has been received

private:
    ServerClient ConnectedClients[num_players];
    AI* AI_Instances = NULL;
    Card* Player_Hands[hand_size][num_players];
    std::array<Card, deck_size> Deck;
    GS  GameState;
    int numConnectedClients = 0;
    int numAuthenticatedUsers = 0;

    QString GenerateMessage(QString);
    QJsonObject Convert_Message_To_Json(QString);
    void Authenticate(QString username, QString password, int id);
    void Shuffle(unsigned seed = 1);
    void Deal();
    void PrintDeck();
    void PrintHands();
    void ConnectClient(int pos);
    void SendMessage(int id, QJsonObject);
    bool isValidSocketId(int id, bool isFirstConnection=false);
    bool isValidBid(int id, int val, int suit);
    bool isValidMove(int id, int val, int suit);
    bool isEnumsContainCard(int val, int suit);
    bool isValidCardInHand(int id, int val, int suit);

private slots:
    void acceptConnection();
    void ValidateInput(QString message);
    void socketDisconnect(int);
};

#endif // SERVER_H
