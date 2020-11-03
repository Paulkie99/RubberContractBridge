/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement the server for the bridge game of EPE321
 * Author: Paul Claasen 18006885
 * Last update: 27/10/2020 Revision 20*/

#include "server.h"

/*
 * Constructor for the server, including server name, sslmode and parent object.
 * Signals for connections and disconnections are connected to relevant server slots
 * Deck is constructed and player_hands are initialised
 * Message types are stored
 * */
Server::Server(const QString &serverName, SslMode secureMode, QObject *parent) : QWebSocketServer(serverName, secureMode, parent), validator(this)
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
 * A valid username/password is non-empty
 * A valid username is unique
 * If authentication is successful, send auth_successful and broadcast lobby_update
 * else, send auth_unsuccessful and disconnect socket
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

        socketDisconnect(id);
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
 * Construct a message as a QJsonArray, which contains the passed player's cards in hand, sorted by suit
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

/*
 * Helper function to get the id of a player's team mate
 * */
int Server::getTeamy(int otherTeamy)
{
    return (otherTeamy + 2) % num_players;
}

/*
 * Deal the deck in-order to players, in a clockwise direction.
 * Shuffle should be called before this function.
 * A desired dealer may be passed or will otherwise be determined randomly if a current dealer does not exist
 * If a dealer exists, the dealer becomes the next player
 * This function also sends bid_start message to each player, which contains the players' hands
 * Bid_request is sent to the dealer
 * */
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
    GS.Reset(dealer);

    //construct and send a message to each client with their cards, and whether or not they are the dealer
    for(int player = 0; player < num_players; ++player)
    {
        QJsonArray client_cards = *Construct_Cards_Message(player);

        QJsonObject hand = Convert_Message_To_Json(GenerateMessage("BID_START"));
        hand["Cards"] = client_cards;
        hand["Dealer"] = GS.getPlayerFromId(dealer);
        SendMessage(player, hand);
    }


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
    out << "North             \t" << "East              \t" << "South             \t" << "West              \n";
    for(int card = 0; card < hand_size; ++card)
    {
        for(int player = 0; player < num_players; ++player)
        {
            if(Player_Hands[card][player])
                Player_Hands[card][player]->print(out);
            else
                out << "                 ";
            out << "\t";
        }
        out << "\n";
    }
}

/*
 * Perform necessary functions to connect a client to a specified position in the ConnectedClients array, the relevant signals and slots are also connected
 * CONNECT_SUCCESFUL is sent
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
    QString strFromObj = QJsonDocument(msg).toJson(QJsonDocument::Compact);

    qInfo() << "Sending message: " << strFromObj;

    emit messageSent(strFromObj);
    ConnectedClients[id].clientSocket->sendTextMessage(strFromObj);
}

/*
 * Helper function to send a message to all connected clients
 * */
void Server::BroadcastMessage(QJsonObject msg)
{
    for (int player = 0; player < num_players; ++player)
    {
        SendMessage(player, msg);
    }
}

/*
 * Determine whether a card is in a player's hand and return it, else return null
 * If it is not the player's turn, and they are the declarer, and it is the dummy turn, check the dummy's hand as well
 * */
Card *Server::findCardInHand(int player, int val, int suit)
{
    if(player == GS.getPlayerTurn())
    {
        for(int card = 0; card < Ace; ++card)
        {
            if(Player_Hands[card][player])
            {
                if(Player_Hands[card][player]->value == val)
                {
                    if(Player_Hands[card][player]->suit == suit)
                    {
                        Card* to_ret = Player_Hands[card][player];
                        Player_Hands[card][player] = NULL;
                        return to_ret;
                    }
                }
            }
        }
    }
    else if(player == getTeamy(GS.getPlayerTurn()) && player == GS.getDeclarer())
    {
        int dummy = getTeamy(player);
        for(int card = 0; card < Ace; ++card)
        {
            if(Player_Hands[card][dummy])
            {
                if(Player_Hands[card][dummy]->value == val)
                {
                    if(Player_Hands[card][dummy]->suit == suit)
                    {
                        Card* to_ret = Player_Hands[card][dummy];
                        Player_Hands[card][dummy] = NULL;
                        return to_ret;
                    }
                }
            }
        }
    }
    return NULL;
}

/*
 * Check each player's hand for honors, depending on trump suit.
 * If a hand contains five honors (or four in case of NT contract), save their Id and number of honors in GS
 * */
void Server::findHonors()
{
    int suit = GS.getCurrentBid()->suit;

    for(int player = 0; player < num_players; ++player)
    {
        int honorCount = suit == NT ? 1 : 0;
        for(int card = 0; card < hand_size; ++card)
        {
            int cardrank = Player_Hands[card][player]->value;
            if(suit == NT)
            {
                if(cardrank == Ace)
                    ++honorCount;
            }
            else
            {
                if(Player_Hands[card][player]->suit == suit)
                    if(cardrank == Ace || cardrank == King || cardrank == Queen || cardrank == Jack || cardrank == Ten)
                        ++honorCount;
            }
        }
        if(honorCount > 3)
        {
            GS.honorsCount = honorCount;
            GS.honorsId = player;
            break;
        }
    }
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
 * Increment player turn and bidroundcount, send a bid request to the player who's turn it is now
 * */
void Server::Next_Bid()
{
    GS.setPlayerTurn((GS.getPlayerTurn() + 1) % num_players);
    if(GS.getPlayerTurn() == GS.getDealer()->id)
        GS.setBidRoundCount(GS.getBidRoundCount() + 1);
    QJsonObject bid_req = Convert_Message_To_Json(GenerateMessage("BID_REQUEST"));
    SendMessage(GS.getPlayerTurn(), bid_req);
}

/*
 * Send a move request to the player who's turn it is, if they are the dummy send a message to the declarer with "MoveDummy" true
 * Unlike Next_Bid, player turn must be incremented outside of this function
 * */
void Server::Next_Move()
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

/*
 * Score a deal according to bridge scoring rules, determine whether a game has ended and whether a rubber has ended
 * Send SCORE, and GAME_END depending on whether a rubber has ended
 * */
void Server::Score_Deal()
{
    QJsonObject score = Convert_Message_To_Json(GenerateMessage("SCORE"));
    QJsonObject NSscores = {
                                qMakePair(QString("overtricks"), QJsonValue(0)),
                                qMakePair(QString("undertricks"), QJsonValue(0)),
                                qMakePair(QString("honors"), QJsonValue(0)),
                                qMakePair(QString("vulnerable"), QJsonValue(int(GS.IsVulnerable[NS]))),
                                qMakePair(QString("double"), QJsonValue(int(GS.getCurrentBid()->isDoubled))),
                                qMakePair(QString("redouble"), QJsonValue(int(GS.getCurrentBid()->isRedoubled))),
                                qMakePair(QString("slam"), QJsonValue(0)),
                                qMakePair(QString("unfinished"), QJsonValue(0)),
                                qMakePair(QString("trickScore"), QJsonValue(0)),
                                qMakePair(QString("insult"), QJsonValue(0)),
                                qMakePair(QString("rubberbonus"), QJsonValue(0))
                           };
    QJsonObject EWscores = {
                                qMakePair(QString("overtricks"), QJsonValue(0)),
                                qMakePair(QString("undertricks"), QJsonValue(0)),
                                qMakePair(QString("honors"), QJsonValue(0)),
                                qMakePair(QString("vulnerable"), QJsonValue(int(GS.IsVulnerable[EW]))),
                                qMakePair(QString("double"), QJsonValue(int(GS.getCurrentBid()->isDoubled))),
                                qMakePair(QString("redouble"), QJsonValue(int(GS.getCurrentBid()->isRedoubled))),
                                qMakePair(QString("slam"), QJsonValue(0)),
                                qMakePair(QString("unfinished"), QJsonValue(0)),
                                qMakePair(QString("trickScore"), QJsonValue(0)),
                                qMakePair(QString("insult"), QJsonValue(0)),
                                qMakePair(QString("rubberbonus"), QJsonValue(0))
                           };
    QJsonObject scores[2] = {NSscores, EWscores};

    Card contract_card = *GS.getCurrentBid();
    int contract = contract_card.value + 1;
    int declarerTeam = GS.getDeclarer() % 2;
    int made = GS.TrickScore[declarerTeam] - 6;
    qInfo() << "Contract: " << contract;
    qInfo() << "Made: " << made;
    if(made > contract) // overtrick(s) and contract points
    {
        int num_over = made - contract;
        if(contract_card.isRedoubled)
        {
            scores[declarerTeam]["overtricks"] = num_over * 200 * (GS.IsVulnerable[declarerTeam] ? 2 : 1);
        }
        else if(contract_card.isDoubled)
        {
            scores[declarerTeam]["overtricks"] = num_over * 100 * (GS.IsVulnerable[declarerTeam] ? 2 : 1);
        }
        else
        {
            if(contract_card.suit > Diamonds) // major suit or no trump
                scores[declarerTeam]["overtricks"] = num_over * 30;
            else // minor suit
                scores[declarerTeam]["overtricks"] = num_over * 20;
        }

        // contract points
        int trickScore = 0;
        if(contract_card.suit == NT)
        {
            trickScore = 40;
            trickScore += 30 * (contract - 1);
        }
        else if(contract_card.suit > Diamonds) // major suit
            trickScore = 30 * contract;
        else // minor suit
            trickScore = 20 * contract;

        trickScore *= (contract_card.isDoubled ? 2 : 1);
        trickScore *= (contract_card.isRedoubled ? 2 : 1);

        scores[declarerTeam]["trickScore"] = trickScore;
        qInfo() << "NSscore under" << GS.underTheLine[0];
        GS.underTheLine[declarerTeam] += trickScore;
        qInfo() << "NSscore under" << GS.underTheLine[0];

        int insult = 1;
        insult *= (contract_card.isDoubled ? 50 : 0);
        insult *= (contract_card.isRedoubled ? 2 : 1);
        scores[declarerTeam]["insult"] = insult;

        if(contract == 6)
            scores[declarerTeam]["slam"] = GS.IsVulnerable[declarerTeam] ? 750 : 500;
    }
    else if(made < contract) // undertrick(s)
    {
        int undertrick = 0;
        int num_under = contract - made;
        if(GS.IsVulnerable[declarerTeam])
        {
            if(!contract_card.isDoubled)
            {
                undertrick = 100 * num_under;
            }
            else
            {
                undertrick = 200;
                undertrick += 300 * (num_under - 1);
            }

            undertrick *= contract_card.isRedoubled ? 2 : 1;
        }
        else
        {
            if(!contract_card.isDoubled)
            {
                undertrick = 50 * num_under;
            }
            else
            {
                undertrick = 100;
                undertrick += (num_under - 1 > 0 ? 200 : 0);
                undertrick += (num_under - 2 > 0 ? 200 : 0);
                undertrick += (num_under - 3 > 0 ? (300 * (num_under - 3)) : 0);
            }

            undertrick *= contract_card.isRedoubled ? 2 : 1;
        }
        scores[(declarerTeam + 1) % 2]["undertricks"] = undertrick;
    }
    else // equal
    { // just contract points
        qInfo() << "NSscore under" << GS.underTheLine[0];
        int trickScore = 0;
        if(contract_card.suit == NT)
        {
            trickScore = 40;
            trickScore += 30 * (contract - 1);
        }
        else if(contract_card.suit > Diamonds) // major suit
            trickScore = 30 * contract;
        else // minor suit
            trickScore = 20 * contract;

        trickScore *= (contract_card.isDoubled ? 2 : 1);
        trickScore *= (contract_card.isRedoubled ? 2 : 1);

        scores[declarerTeam]["trickScore"] = trickScore;
        GS.underTheLine[declarerTeam] += trickScore;
        qInfo() << "NSscore under" << GS.underTheLine[0];

        int insult = 1;
        insult *= (contract_card.isDoubled ? 50 : 0);
        insult *= (contract_card.isRedoubled ? 2 : 1);
        scores[declarerTeam]["insult"] = insult;

        if(contract == 6)
            scores[declarerTeam]["slam"] = GS.IsVulnerable[declarerTeam] ? 750 : 500;
        else if(contract == 7)
            scores[declarerTeam]["slam"] = GS.IsVulnerable[declarerTeam] ? 1500 : 1000;
    }

    if(GS.honorsCount > 3)
    {
        if(GS.honorsCount == 4)
            scores[GS.honorsId % 2]["honors"] = 100;
        else
            scores[GS.honorsId % 2]["honors"] = 150;
    }


    qInfo() << "NSscore Rubber" << GS.RubberScore[0];
    GS.RubberScore[NS] += scores[NS]["overtricks"].toInt() +
                          scores[NS]["undertricks"].toInt() +
                          scores[NS]["honors"].toInt() +
                          scores[NS]["slam"].toInt() +
                          scores[NS]["unfinished"].toInt() +
                          scores[NS]["trickScore"].toInt() +
                          scores[NS]["insult"].toInt();
    qInfo() << "NSscore Rubber" << GS.RubberScore[0];

    GS.RubberScore[EW] += scores[EW]["overtricks"].toInt() +
                          scores[EW]["undertricks"].toInt() +
                          scores[EW]["honors"].toInt() +
                          scores[EW]["slam"].toInt() +
                          scores[EW]["unfinished"].toInt() +
                          scores[EW]["trickScore"].toInt() +
                          scores[EW]["insult"].toInt();

    score["NSscores"] = scores[NS];
    score["EWscores"] = scores[EW];

    if(GS.underTheLine[declarerTeam] >= 100)
    {
        GS.underTheLine[declarerTeam] = 0;
        if(GS.IsVulnerable[declarerTeam])
        {
            // second win
            scores[declarerTeam]["rubberbonus"] = GS.IsVulnerable[(declarerTeam + 1) % 2] ? 500 : 700;
            GS.RubberScore[declarerTeam] += scores[declarerTeam]["rubberbonus"].toInt();

            score["NSscores"] = scores[NS];
            score["EWscores"] = scores[EW];

            BroadcastMessage(score);

            QJsonObject game_end = Convert_Message_To_Json(GenerateMessage("GAME_END"));
            game_end["WinningPartnership"] = GS.getTeamFromId(GS.RubberScore[NS] > GS.RubberScore[EW] ? NS : EW);
            game_end["NSscore"] = GS.RubberScore[NS];
            game_end["EWscore"] = GS.RubberScore[EW];

            GS.isGameOver = true;
            BroadcastMessage(game_end);
        }
        else
        {
            GS.IsVulnerable[declarerTeam] = true;
            scores[declarerTeam]["vulnerable"] = 1;
            BroadcastMessage(score);
        }
    }
    else
    {
        BroadcastMessage(score);
    }
}

/*
 * Find the best card in the current trick based on the bid contract
 * */
Card* Server::GetBestCardInTrick()
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
    return best_card;
}

/*
 * Update GS based on a recent bid, if three consecutive passses have occurred send bid_end, play_start and move_request
 * If the deal is passed out (four passes in first bidding round), shuffle and redeal
 * Call Next_Bid otherwise
 * */
void Server::Play_Start()
{
    GS.SetBidStage(false);
    GS.setMoveStage(true);
    GS.setDeclarer(GS.firstDenominationBids[GS.getCurrentBid()->suit][GS.getCurrentBid()->owner % 2]);
    GS.setPlayerTurn((GS.getDeclarer() + 1) % num_players);

    findHonors();

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

void Server::Update_Bid(int id, int value, int suit)
{
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
        qInfo() << "PASS DETECTED" << GS.getPassCount();
        if(GS.getPassCount() == 3) // three consecutive passses, play should commence
        {// start play stage
            qInfo() << "Play starting";
            Play_Start();
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
            if(shuffle)
                Shuffle();
            Deal();
        }
        else if(GS.getPassCount() == 3)
        {
            if(GS.getCurrentBid())
            {
                Play_Start();
            }
            else
            {
                Next_Bid();
            }
        }
        else
        {
            Next_Bid();
        }
    }
}

/*
 * Update GS based on a recent move
 * If a trick has ended broadcast trick_end
 * If thirteen tricks have ended broadcast play_end and call Score_Deal
 * Call Next_Deal otherwise
 * */
void Server::Update_Play()
{
    if(GS.CurrentTrick.size() == num_players) // end trick
    {

        Card* best_card = GetBestCardInTrick();

        QString winning_partnership = GS.getTeamFromId(best_card->owner);
        GS.TrickScore[best_card->owner % 2] += 1;

        QJsonObject trick_end = Convert_Message_To_Json(GenerateMessage("TRICK_END"));
        trick_end["WinningPartnership"] = winning_partnership;
        BroadcastMessage(trick_end);

        GS.setTrickCount(GS.getTrickCount() + 1);

        GS.CurrentTrick.clear();

//        PrintHands();

        if(GS.getTrickCount() == hand_size) // end play
        {
            QJsonObject play_end = Convert_Message_To_Json(GenerateMessage("PLAY_END"));

            if(GS.TrickScore[NS] > GS.TrickScore[EW])
            {
                play_end["WinningPartnership"] = "NS";
                play_end["TricksWon"] = GS.TrickScore[NS];
            }
            else
            {
                play_end["WinningPartnership"] = "EW";
                play_end["TricksWon"] = GS.TrickScore[EW];
            }

            BroadcastMessage(play_end);

            // scoring
            Score_Deal();

            if(GS.isGameOver)
            {
                GameState newGS;
                GS = newGS; // reinitialise GS

                for(int i = 0; i < num_players; ++i)
                    socketDisconnect(i);
            }
            else
            {
                if(shuffle)
                    Shuffle();
                Deal();
            }
        }
        else
        {
            GS.setPlayerTurn(best_card->owner);
            Next_Move();
        }
    }
    else
    {
        GS.setPlayerTurn(GS.nextPlayerTurn());
        Next_Move();
    }
}

/*
 * This slot receives client text messages and calls the relevant functions based on the received message
 * In case of connect_request : Authenticate()
 * Bid_Send : isValidBid() and Update_Bid()
 * Move_Send : isValidMove() and Update_Play()
 * Ping : send Pong
 * Pong : output that pong has been received
 * Disconnect player: call socketDisconnect
 * Player_Ready: Ignore if in bidding or play stage, else increment number of ready players if the player is not already ready,
 * if there is four ready players, Shuffle() and Deal()
 * */
void Server::ValidateInput(QString message)
{
//     emit messageReceived(message); // add message to ui listwidget

     QJsonObject msg = Convert_Message_To_Json(message); // convert message string to Json
     QString type = msg["Type"].toString(); // get type of message

     qInfo() << "Validating message: " << type;

     if(!validator.isValidSocketId(msg["Id"].toInt()))
        return;

     switch(msgTypes.indexOf(type))
     {
        case 0: // CONNECT_REQUEST
        {
            emit messageReceived("Connect request received");
            Authenticate(msg["Alias"].toString(), msg["Password"].toString(), msg["Id"].toInt());
        }
        break;

        case 1: // BID_SEND
        {
            emit messageReceived("Bid received");

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
                emit messageReceived("Bid Valid");
                Update_Bid(id, value, suit);
            }
            else
            {
                qInfo() << "Bid Invalid";
                emit messageReceived("Bid Invalid");
            }
        }
        break;

        case 2: // MOVE_SEND
        {
            emit messageReceived("Move received");

            QJsonObject card = msg["Move"].toObject();

            int id = msg["Id"].toInt();
            int value = Card::StringToValue(card["Rank"].toString());
            int suit = Card::StringToSuit(card["Suit"].toString());

            bool valid = validator.isValidMove(id, value, suit);

            if(valid)
            {
                qInfo() << "Move Valid";
                emit messageReceived("Move Valid");

                QJsonObject move_update = Convert_Message_To_Json(GenerateMessage("MOVE_UPDATE"));
                move_update["Move"] = card;
                move_update["Player"] = GS.getPlayerFromId(id);
                BroadcastMessage(move_update);

                GS.CurrentTrick.push_back(findCardInHand(id, value, suit));

                Update_Play();
            }
            else
            {
                emit messageReceived("Move Invalid");
                qInfo() << "Invalid Move";
                Next_Move();
            }
        }
        break;

        case 3: // PING
        {
            //reply with a pong
            QJsonObject pong = Convert_Message_To_Json(GenerateMessage("PONG"));
            pong["Id"] = 100;
            SendMessage(msg["Id"].toInt(), pong);
            emit messageReceived("Ping received");
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
            emit messageReceived("Disconnect player received");
        }
        break;

        case 6: // PLAYER_READY
        {
            if(GS.GetBidStage() || GS.getMoveStage() || !validator.isValidSocketId(msg["Id"].toInt())) // game in progress
                break;

            if(ConnectedClients[msg["Id"].toInt()].isAuthenticated)
            {
                if(!ConnectedClients[msg["Id"].toInt()].isReady)
                {
                    ++numReady;
                    ConnectedClients[msg["Id"].toInt()].isReady = true;
                }
            }
            else
            {
                QJsonObject not_ready = Convert_Message_To_Json(GenerateMessage("NOT_READY"));
                SendMessage(msg["Id"].toInt(), not_ready);
            }

            if(numReady == num_players) // Four users are connected and authenticated, the game may commence.
            {
                if(shuffle)
                   Shuffle();
                Deal();
            }
            emit messageReceived("Player ready received");
        }
        break;

        default:
            qWarning() << "Message type not found: " << type;
            emit messageReceived("Unknown Message Received");
     }
}

/*
 * Slot triggered when a client disconnects, reinitialise serverclient based on id and broadcast DISCONNECT_PLAYER
 * */
void Server::socketDisconnect(int id)
{
    if(!validator.isValidSocketId(id))
        return;
    emit messageReceived("Client " + QString::number(id) + " disconnected");
    if(ConnectedClients[id].isAuthenticated)
        --numAuthenticatedUsers;
    if(ConnectedClients[id].isReady)
        --numReady;
    ConnectedClients[id].isAuthenticated = false;
    ConnectedClients[id].isReady = false;
    ConnectedClients[id].clientSocket = NULL;
    ConnectedClients[id].alias = "";
    --numConnectedClients;

    QJsonObject disconnect_player = Convert_Message_To_Json(GenerateMessage("DISCONNECT_PLAYER"));
    disconnect_player["Type"] = "DISCONNECT_PLAYER";
    disconnect_player["PlayerPos"] = GS.getPlayerFromId(id);
    BroadcastMessage(disconnect_player);

    if(numConnectedClients == 0)
    {
        GameState newGs;
        GS = newGs;
    }
}
