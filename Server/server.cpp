//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the server for the bridge game of EPE321
//Author: Paul Claasen 18006885
//Last update: 05/10/2020 Revision 2

#include "server.h"

//path for Json temlpate files
const QString JPath = "../JFILES/";

//Constructor for the server, including server name, sslmode and parent object
Server::Server(const QString &serverName, SslMode secureMode, QObject *parent) : QWebSocketServer(serverName, secureMode, parent)
{
    qInfo() << "Constructing server";
    numConnectedClients = 0;
    connect(this, SIGNAL(newConnection()), //connect the QWebSocketServer::newConnection() signal to the acceptConnection() slot, to store connecting QWebSockets
            this, SLOT(acceptConnection()));

    //Initialise deck
    qInfo() << "Constructing deck";
    int count = 0;
    for(int suit = Clubs; suit <= Spades; suit++)
        for(int value = Two; value <= Ace; value++)
            Deck[count++] = Card(value, suit);
//    PrintDeck();
//    Shuffle();
//    PrintDeck();
//    Deal();
}

//Adapted from J Human's networking code
//This function is used to convert received messages to Json objects
QJsonObject Server::Convert_Message_To_Json(QString msg)
{
    qInfo() << "Converting message to Json: " << msg;
    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject jObject = d.object();
    return jObject;
}

//Adapted from J Human's networking code
//This function is used to generate messages of a specific type to be sent to clients
//Type string must match one of the files' names in JFILES folder
QString Server::GenerateMessage(QString type)
{
    QString val;
    QFile file;
    QString path = JPath; //this path needs to change to where the json files are stored
    path = path + type + ".json";   //full path is created here by passing in the parameter
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    qInfo() << "Generating message: " << val;
    return val;
}

// authenticate username and password of connecting client
void Server::Authenticate(QString username, QString password, int id)
{
    bool valid;

    //criteria for username and password?
    if(username != "" && password != "")
        valid = true;
    else
        valid = false;

    if(!valid)
    {
        QJsonObject error = Convert_Message_To_Json(GenerateMessage("AUTH_UNSUCCESSFUL"));
        error["Description"] = "Username/password invalid";
        SendMessage(id, error);
    }
    else //valid
    {
        ConnectedClients[id].isAuthenticated = true;
        SendMessage(id, Convert_Message_To_Json(GenerateMessage("AUTH_SUCCESSFUL")));
    }
}

// Shuffle the deck
void Server::Shuffle(unsigned seed)
{
    if(seed == 1) //seed not given (or just a really lame one)
        seed = std::chrono::system_clock::now().time_since_epoch().count();

    qInfo() << "Shuffling deck...";
    std::shuffle(Deck.begin(), Deck.end(), std::default_random_engine(seed));
}

// Deal the deck to connected players
void Server::Deal()
{
    //first assign cards one at a time
    int count = 0; //keep track of card in deck
    for(int card = 0; card < hand_size; ++card)
    {
        for(int player = 0; player < num_players; ++player)
        {
            Player_Hands[card][player] = &Deck[count++];
        }
    }

    //construct and send a message to each client with their cards
    for(int player = 0; player < num_players; ++player)
    {
        QJsonArray client_cards;
        for(int card = 0; card < hand_size; ++card)
        {
            Card* card_ptr = Player_Hands[card][player];
            auto card_to_int = QJsonObject({
                                               qMakePair(QString("Suit"), QJsonValue(card_ptr->suit)),
                                               qMakePair(QString("Value"), QJsonValue(card_ptr->value))
                                           });
            client_cards.push_back(card_to_int);
        }
        QJsonObject hand = Convert_Message_To_Json(GenerateMessage("HAND_DEALT"));
        hand["Cards"] = client_cards;
        SendMessage(player, hand);
    }

    PrintHands();
}

//Print every card in the deck
void Server::PrintDeck()
{
    QTextStream out(stdout);
    for(int card = 0; card < deck_size; card++)
    {
        Deck[card].print(out);
        out << "\n";
    }
}

//Print current player hands
void Server::PrintHands()
{
    QTextStream out(stdout);
    out << "North                       \t" << "South                       \t" << "East                        \t" << "West                        \n";
    for(int card = 0; card < hand_size; ++card)
    {
        for(int player = 0; player < num_players; ++player)
        {
            Player_Hands[card][player]->print(out);
            out << "\t";
        }
        out << "\n";
    }
}

//perform necessary functions to connect a client
void Server::ConnectClient(int pos)
{
    ConnectedClients[pos].clientSocket = nextPendingConnection(); //add the connecting QWebSocket
    ConnectedClients[pos].id = pos; //assign id based on pos in ConnectedClients array
    connect(ConnectedClients[pos].clientSocket, SIGNAL(textMessageReceived(QString)),
            this, SLOT(ValidateInput(QString))); //connect the connecting QWebSocket textMessageReceived function to the validateInput function

    QJsonObject success_msg = Convert_Message_To_Json(GenerateMessage("CONNECT_SUCCESSFUL"));
    SendMessage(pos, success_msg);
}

//send a message to a client based on id
void Server::SendMessage(int id, QJsonObject msg)
{
    msg["Id"] = id;
    QString strFromObj = QJsonDocument(msg).toJson(QJsonDocument::Compact);
    ConnectedClients[id].clientSocket->sendTextMessage(strFromObj);
}

//This function accepts a new connection by storing the corresponding QWebSocket in an array
void Server::acceptConnection()
{
    qInfo() << "Client connecting.";

    if(numConnectedClients == num_players) //client connecting, but max clients already connected
    {
        int id = 0;
        bool isFreeSpace = false;
        for(; id < num_players; id++)
        {
            if(!ConnectedClients[id].isAuthenticated) //if an unauthenticated client exists
            {
                //send a message to that client informing them of their disconnect
                QJsonObject unath = Convert_Message_To_Json(GenerateMessage("CONNECT_UNSUCCESSFUL"));
                unath["Description"] = "Authentication not received after connection, another client has replaced you";
                SendMessage(id, unath);

                ConnectClient(id); //replace that client with the new one
                isFreeSpace = true;
            }
        }
        if(!isFreeSpace)
        {
            QJsonObject lobbby_full = Convert_Message_To_Json(GenerateMessage("CONNECT_UNSUCCESSFUL"));
            SendMessage(100, lobbby_full);
        }
    }
    else
    {
    ConnectClient(numConnectedClients++);
    }
}

//This function receives messages from clients and calls the relevant validation function based on the message type
void Server::ValidateInput(QString message)
{
    emit messageReceived(message);
    QJsonObject msg = Convert_Message_To_Json(message);
    QString type = msg["Type"].toString();
    qInfo() << "Validating message: " << type;
     QStringList msgTypes;
     msgTypes << "CONNECT_REQUEST" << "BID_SEND" << "MOVE_SEND" << "PING" << "PONG" ;

     switch(msgTypes.indexOf(type))
     {
         case 0:
         {
            Authenticate(msg["Alias"].toString(), msg["Password"].toString(), msg["Id"].toInt());

           break;
         }
         case 1:
         {
             QJsonObject te = Convert_Message_To_Json(GenerateMessage("BID_END"));
                int iz = 5;
             SendMessage(iz, te);

           break;
         }
         case 2:

         break;

         case 3:

           break;

         case 4:

         break;
     }
}
