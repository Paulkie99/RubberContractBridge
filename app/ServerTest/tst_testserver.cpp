/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement tests for the server
 * Author: Paul Claasen 18006885
 * Last update: 27/10/2020 Revision 10*/

#include <inputvalidator.h>
#include <serverinterface.h>
#include <clientconnection.h>
#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class TestServer : public QObject
{
    Q_OBJECT

public:
    TestServer();
    ~TestServer();

    void PassAndPlay();
    void PassAndPlay2();

private:
    ServerInterface* server;
    QSignalSpy* spyServerReception;
    QSignalSpy* spyServerSend;
    QJsonObject Convert_Message_To_Json(QString msg)
    {
    //    qInfo() << "Converting message to Json: " << msg;
        QJsonDocument d = QJsonDocument::fromJson(msg.toUtf8());
        QJsonObject jObject = d.object();
        return jObject;
    }
    std::vector<clientconnection*> clients;
    std::vector<QSignalSpy*> spies;
    void send_bid(QString suit, QString rank, bool out_of_turn = false);
    void send_move(QString suit, QString rank, bool out_of_turn = false, int id = -1);

private slots:
    void initTestCase();
    void init();
    void cleanup();

    void TestIdealServerSendsAndReceives();
    void TestAuthFailed();
    void TestInputBranch();
    void TestDeal();
    void TestShuffle();
    void TestConnectLobbyFull();
    void TestDisconnect();
    void TestReconnect();
    void TestValidInvalidBid();
    void TestValidInvalidMove();
    void TestScoring();
};

TestServer::TestServer()
{

}

TestServer::~TestServer()
{

}

void TestServer::initTestCase()
{
}

/*
 * For each test, create a new server and signal spies
 * */
void TestServer::init()
{
    server = new ServerInterface();
    server->bridgeServer->shuffle = false;
    spyServerReception = new QSignalSpy(server->bridgeServer, SIGNAL(messageReceived(QString)));
    spyServerSend = new QSignalSpy(server->bridgeServer, SIGNAL(messageSent(QString)));
    server->bridgeServer->GS.setDealer(&server->bridgeServer->ConnectedClients[1]);
}

/*
 * After each test, delete signal spies, server and clear client and spy vectors
 * */
void TestServer::cleanup()
{
    delete server;
    delete spyServerReception;
    delete spyServerSend;
    clients.clear();
    spies.clear();
}

/*
 * Test connection of one client (with valid credentials) with expected success messages: connect_successful, auth_successful, lobby_update
 * */
void TestServer::TestIdealServerSendsAndReceives()
{
    clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "Username"); //connect the client to server
    // wait sufficient amount of time for all messages to be sent/received
    spyServerReception->wait(100);
    spyServerSend->wait(100);
    QList<QVariant> args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Unknown Message Received"); // first messsage received should be "Hello There"

    args = spyServerSend->takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "CONNECT_SUCCESSFUL"); // Server should reply saying that connection was successful

    args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Connect request received"); // Server should then receive username and password info

    args = spyServerSend->takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "AUTH_SUCCESSFUL"); // server should reply saying that the user was successfully authenticated

    args = spyServerSend->takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "LOBBY_UPDATE"); // server should reply saying that the user was successfully authenticated
}

/*
 * Test that the server sends an AUTH_FAILED if the user has invalid credentials, invalid credentials include a user having an
 * empty username/password or a username that is identical to that of an existing user
 * */
void TestServer::TestAuthFailed()
{
    clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), true); //connect the client to server, debug = true sends empty password
    // wait sufficient amount of time for all messages to be sent/received
    spyServerReception->wait(100);
    spyServerSend->wait(100);
    QList<QVariant> args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Unknown Message Received"); // first messsage received should be "Hello There"

    args = spyServerSend->takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "CONNECT_SUCCESSFUL"); // Server should reply saying that connection was successful

    args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Connect request received"); // Server should then receive username and password info

    args = spyServerSend->takeAt(0); // server should reply saying that the user was could not be authenticated
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "AUTH_UNSUCCESSFUL");
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Description"], "Username/password invalid");
}

/*
 * Test whether the server logic branches correctly according to the message received, clients first send "Hello there", which
 * is seen as an unknown message. Upon receiving a connection request, the server should emit a signal saying so. The same applies
 * to ping, bid_send and move_send messages
 * */
void TestServer::TestInputBranch()
{
    clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "Username"); //connect the client to server
    // wait sufficient amount of time for all messages to be sent/received
    spyServerReception->wait(100);
    spyServerSend->wait(100);

    QList<QVariant> args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Unknown Message Received"); // first messsage received should be "Hello There"

    args = spyServerSend->takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "CONNECT_SUCCESSFUL"); // Server should reply saying that connection was successful

    args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Connect request received"); // Server should then receive username and password info

    args = spyServerSend->takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "AUTH_SUCCESSFUL"); // server should reply saying that the user was successfully authenticated

    args = spyServerSend->takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "LOBBY_UPDATE"); // server should reply saying that the user was successfully authenticated

    QJsonObject ping = client.CreateJObject(client.GenerateMessage("PING"));
    ping["Id"] = 0;
    client.SendMessageToServer(client.CreateJString(ping)); // PING server

    spyServerReception->wait(50);
    spyServerSend->wait(50);

    args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Ping received"); // server correctly sent pong

    args = spyServerSend->takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "PONG"); // server correctly sent pong

    QJsonObject bid_send = client.CreateJObject(client.GenerateMessage("BID_SEND"));
    bid_send["Id"] = 0;
    client.SendMessageToServer(client.CreateJString(bid_send)); // send bid

    spyServerReception->wait(50);

    args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Bid received"); // server received bid

    QJsonObject move_send = client.CreateJObject(client.GenerateMessage("MOVE_SEND"));
    move_send["Id"] = 0;
    client.SendMessageToServer(client.CreateJString(move_send)); // send move

    spyServerReception->wait(50);

    args = spyServerReception->takeAt(1);
    QCOMPARE(args.at(0).toString(), "Move received"); // server received move
}

/*
 * Test whether the server sends card arrays to each client after four have connected, and all clients
 * have sent ready messages. One client (the dealer) should also receive a bid_request message
 * */
void TestServer::TestDeal()
{

    for(int i = 0; i < 4; ++i)
    {
        QString username = "User" + QString(i);

        clientconnection* temp = new clientconnection(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, username);

        QSignalSpy* temp_spy = new QSignalSpy(temp, SIGNAL(messageReceived(QString)));

        clients.push_back(temp);
        spies.push_back(temp_spy);
        spies[i]->wait(50);
    }

    QJsonObject clien1_msg = clients[0]->CreateJObject(clients[0]->GenerateMessage("PLAYER_READY"));
    clients[0]->SendMessageToServer(clients[0]->CreateJString(clien1_msg));

    QJsonObject clien2_msg = clients[1]->CreateJObject(clients[1]->GenerateMessage("PLAYER_READY"));
    clients[1]->SendMessageToServer(clients[1]->CreateJString(clien1_msg));

    QJsonObject clien3_msg = clients[2]->CreateJObject(clients[2]->GenerateMessage("PLAYER_READY"));
    clients[2]->SendMessageToServer(clients[2]->CreateJString(clien1_msg));

    QJsonObject clien4_msg = clients[3]->CreateJObject(clients[3]->GenerateMessage("PLAYER_READY"));
    clients[3]->SendMessageToServer(clients[3]->CreateJString(clien1_msg));

    spies[0]->wait(50);
    spies[1]->wait(50);
    spies[2]->wait(50);
    spies[3]->wait(50);

    for(int i = 0; i < 4; ++i)
    {
        if(spies[i]->size() == (8 - i))
        {
            QCOMPARE(Convert_Message_To_Json(spies[i]->takeAt((8 - i) - 2).at(0).toString())["Type"], "BID_START");
            QCOMPARE(Convert_Message_To_Json(spies[i]->takeAt((8 - i) - 2).at(0).toString())["Type"], "BID_REQUEST");

            QJsonObject bid_send = clients[i]->CreateJObject(clients[i]->GenerateMessage("BID_SEND"));
            QJsonObject bid = {qMakePair(QString("Suit"), QJsonValue("NT")), qMakePair(QString("Rank"), QJsonValue("1"))};
            bid_send["Bid"] = bid;
            bid_send["Id"] = clients[i]->id;
            clients[i]->SendMessageToServer(clients[i]->CreateJString(bid_send));
        }
        else if(spies[i]->size() == 7 - i)
        {
            QCOMPARE(Convert_Message_To_Json(spies[i]->takeAt(7 - i - 1).at(0).toString())["Type"], "BID_START");
        }
    }
}

/*
 * Function testing the shuffle() function of the server
 * */
void TestServer::TestShuffle()
{
    delete server;
    server = new ServerInterface();
    server->bridgeServer->shuffle = true;

    server->bridgeServer->GS.setDealer(&server->bridgeServer->ConnectedClients[0]);

    for(int i = 0; i < 4; ++i)
    {
        QString username = "User" + QString(i);

        clientconnection* temp = new clientconnection(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, username);

        QSignalSpy* temp_spy = new QSignalSpy(temp, SIGNAL(messageReceived(QString)));

        clients.push_back(temp);
        spies.push_back(temp_spy);
        spies[i]->wait(50);
    }

    QJsonObject clien1_msg = clients[0]->CreateJObject(clients[0]->GenerateMessage("PLAYER_READY"));
    clients[0]->SendMessageToServer(clients[0]->CreateJString(clien1_msg));

    QJsonObject clien2_msg = clients[1]->CreateJObject(clients[1]->GenerateMessage("PLAYER_READY"));
    clients[1]->SendMessageToServer(clients[1]->CreateJString(clien1_msg));

    QJsonObject clien3_msg = clients[2]->CreateJObject(clients[2]->GenerateMessage("PLAYER_READY"));
    clients[2]->SendMessageToServer(clients[2]->CreateJString(clien1_msg));

    QJsonObject clien4_msg = clients[3]->CreateJObject(clients[3]->GenerateMessage("PLAYER_READY"));
    clients[3]->SendMessageToServer(clients[3]->CreateJString(clien1_msg));

    spies[0]->wait(50);
    spies[1]->wait(50);
    spies[2]->wait(50);
    spies[3]->wait(50);

    for(int i = 0; i < 4; ++i)
    {
        if(spies[i]->size() == (8 - i))
        {
            QJsonObject bid_start = Convert_Message_To_Json(spies[i]->takeAt((8 - i) - 2).at(0).toString());
            QCOMPARE(bid_start["Type"], "BID_START");
            QVERIFY(bid_start["Cards"].toArray().at(0).toObject()["Rank"].toArray().at(0).toString() != "K" && bid_start["Cards"].toArray().at(0).toObject()["Rank"].toArray().at(1).toString() != "9" && bid_start["Cards"].toArray().at(0).toObject()["Rank"].toArray().at(2).toString() != "5");
            QCOMPARE(Convert_Message_To_Json(spies[i]->takeAt((8 - i) - 2).at(0).toString())["Type"], "BID_REQUEST");
        }
    }
}


/*
 * Test whether the server allows a fifth connection even though a lobby consists of four, four clients are connected
 * after which a fifth user should be rejected, due to "LOBBY_FULL"
 * */
void TestServer::TestConnectLobbyFull()
{
    clientconnection client1(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User1");
    QSignalSpy spy1(&client1, SIGNAL(messageReceived(QString)));
    spy1.wait(50);

    clientconnection client2(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User2");
    QSignalSpy spy2(&client2, SIGNAL(messageReceived(QString)));
    spy2.wait(50);

    clientconnection client3(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User3");
    QSignalSpy spy3(&client3, SIGNAL(messageReceived(QString)));
    spy3.wait(50);

    clientconnection client4(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User4");
    QSignalSpy spy4(&client4, SIGNAL(messageReceived(QString)));
    spy4.wait(50);

    clientconnection client5(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User5");
    QSignalSpy spy5(&client5, SIGNAL(messageReceived(QString)));
    spy5.wait(50);


    QList<QVariant> args = spy5.takeAt(0); // Server should send CONNECT_UNSUCCESSFUL to fifth connecting client
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "CONNECT_UNSUCCESSFUL");
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Description"], "LOBBY_FULL");
}

/*
 * Test whether the server performs the applicable housekeeping when a user disconnects, four clients are connected
 * after which one disconnects by closing its socket. Reception of a disconnect message from the server is monitored, which
 * indicates that the server has processed the disconnect.
 * */
void TestServer::TestDisconnect()
{

    clientconnection client1(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User1");
    QSignalSpy spy1(&client1, SIGNAL(messageReceived(QString)));
    spy1.wait(50);

    clientconnection client2(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User2");
    QSignalSpy spy2(&client2, SIGNAL(messageReceived(QString)));
    spy2.wait(50);

    clientconnection client3(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User3");
    QSignalSpy spy3(&client3, SIGNAL(messageReceived(QString)));
    spy3.wait(50);

    clientconnection client4(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User4");
    QSignalSpy spy4(&client4, SIGNAL(messageReceived(QString)));
    spy4.wait(50);

    client4.clientSocket->close();

    spyServerReception->wait(100);

    QList<QVariant> args = spyServerReception->takeAt(8);
    QVERIFY2(args.at(0).toString() == ("Client 3 disconnected"), args.at(0).toString().toStdString().c_str());
}

/*
 * Test whether the server performs the applicable housekeeping when a user reconnects after a disconnect
 * */
void TestServer::TestReconnect()
{
    TestDisconnect();

    clientconnection client4(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User4");
    QSignalSpy spy4(&client4, SIGNAL(messageReceived(QString)));
    spy4.wait(50);

    QCOMPARE(Convert_Message_To_Json(spy4.takeAt(0).at(0).toString())["Type"], "CONNECT_SUCCESSFUL");
}

/*
 * Helper function to send bids to the server, by default out_of_turn is false such that moves are made according to player turn
 * */
void TestServer::send_bid(QString suit, QString rank, bool out_of_turn)
{
    int from = out_of_turn ? (server->bridgeServer->GS.getPlayerTurn() + 1) % 4 : server->bridgeServer->GS.getPlayerTurn();
    QJsonObject bid_send = clients[from]->CreateJObject(clients[from]->GenerateMessage("BID_SEND"));
    QJsonObject bid = {qMakePair(QString("Suit"), QJsonValue(suit)), qMakePair(QString("Rank"), QJsonValue(rank))};
    bid_send["Bid"] = bid;
    bid_send["Id"] = clients[from]->id;
    clients[from]->SendMessageToServer(clients[from]->CreateJString(bid_send));
}

/*
 * Helper function to send moves to the server, by default out_of_turn is false such that moves are made according to player turn,
 * an id can also be specified to verify whether the server rejects messages from invalid IDs
 * */
void TestServer::send_move(QString suit, QString rank, bool out_of_turn, int id)
{
    int from = -1;
    if(id == -1)
        from = out_of_turn ? (server->bridgeServer->GS.getPlayerTurn() + 1) % 4 : server->bridgeServer->GS.getPlayerTurn();
    else
        from = id;

    QJsonObject move_send = clients[from]->CreateJObject(clients[from]->GenerateMessage("MOVE_SEND"));
    QJsonObject move = {qMakePair(QString("Suit"), QJsonValue(suit)), qMakePair(QString("Rank"), QJsonValue(rank))};
    move_send["Move"] = move;
    move_send["Id"] = clients[from]->id;
    clients[from]->SendMessageToServer(clients[from]->CreateJString(move_send));
}

/*
 * Tests a variety of bids and checks whether they are valid or invalid
 * */
void TestServer::TestValidInvalidBid()
{
    TestDeal(); // west sent bid

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(13).at(0).toString(), "Bid Valid");

    send_bid("NT", "2", true); // out of turn bid

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(14).at(0).toString(), "Bid Invalid");

    send_bid("C", "2"); // north bid

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(15).at(0).toString(), "Bid Valid");

    send_bid("NT", "1"); // east bid, rank invalid

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(16).at(0).toString(), "Bid Invalid");

    send_bid("D", "2"); // east bid

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(17).at(0).toString(), "Bid Valid");

    send_bid("C", "2"); // south bid, suit invalid

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(18).at(0).toString(), "Bid Invalid");

    send_bid("S", "2"); // south bid

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(19).at(0).toString(), "Bid Valid");

    send_bid("C", "3"); // west bid

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(20).at(0).toString(), "Bid Valid");

    send_bid("C", "3"); // north bid invalid

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(21).at(0).toString(), "Bid Invalid");

}

/*
 * Tests a variety of moves and checks whether they correctly return valid or invalid, also plays an entire deal
 * with the end result being that NS wins 9 tricks, with a contract of 4 Clubs.
 * */
void TestServer::PassAndPlay()
{
    send_bid("PASS", NULL); // west pass
    spyServerReception->wait(50);
    send_bid("PASS", NULL); // north pass
    spyServerReception->wait(50);
    send_bid("PASS", NULL); // east pass
    spyServerReception->wait(50);

    QVERIFY(server->bridgeServer->GS.getMoveStage() == true); // verify that we are in play stage after three passes

    send_move("C", "2", true); // out of turn
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(28).at(0).toString(), "Move Invalid");

    send_move("C", "2"); // west, not in hand
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(29).at(0).toString(), "Move Invalid");

    send_move("NT", "2"); //NT not valid card
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(30).at(0).toString(), "Move Invalid");

    send_move("Pass", "2"); // pass invalid
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(31).at(0).toString(), "Move Invalid");

    send_move("Double", "2"); // double invalid
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(32).at(0).toString(), "Move Invalid");

    send_move("Redouble", "2"); // redouble invalid
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(33).at(0).toString(), "Move Invalid");

    send_move("C", "1"); // No "1" card
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(34).at(0).toString(), "Move Invalid");

    send_move("C", "11"); // No "11" card
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(35).at(0).toString(), "Move Invalid");

    send_move("S", "2"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(36).at(0).toString(), "Move Valid");

    send_move("S", "3", false, 2); // north dummy hand
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(37).at(0).toString(), "Move Valid");

    send_move("S", "4"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(38).at(0).toString(), "Move Valid");

    send_move("C", "8"); // south invalid, can follow suit but doesn't
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(39).at(0).toString(), "Move Invalid");

    send_move("S", "5"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(40).at(0).toString(), "Move Valid");

    send_move("H", "2"); // south won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(41).at(0).toString(), "Move Valid");

    send_move("H", "3"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(42).at(0).toString(), "Move Valid");

    send_move("H", "8", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(43).at(0).toString(), "Move Valid");

    send_move("H", "5"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(44).at(0).toString(), "Move Valid");

    send_move("H", "4"); // north won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(45).at(0).toString(), "Move Valid");

    send_move("H", "9"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(46).at(0).toString(), "Move Valid");

    send_move("H", "A"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(47).at(0).toString(), "Move Valid");

    send_move("H", "7"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(48).at(0).toString(), "Move Valid");

    send_move("H", "6"); // south won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(49).at(0).toString(), "Move Valid");

    send_move("H", "J"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(50).at(0).toString(), "Move Valid");

    send_move("H", "Q", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(51).at(0).toString(), "Move Valid");

    send_move("H", "K"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(52).at(0).toString(), "Move Valid");

    send_move("D", "6"); // east won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(53).at(0).toString(), "Move Valid");

    send_move("D", "7"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(54).at(0).toString(), "Move Valid");

    send_move("D", "Q"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(55).at(0).toString(), "Move Valid");

    send_move("D", "K", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(56).at(0).toString(), "Move Valid");

    send_move("D", "5", false, 2); // north won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(57).at(0).toString(), "Move Valid");

    send_move("D", "10"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(58).at(0).toString(), "Move Valid");

    send_move("D", "J"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(59).at(0).toString(), "Move Valid");

    send_move("D", "4"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(60).at(0).toString(), "Move Valid");

    send_move("D", "3"); // south won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(61).at(0).toString(), "Move Valid");

    send_move("D", "8"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(62).at(0).toString(), "Move Valid");

    send_move("D", "9", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(63).at(0).toString(), "Move Valid");

    send_move("D", "A"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(64).at(0).toString(), "Move Valid");

    send_move("S", "Q"); // east won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(65).at(0).toString(), "Move Valid");

    send_move("S", "K"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(66).at(0).toString(), "Move Valid");

    send_move("S", "A"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(67).at(0).toString(), "Move Valid");

    send_move("S", "7", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(68).at(0).toString(), "Move Valid");

    send_move("S", "6"); // west won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(69).at(0).toString(), "Move Valid");

    send_move("S", "J", false, 2); // north dummy
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(70).at(0).toString(), "Move Valid");

    send_move("S", "8"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(71).at(0).toString(), "Move Valid");

    send_move("S", "9"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(72).at(0).toString(), "Move Valid");

    send_move("C", "2", false, 2); // north won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(73).at(0).toString(), "Move Valid");

    send_move("C", "3"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(74).at(0).toString(), "Move Valid");

    send_move("C", "4"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(75).at(0).toString(), "Move Valid");

    send_move("C", "5"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(76).at(0).toString(), "Move Valid");

    send_move("S", "10"); // west won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(77).at(0).toString(), "Move Valid");

    send_move("C", "6", false, 2); // north dummy
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(78).at(0).toString(), "Move Valid");

    send_move("C", "7"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(79).at(0).toString(), "Move Valid");

    send_move("C", "8"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(80).at(0).toString(), "Move Valid");

    send_move("H", "10"); // south won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(81).at(0).toString(), "Move Valid");

    send_move("C", "9"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(82).at(0).toString(), "Move Valid");

    send_move("C", "10", false, 2); // north dummy
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(83).at(0).toString(), "Move Valid");

    send_move("D", "2"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(84).at(0).toString(), "Move Valid");

    send_move("C", "A", false, 2); // north won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(85).at(0).toString(), "Move Valid");

    send_move("C", "J"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(86).at(0).toString(), "Move Valid");

    send_move("C", "Q"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(87).at(0).toString(), "Move Valid");

    send_move("C", "K"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(88).at(0).toString(), "Move Valid");
}

void TestServer::PassAndPlay2()
{
    send_bid("PASS", NULL); // west pass
    spyServerReception->wait(50);
    send_bid("PASS", NULL); // north pass
    spyServerReception->wait(50);
    send_bid("PASS", NULL); // east pass
    spyServerReception->wait(50);

    QVERIFY(server->bridgeServer->GS.getMoveStage() == true); // verify that we are in play stage after three passes

    send_move("C", "2", true); // out of turn
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(28).at(0).toString(), "Move Invalid");

    send_move("C", "2"); // west, not in hand
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(29).at(0).toString(), "Move Invalid");

    send_move("NT", "2"); //NT not valid card
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(30).at(0).toString(), "Move Invalid");

    send_move("Pass", "2"); // pass invalid
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(31).at(0).toString(), "Move Invalid");

    send_move("Double", "2"); // double invalid
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(32).at(0).toString(), "Move Invalid");

    send_move("Redouble", "2"); // redouble invalid
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(33).at(0).toString(), "Move Invalid");

    send_move("C", "1"); // No "1" card
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(34).at(0).toString(), "Move Invalid");

    send_move("C", "11"); // No "11" card
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(35).at(0).toString(), "Move Invalid");

    send_move("S", "A"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(36).at(0).toString(), "Move Valid");

    send_move("S", "3", false, 2); // north dummy hand
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(37).at(0).toString(), "Move Valid");

    send_move("S", "4"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(38).at(0).toString(), "Move Valid");

    send_move("C", "8"); // south invalid, can follow suit but doesn't
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(39).at(0).toString(), "Move Invalid");

    send_move("S", "5"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(40).at(0).toString(), "Move Valid");

    send_move("C", "K"); // west won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(41).at(0).toString(), "Move Valid");

    send_move("C", "A", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(42).at(0).toString(), "Move Valid");

    send_move("C", "J"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(43).at(0).toString(), "Move Valid");

    send_move("C", "4"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(44).at(0).toString(), "Move Valid");

    send_move("H", "4", false, 2); // north won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(45).at(0).toString(), "Move Valid");

    send_move("H", "K"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(46).at(0).toString(), "Move Valid");

    send_move("H", "A"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(47).at(0).toString(), "Move Valid");

    send_move("H", "J"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(48).at(0).toString(), "Move Valid");

    send_move("H", "6"); // south won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(49).at(0).toString(), "Move Valid");

    send_move("H", "7"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(50).at(0).toString(), "Move Valid");

    send_move("H", "8", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(51).at(0).toString(), "Move Valid");

    send_move("H", "5"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(52).at(0).toString(), "Move Valid");

    send_move("H", "Q"); // north won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(53).at(0).toString(), "Move Valid");

    send_move("H", "9"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(54).at(0).toString(), "Move Valid");

    send_move("H", "2"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(55).at(0).toString(), "Move Valid");

    send_move("H", "3"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(56).at(0).toString(), "Move Valid");

    send_move("D", "5", false, 2); // north won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(57).at(0).toString(), "Move Valid");

    send_move("D", "10"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(58).at(0).toString(), "Move Valid");

    send_move("D", "J"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(59).at(0).toString(), "Move Valid");

    send_move("D", "4"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(60).at(0).toString(), "Move Valid");

    send_move("D", "3"); // south won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(61).at(0).toString(), "Move Valid");

    send_move("D", "8"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(62).at(0).toString(), "Move Valid");

    send_move("D", "9", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(63).at(0).toString(), "Move Valid");

    send_move("D", "A"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(64).at(0).toString(), "Move Valid");

    send_move("S", "Q"); // east won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(65).at(0).toString(), "Move Valid");

    send_move("S", "9"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(66).at(0).toString(), "Move Valid");

    send_move("S", "10"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(67).at(0).toString(), "Move Valid");

    send_move("S", "7", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(68).at(0).toString(), "Move Valid");

    send_move("S", "8"); // east won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(69).at(0).toString(), "Move Valid");

    send_move("S", "K"); // south dummy
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(70).at(0).toString(), "Move Valid");

    send_move("S", "6"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(71).at(0).toString(), "Move Valid");

    send_move("S", "J", false, 2); // north dum
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(72).at(0).toString(), "Move Valid");

    send_move("C", "8"); // south won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(73).at(0).toString(), "Move Valid");

    send_move("C", "5"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(74).at(0).toString(), "Move Valid");

    send_move("C", "2", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(75).at(0).toString(), "Move Valid");

    send_move("C", "3"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(76).at(0).toString(), "Move Valid");

    send_move("C", "Q"); // south won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(77).at(0).toString(), "Move Valid");

    send_move("C", "9"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(78).at(0).toString(), "Move Valid");

    send_move("C", "6", false, 2); // north
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(79).at(0).toString(), "Move Valid");

    send_move("C", "7"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(80).at(0).toString(), "Move Valid");

    send_move("D", "7"); // south won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(81).at(0).toString(), "Move Valid");

    send_move("D", "Q"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(82).at(0).toString(), "Move Valid");

    send_move("D", "K", false, 2); // north dummy
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(83).at(0).toString(), "Move Valid");

    send_move("D", "6"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(84).at(0).toString(), "Move Valid");

    send_move("C", "10", false, 2); // north won
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(85).at(0).toString(), "Move Valid");

    send_move("D", "2"); // east
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(86).at(0).toString(), "Move Valid");

    send_move("H", "10"); // south
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(87).at(0).toString(), "Move Valid");

    send_move("S", "2"); // west
    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(88).at(0).toString(), "Move Valid");
}

void TestServer::TestValidInvalidMove()
{
    TestValidInvalidBid(); // last bid is 4C by South, who is declarer

    PassAndPlay();

    // North won
    QCOMPARE(server->bridgeServer->GS.underTheLine[0], 60);
    QCOMPARE(server->bridgeServer->GS.RubberScore[0], 60);
}

void TestServer::TestScoring()
{
    TestValidInvalidMove();

    server->bridgeServer->GS.setPlayerTurn(2);
    send_bid("C", "4");
    spyServerReception->wait(50); // south bid

    while(spyServerReception->size() > 21){spyServerReception->removeLast();}
    PassAndPlay();
    spyServerReception->wait(50);

    QCOMPARE(server->bridgeServer->GS.underTheLine[NS], 60);
    QCOMPARE(server->bridgeServer->GS.RubberScore[NS], 60);
    QCOMPARE(server->bridgeServer->GS.underTheLine[EW], 0);
    QCOMPARE(server->bridgeServer->GS.RubberScore[EW], 50);

    server->bridgeServer->GS.setPlayerTurn(2);
    send_bid("C", "2");
    spyServerReception->wait(50); // south bid

    while(spyServerReception->size() > 21){spyServerReception->removeLast();}
    PassAndPlay();
    spyServerReception->wait(50);

    QVERIFY(server->bridgeServer->GS.IsVulnerable[NS]);
    QCOMPARE(server->bridgeServer->GS.underTheLine[NS], 0);
    QCOMPARE(server->bridgeServer->GS.RubberScore[NS], 120);
    QCOMPARE(server->bridgeServer->GS.underTheLine[EW], 0);
    QCOMPARE(server->bridgeServer->GS.RubberScore[EW], 50);

    server->bridgeServer->GS.setPlayerTurn(2);
    send_bid("NT", "3");
    spyServerReception->wait(50); // south bid

    while(spyServerReception->size() > 21){spyServerReception->removeLast();}
    PassAndPlay2();
    spyServerReception->wait(50);
    spies[0]->wait(50);

    QVERIFY(!server->bridgeServer->GS.IsVulnerable[NS]);

    QJsonObject game_end = Convert_Message_To_Json(spies[0]->takeLast().at(0).toString());
    QCOMPARE(game_end["Type"], "GAME_END");
    QCOMPARE(game_end["WinningPartnership"], "NS");
    QCOMPARE(game_end["NSscore"], 950);
    QCOMPARE(game_end["EWscore"], 50);

    QJsonObject score = Convert_Message_To_Json(spies[0]->takeLast().at(0).toString());
    QJsonObject nsscore = score["NSscores"].toObject();
    QCOMPARE(score["Type"], "SCORE");
    QCOMPARE(nsscore["trickScore"], 100);
    QCOMPARE(nsscore["rubberbonus"], 700);
    QCOMPARE(nsscore["overtricks"], 30);
}

QTEST_MAIN(TestServer)

#include "tst_testserver.moc"
