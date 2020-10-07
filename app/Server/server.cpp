/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement the server for the bridge game of EPE321
 * Author: Paul Claasen 18006885
 * Last update: 06/10/2020 Revision 3*/

#include "server.h"

//path for Json temlpate files
const QString JPath = "../JFILES/";

/*
 * Constructor for the server, including server name, sslmode and parent object. Also can be specified whether shuffle should be called on construction, which is useful for testing.
 * */
Server::Server(const QString &serverName, SslMode secureMode, QObject *parent, bool shuffle) : QWebSocketServer(serverName, secureMode, parent)
{
    qInfo() << "Constructing server";
    connect(this, SIGNAL(newConnection()), //connect the QWebSocketServer::newConnection() signal to the acceptConnection() slot, to store connecting QWebSockets
            this, SLOT(acceptConnection()));

    for(int i = 0; i < num_players; ++i) //connect the socketDisconnect signal of every instance of ServerClient in the ConnectedClients array to the server's socketDisconnect slot
        connect(&ConnectedClients[i], SIGNAL(socketDisconnect(int)),
                this, SLOT(socketDisconnect(int)));

    //Initialise deck
    qInfo() << "Constructing deck";
    int count = 0;
    for(int suit = Clubs; suit <= Spades; suit++)   // step through the values of the card value and suit enums and add each combination to the deck
        for(int value = Two; value <= Ace; value++)
            Deck[count++] = Card(value, suit);
//    PrintDeck();
    if(shuffle)
        Shuffle();
//    PrintDeck();
//    Deal();

    //Initialise Player_Hands entries to NULL
    for(int card = 0; card < hand_size; ++card)
    {
        for(int player = 0; player < num_players; ++player) // iterate column (player) first, then row
        {
            Player_Hands[card][player] = NULL;
        }
    }
}

/*
 * Adapted from J Human's networking code
 * This function is used to convert received messages to Json objects
 * */
QJsonObject Server::Convert_Message_To_Json(QString msg)
{
//    qInfo() << "Converting message to Json: " << msg;
    QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject jObject = d.object();
    return jObject;
}

/*
 * Adapted from J Human's networking code
 * This function is used to generate messages of a specific type to be sent to clients
 * Type string must match one of the files' names in JFILES folder
 * */
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
//    qInfo() << "Generating message: " << val;
    return val;
}

/*
 * Authenticate username and password of connecting client
 * */
void Server::Authenticate(QString username, QString password, int id)
{
    qInfo() << "Authenticating " << username << ", " << password;

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

        if(isValidSocketId(id)) // send a message only if the received id is in range and has a non-null websocket
            SendMessage(id, error);
    }
    else //valid
    {
        if(isValidSocketId(id))
        {
            ++numAuthenticatedUsers;
            ConnectedClients[id].isAuthenticated = true;
            SendMessage(id, Convert_Message_To_Json(GenerateMessage("AUTH_SUCCESSFUL")));
        }

        if(numAuthenticatedUsers == num_players) // Four users are connected and authenticated, the game may commence.
            Deal();
    }
}

/*
 * Shuffle the deck
 * */
void Server::Shuffle(unsigned seed)
{
    if(seed == 1) //seed not given (or just a really lame one)
        seed = std::chrono::system_clock::now().time_since_epoch().count();

    qInfo() << "Shuffling deck...";
    std::shuffle(Deck.begin(), Deck.end(), std::default_random_engine(seed));
}

/*
 * Deal the deck to connected players
 * */
void Server::Deal()
{
    //first assign cards one at a time to each player
    int count = 0; //keep track of card in deck
    for(int card = 0; card < hand_size; ++card)
    {
        for(int player = 0; player < num_players; ++player) // iterate column (player) first, then row
        {
            Player_Hands[card][player] = &Deck[count++];
        }
    }

    //construct and send a message to each client with their cards
    for(int player = 0; player < num_players; ++player)
    {
        QJsonArray client_cards;
        for(int card = 0; card < hand_size; ++card) // iterate row (card) first, then column
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
        if(isValidSocketId(player))
            SendMessage(player, hand);
    }

    PrintHands();
}

/*
 * Print every card in the deck
 * */
void Server::PrintDeck()
{
    QTextStream out(stdout);
    for(int card = 0; card < deck_size; card++)
    {
        Deck[card].print(out);
        out << "\n";
    }
}

/*
 * Print current player hands
 * */
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

/*
 * Perform necessary functions to connect a client to a specified position in the ConnectedClients array, the relevant signals and slots are also connected
 * */
void Server::ConnectClient(int pos)
{
    if(!isValidSocketId(pos, true))
    {
        qWarning() << "Tried to connect invalid id: " << pos;
        return;
    }

    ConnectedClients[pos].clientSocket = nextPendingConnection(); //add the connecting QWebSocket
    ConnectedClients[pos].id = pos; //assign id based on pos in ConnectedClients array

    connect(ConnectedClients[pos].clientSocket, SIGNAL(textMessageReceived(QString)),
            this, SLOT(ValidateInput(QString))); //connect the connecting QWebSocket textMessageReceived function to the validateInput function

    connect(ConnectedClients[pos].clientSocket, SIGNAL(aboutToClose()),
            &ConnectedClients[pos], SLOT(onDisconnect())); //connect the QWebSocket's aboutToClose() signal to the ServerClient object's onDisconnect slot

    QJsonObject success_msg = Convert_Message_To_Json(GenerateMessage("CONNECT_SUCCESSFUL"));
    SendMessage(pos, success_msg);
}

/*
 * Send a message to a client based on id
 **/
void Server::SendMessage(int id, QJsonObject msg)
{
    if(!isValidSocketId(id))
        return;

    msg["Id"] = id;
    QString strFromObj = QJsonDocument(msg).toJson(QJsonDocument::Compact);

    qInfo() << "Sending message: " << strFromObj;

    emit messageSent(strFromObj);
    ConnectedClients[id].clientSocket->sendTextMessage(strFromObj);
}

/*
 * This function checks if the given id is in range, and if the websocket at the specified id is non-null
 * */
bool Server::isValidSocketId(int id, bool isFirstConnection)
{
    if(isFirstConnection)
    {
        if(0 <= id && id < num_players)
            return true;
    }
    else if(0 <= id && id < num_players && ConnectedClients[id].clientSocket)
            return true;

    qWarning() << "Invalid socket id: " << id;
    return false;
}

/*
 * Function used to validate a bid
 * */
bool Server::isValidBid(int id, int val, int suit)
{
    if(!isValidSocketId(id))
        return false;

    if(!isEnumsContainCard(val, suit))
        return false;

    //TODO: Add validation logic based on GS (last bid, number of passes, etc)

    //else
    return true;
}

/*
 * Function used to validate a move (played card)
 * */
bool Server::isValidMove(int id, int val, int suit)
{
    if(!isValidCardInHand(id, val, suit))
        return false;

    //TODO: Add validation logic based on GS (trump card, lead suit, etc)

    //else
    return true;
}

/*
 * Function to check whether card values are valid
 * */
bool Server::isEnumsContainCard(int val, int suit)
{
    if(val > Ace || val < Two) // check if the value is within the values enum
        return false;

    if(suit > Spades || suit < Clubs) // check if the suit is within the suits enum
        return false;

    //else
    return true;
}

/*
 * Function to check whether the given card is in the given player's (specified by id) hand
 * */
bool Server::isValidCardInHand(int id, int val, int suit)
{
    if(!isValidSocketId(id))
        return false;

    if(!isEnumsContainCard(val, suit))
        return false;

    bool found = false;
    int player = id;
    for(int card = 0; card <= Ace; ++card)
    {
        if(Player_Hands[card][player])
            if(Player_Hands[card][player]->value == val)
                if(Player_Hands[card][player]->suit == suit)
                    return true;
    }
    return found;
}

/*
 * This function accepts a new connection by storing the corresponding QWebSocket in an array,
 * it also handles the case of a full lobby with a new pending connection attempt
 * */
void Server::acceptConnection()
{

    if(numConnectedClients == num_players) //client connecting, but max clients already connected
    {
        int id = 0;
        bool isFreeSpace = false;
        for(; id < num_players; id++)
        {
            if(ConnectedClients[id].clientSocket == NULL && !isFreeSpace) //if a serverclient without a connected websocket exists
            {
                qInfo() << "Client" << id << "connecting.";
                ConnectClient(id); //connect connecting websocket to the serverclient
                isFreeSpace = true;
            }
            else if(!ConnectedClients[id].isAuthenticated && !isFreeSpace) //if an unauthenticated client exists
            {
                //send a message to that client informing them of their disconnect
                QJsonObject unath = Convert_Message_To_Json(GenerateMessage("CONNECT_UNSUCCESSFUL"));
                unath["Description"] = "Authentication not received after connection, another client has replaced you";
                SendMessage(id, unath);
                ConnectedClients[id].clientSocket->close();

                qInfo() << "Client" << id << "connecting.";
                ConnectClient(id); //replace that client with the new one
                isFreeSpace = true;
            }
        }
        if(!isFreeSpace) // Lobby is full and everyone is authenticated
        {
            nextPendingConnection()->sendTextMessage(GenerateMessage("CONNECT_UNSUCCESSFUL"));
        }
    }
    else
    {
        qInfo() << "Client" << numConnectedClients << "connecting.";
        ConnectClient(numConnectedClients++);
    }
}

/*
 * This function receives messages from clients and calls the relevant validation function based on the message type
 * */
void Server::ValidateInput(QString message)
{
     emit messageReceived(message); // add message to ui listwidget

     QJsonObject msg = Convert_Message_To_Json(message); // convert message string to Json
     QString type = msg["Type"].toString(); // get type of message

     qInfo() << "Validating message: " << type;

     QStringList msgTypes;
     msgTypes << "CONNECT_REQUEST" << "BID_SEND" << "MOVE_SEND" << "PING" << "PONG" << "DISCONNECT_PLAYER"; // Messages the server might receive

     switch(msgTypes.indexOf(type))
     {
         case 0: // CONNECT_REQUEST
         {
           Authenticate(msg["Alias"].toString(), msg["Password"].toString(), msg["Id"].toInt());
         }
         break;

         case 1: // BID_SEND
         {
            QJsonObject card = msg["Bid"].toObject();
            bool valid = isValidBid(msg["Id"].toInt(), card["Rank"].toInt(), card["Suit"].toInt());

            if(valid)
                //TODO: Update GS based on bid
                qInfo() << "Bid Valid";
            emit messageReceived("Bid received");
         }
         break;

         case 2: // MOVE_SEND
         {
            QJsonObject card = msg["Move"].toObject();
            bool valid = isValidMove(msg["Id"].toInt(), card["Rank"].toInt(), card["Suit"].toInt());

            if(valid)
                //TODO: Update GS based on move
                qInfo() << "Move Valid";
            emit messageReceived("Move received");
         }
         break;

         case 3: // PING
         {
            //reply with a pong
            QJsonObject pong = Convert_Message_To_Json(GenerateMessage("PONG"));
            pong["Id"] = 100;
            SendMessage(msg["Id"].toInt(), pong);
         }
         break;

         case 4: // PONG
         {
            qInfo() << "Pong received from id: " << msg["Id"];
            emit messageReceived("Pong received");
         }
         break;

         case 5: // DISCONNECT_PLAYER
         {
            if(ConnectedClients[msg["Id"].toInt()].clientSocket)
                socketDisconnect(msg["Id"].toInt());
         }
         break;

         default:
            qWarning() << "Message type not found: " << type;
     }
}

/*
 * Slot triggered when a client disconnects
 * */
void Server::socketDisconnect(int id)
{
    if(!isValidSocketId(id))
        return;
    emit messageReceived("Client " + QString::number(id) + " disconnected");
    if(ConnectedClients[id].isAuthenticated)
        --numAuthenticatedUsers;
    ConnectedClients[id].isAuthenticated = false;
    ConnectedClients[id].clientSocket = NULL;
    --numConnectedClients;
}
