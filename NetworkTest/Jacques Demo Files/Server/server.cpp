/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement the server for the bridge game of EPE321
 * Author: Paul Claasen 18006885
 * Last update: 06/10/2020 Revision 3*/

#include "server.h"

/*
 * Constructor for the server, including server name, sslmode and parent object. Also can be specified whether shuffle should be called on construction, which is useful for testing.
 * */
Server::Server(const QString &serverName, SslMode secureMode, QObject *parent, bool shuffle) : QWebSocketServer(serverName, secureMode, parent), GS(this), validator(this)
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
        for(int value = One; value < Ace; value++)
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

    msgTypes << "CONNECT_REQUEST" << "BID_SEND" << "MOVE_SEND" << "PING" << "PONG" << "DISCONNECT_PLAYER" << "PLAYER_READY"; // Messages the server might receive
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

    bool valid = true;

    //criteria for username and password?
    if(username != "" && password != "")
    {
        for(int i = 0; i < num_players; ++i)
        {
            if(username == ConnectedClients[i].alias)
                valid = false;
        }
    }
    else
    {
        valid = false;
    }

    if(!valid)
    {
        QJsonObject error = Convert_Message_To_Json(GenerateMessage("AUTH_UNSUCCESSFUL"));
        error["Description"] = "Username/password invalid";

        if(validator.isValidSocketId(id)) // send a message only if the received id is in range and has a non-null websocket
            SendMessage(id, error);
    }
    else //valid
    {
        if(validator.isValidSocketId(id))
        {
            ++numAuthenticatedUsers;
            ConnectedClients[id].isAuthenticated = true;
            ConnectedClients[id].alias = username;
            SendMessage(id, Convert_Message_To_Json(GenerateMessage("AUTH_SUCCESSFUL")));

            QJsonObject lobby_update = Convert_Message_To_Json(GenerateMessage("LOBBY_UPDATE"));
            QJsonArray player_positions;
            for (int player = 0; player < numAuthenticatedUsers; ++player)
            {
                if(ConnectedClients[player].alias != "")
                {
                    QJsonObject player_loc = QJsonObject({
                                                       qMakePair(QString("Position"), QJsonValue(GS.getPlayerFromId(player))),
                                                       qMakePair(QString("Alias"), QJsonValue(ConnectedClients[player].alias))
                                                   });
                    player_positions.push_back(player_loc);
                }
            }
            lobby_update["PlayerPositions"] = player_positions;
            BroadcastMessage(lobby_update);
        }
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
 * Deal the deck to connected players, dealer passed is the int index of the client in ConnectedClients[] who should be the dealer
 * */
QJsonArray* Server::Construct_Cards_Message(int player)
{
    QJsonArray* client_cards = new QJsonArray();

    QJsonArray Hearts_arr;
    QJsonArray Spades_arr;
    QJsonArray Clubs_arr;
    QJsonArray Diamonds_arr;

    for(int card = 0; card < hand_size; ++card) // iterate row (card) first, then column
    {
        // TODO: Format this according to BID_START
        Card* card_ptr = Player_Hands[card][player];

        switch (card_ptr->suit)
        {
            case Hearts:
                Hearts_arr.push_back(card_ptr->ValToString());
            break;

            case Spades:
                Spades_arr.push_back(card_ptr->ValToString());
            break;

            case Diamonds:
                Diamonds_arr.push_back(card_ptr->ValToString());
            break;

            case Clubs:
                Clubs_arr.push_back(card_ptr->ValToString());
            break;
        }

    }
    QJsonObject hearts_entry = QJsonObject({
                                       qMakePair(QString("Suit"), QJsonValue("H")),
                                       qMakePair(QString("Rank"), QJsonValue(Hearts_arr))
                                   });
    QJsonObject spades_entry = QJsonObject({
                                       qMakePair(QString("Suit"), QJsonValue("S")),
                                       qMakePair(QString("Rank"), QJsonValue(Spades_arr))
                                   });
    QJsonObject diamonds_entry = QJsonObject({
                                       qMakePair(QString("Suit"), QJsonValue("D")),
                                       qMakePair(QString("Rank"), QJsonValue(Diamonds_arr))
                                   });
    QJsonObject clubs_entry = QJsonObject({
                                       qMakePair(QString("Suit"), QJsonValue("C")),
                                       qMakePair(QString("Rank"), QJsonValue(Clubs_arr))
                                   });
    client_cards->push_back(hearts_entry);
    client_cards->push_back(spades_entry);
    client_cards->push_back(diamonds_entry);
    client_cards->push_back(clubs_entry);

    return client_cards;
}

int Server::getTeamy(int otherTeamy)
{
    return (otherTeamy + 2) % num_players;
}

void Server::Deal(int dealer)
{
    //first assign cards one at a time to each player
    int count = 0; //keep track of card in deck
    for(int card = 0; card < hand_size; ++card)
    {
        for(int player = 0; player < num_players; ++player) // iterate column (player) first, then row
        {
            Deck[count].owner = player;
            Player_Hands[card][player] = &Deck[count++];
        }
    }

    //determine who is the dealer
    if(GS.getDealer() == NULL)
    {
        if(dealer == -1)
            dealer = rand() % num_players;
    }
    else
    {
        if(dealer == -1)
            dealer = (GS.getDealer()->id + 1) % num_players;
    }
    GS.setDealer(&ConnectedClients[dealer]);

    //construct and send a message to each client with their cards, and whether or not they are the dealer
    for(int player = 0; player < num_players; ++player)
    {
        QJsonArray client_cards = *Construct_Cards_Message(player);

        QJsonObject hand = Convert_Message_To_Json(GenerateMessage("BID_START"));
        hand["Cards"] = client_cards;
        hand["Dealer"] = GS.getPlayerFromId(dealer);
        SendMessage(player, hand);
    }

    GS.Reset(dealer);

    QJsonObject bid_req = Convert_Message_To_Json(GenerateMessage("BID_REQUEST"));
    SendMessage(dealer, bid_req);

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
    out << "North                       \t" << "East                        \t" << "South                       \t" << "West                        \n";
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
    if(!validator.isValidSocketId(pos, true))
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
    if(!validator.isValidSocketId(id))
        return;

    msg["Id"] = id;
    msg["Type"] = "CONNECT_SUCCESSFUL";
    QString strFromObj = QJsonDocument(msg).toJson(QJsonDocument::Compact);

    qInfo() << "Sending message: " << strFromObj;

    emit messageSent(strFromObj);
    ConnectedClients[id].clientSocket->sendTextMessage(strFromObj);
}

void Server::BroadcastMessage(QJsonObject msg)
{
    for (int player = 0; player < num_players; ++player)
    {
        SendMessage(player, msg);
    }
}

Card *Server::findCardInHand(int player, int val, int suit)
{
    for(int card = 0; card < Ace; ++card)
    {
        if(Player_Hands[card][player])
            if(Player_Hands[card][player]->value == val)
                if(Player_Hands[card][player]->suit == suit)
                {
                    Card* to_ret = Player_Hands[card][player];
                    Player_Hands[card][player] = NULL;
                    return to_ret;
                }
    }
    return NULL;
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
void Server::Next_Bid()
{
    GS.setPlayerTurn((GS.getPlayerTurn() + 1) % num_players);
    if(GS.getPlayerTurn() == GS.getDealer()->id)
        GS.setBidRoundCount(GS.getBidRoundCount() + 1);
    QJsonObject bid_req = Convert_Message_To_Json(GenerateMessage("BID_REQUEST"));
    SendMessage(GS.getPlayerTurn(), bid_req);
}

void Server::ValidateInput(QString message)
{
     emit messageReceived(message); // add message to ui listwidget

     QJsonObject msg = Convert_Message_To_Json(message); // convert message string to Json
     QString type = msg["Type"].toString(); // get type of message

     qInfo() << "Validating message: " << type;

     if(!validator.isValidSocketId(msg["Id"].toInt()))
         return;

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

            int value;
            if(card["Rank"].isNull())
                value = -1;
            else
                value = Card::StringToValue(card["Rank"].toString());

            int suit = Card::StringToSuit(card["Suit"].toString());
            int id = msg["Id"].toInt();

            bool valid = validator.isValidBid(id, value, suit);

            if(valid)
            {
                QJsonObject bid_update = Convert_Message_To_Json(GenerateMessage("BID_UPDATE"));
                bid_update["Bid"] = msg["Bid"];
                bid_update["Player"] = GS.getPlayerFromId(id);
                BroadcastMessage(bid_update);

                qInfo() << "Bid Valid";
                Card* bid = new Card(value, suit);
                bid->owner = id;

                if(suit == Double)
                {
                    GS.getCurrentBid()->isDoubled = true;
                    GS.ClearPassCount();

                    Next_Bid();
                }
                else if(suit == Redouble)
                {
                    GS.getCurrentBid()->isRedoubled = true;
                    GS.ClearPassCount();

                    Next_Bid();
                }
                else if(suit != Pass)
                {
                    GS.ClearPassCount();
                    GS.setCurrentBid(bid);

                    if(GS.firstDenominationBids[suit][id % 2] == -1)
                        GS.firstDenominationBids[suit][id % 2] = id;

                    Next_Bid();
                }
                else if(GS.getBidRoundCount() > 0) // passed, but not first round
                {
                    GS.IncreasePassCount();
                    if(GS.getPassCount() == 3) // three consecutive passses, play should commence
                    {// start play stage
                        GS.SetBidStage(false);
                        GS.setDeclarer(GS.firstDenominationBids[GS.getCurrentBid()->suit][GS.getCurrentBid()->owner % 2]);
                        GS.setPlayerTurn((GS.getDeclarer() + 1) % num_players);

                        QJsonObject bid_end = Convert_Message_To_Json(GenerateMessage("BID_END"));
                        bid_end["Trump"] = GS.getCurrentBid()->SuitToString();
                        bid_end["Declarer"] = GS.getPlayerFromId(GS.getDeclarer());
                        bid_end["Dummy"] = GS.getPlayerFromId((GS.getDeclarer() + 2) % num_players);

                        QJsonObject contract;
                        contract["Suit"] = GS.getCurrentBid()->SuitToString();
                        contract["Rank"] = GS.getCurrentBid()->ValToString();
                        contract["IsDouble"] = GS.getCurrentBid()->isDoubled;
                        contract["IsRedouble"] = GS.getCurrentBid()->isRedoubled;

                        bid_end["Contract"] = contract;
                        BroadcastMessage(bid_end);

                        QJsonObject play_start = Convert_Message_To_Json(GenerateMessage("PLAY_START"));
                        QJsonArray dummy_cards = *Construct_Cards_Message((GS.getDeclarer() + 2) % num_players);
                        play_start["DummyCards"] = dummy_cards;
                        BroadcastMessage(play_start);

                        QJsonObject move_req = Convert_Message_To_Json(GenerateMessage("MOVE_REQUEST"));
                        SendMessage(GS.getPlayerTurn(), move_req);
                    }
                    else
                    {
                        Next_Bid();
                    }
                }
                else // passed in first round
                {
                    GS.IncreasePassCount();
                    if(GS.getPassCount() == 4) // everyone passed in first round
                    {
                        // deal passed out
                        Shuffle();
                        Deal();
                    }
                    else
                    {
                        Next_Bid();
                    }
                }
            }
            emit messageReceived("Bid received");
        }
        break;

        case 2: // MOVE_SEND
        {
            QJsonObject card = msg["Move"].toObject();

            int id = msg["Id"].toInt();
            int value = card["Rank"].toInt();
            int suit = card["Suit"].toInt();

            bool valid = validator.isValidMove(id, value, suit);

            if(valid)
            {
                qInfo() << "Move Valid";


                QJsonObject move_update = Convert_Message_To_Json(GenerateMessage("MOVE_UPDATE"));
                move_update["Move"] = card;
                move_update["Player"] = GS.getPlayerFromId(id);
                BroadcastMessage(move_update);

                GS.CurrentTrick.push_back(findCardInHand(id, value, suit));
                GS.setPlayerTurn(GS.nextPlayerTurn());

                if(GS.CurrentTrick.size() == num_players) // end trick
                {
                    int lead_suit = GS.CurrentTrick[0]->suit;
                    int trump_suit = GS.getCurrentBid()->suit;

                    Card* best_card = GS.CurrentTrick[0];
                    for(int card = 1; card < num_players; ++card)
                    {
                        if(GS.CurrentTrick[card]->suit == trump_suit)
                        {
                            if(best_card->suit == trump_suit)
                            {
                                if(GS.CurrentTrick[card]->value > best_card->value)
                                    best_card = GS.CurrentTrick[card];
                            }
                            else
                            {
                                best_card = GS.CurrentTrick[card];
                            }
                        }
                        else if(GS.CurrentTrick[card]->suit == lead_suit)
                        {
                            if(best_card->suit == lead_suit)
                            {
                                if(GS.CurrentTrick[card]->value > best_card->value)
                                    best_card = GS.CurrentTrick[card];
                            }
                        }
                    }

                    QString winning_partnership = GS.getTeamFromId(best_card->owner);
                    GS.TrickScore[best_card->owner % 2] += 1;

                    QJsonObject trick_end = Convert_Message_To_Json(GenerateMessage("TRICK_END"));
                    trick_end["WinningPartnership"] = winning_partnership;
                    BroadcastMessage(trick_end);

                    GS.setTrickCount(GS.getTrickCount() + 1);

                    if(GS.getTrickCount() == hand_size) // end play
                    {
                        if(GS.TrickScore[NS] > GS.TrickScore[EW])
                            winning_partnership = "NS";
                        else
                            winning_partnership = "EW";


                        QJsonObject play_end = Convert_Message_To_Json(GenerateMessage("PLAY_END"));
                        trick_end["WinningPartnership"] = winning_partnership;
                        BroadcastMessage(trick_end);

                        //TODO scoring

                        // TODO next game

                    }

                    GS.CurrentTrick.clear();
                }
                else
                {
                    QJsonObject move_req = Convert_Message_To_Json(GenerateMessage("MOVE_REQUEST"));\
                    if(GS.getPlayerTurn() == getTeamy(GS.getDeclarer()))
                    {
                        move_req["MoveDummy"] = true;
                        SendMessage(GS.getDeclarer(), move_req);
                    }
                    else
                    {
                        move_req["MoveDummy"] = false;
                        SendMessage(GS.getPlayerTurn(), move_req);
                    }
                }
            }
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

        case 6: // PLAYER_READY
        {
            if(ConnectedClients[msg["Id"].toInt()].isAuthenticated)
            {
                ++numReady;
            }
            else
            {
                QJsonObject not_ready = Convert_Message_To_Json(GenerateMessage("NOT_READY"));
                SendMessage(msg["Id"].toInt(), not_ready);
            }

            if(numReady == num_players) // Four users are connected and authenticated, the game may commence.
            {
                Shuffle();
                Deal();
            }
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
    if(!validator.isValidSocketId(id))
        return;
    emit messageReceived("Client " + QString::number(id) + " disconnected");
    if(ConnectedClients[id].isAuthenticated)
        --numAuthenticatedUsers;
    ConnectedClients[id].isAuthenticated = false;
    ConnectedClients[id].clientSocket = NULL;
    ConnectedClients[id].alias = "";
    --numConnectedClients;
}
