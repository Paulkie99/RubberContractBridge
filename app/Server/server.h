/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement the server for the bridge game of EPE321
 * Author: Paul Claasen 18006885
 * Last update: 06/10/2020 Revision 3*/

#ifndef SERVER_H
#define SERVER_H

#include <QWebSocketServer>

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <random>       // std::default_random_engine
#include <inputvalidator.h>
#include <gamestate.h>

class AI;               // AI Class to be integrated

class Server : public QWebSocketServer
{
    Q_OBJECT
public:
    explicit Server(const QString &serverName = "Bridge Server", SslMode secureMode = SecureMode, QObject *parent = NULL);
    friend class TestServer;
    friend class ServerInterface;
    friend class InputValidator;

    void Next_Bid();

    QJsonArray* Construct_Cards_Message(int player);
    int getTeamy(int otherTeamy);

    void Next_Move();

signals:
    void messageReceived(QString); //signal to the server-interface that a message has been received
    void messageSent(QString);

private:
    ServerClient ConnectedClients[num_players];
    AI* AI_Instances = NULL;
    Card* Player_Hands[hand_size][num_players];
    GameState  GS;
    InputValidator validator;

    bool shuffle = true;

    std::array<Card, deck_size> Deck;
    int numConnectedClients = 0;
    int numAuthenticatedUsers = 0;
    int numReady = 0;
    QStringList msgTypes;
    const QString JPath = "C:/Users/pj/Documents/Y3S2/EPE321/Project/group_e/app/JFILES/"; //path for Json temlpate files

    QString GenerateMessage(QString);
    QJsonObject Convert_Message_To_Json(QString);
    void Authenticate(QString username, QString password, int id);
    void Shuffle(unsigned seed = 1);
    void Deal(int dealer=-1);
    void PrintDeck();
    void PrintHands();
    void ConnectClient(int pos);
    void SendMessage(int id, QJsonObject);
    void BroadcastMessage(QJsonObject);
    void UpdateGameState(int card_val, int card_suit, bool isBid);
    Card* findCardInHand(int player, int val, int suit);

    void findHonors();

    void Score_Deal();

    Card* GetBestCardInTrick();

    void Update_Bid(int id, int value, int suit);

    void Update_Play();

private slots:
    void acceptConnection();
    void ValidateInput(QString message);
    void socketDisconnect(int);
};

#endif // SERVER_H
