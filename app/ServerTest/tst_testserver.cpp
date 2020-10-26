/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement tests for the server
 * Author: Paul Claasen 18006885
 * Last update: 06/10/2020 Revision 1*/

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

private slots:
    void initTestCase();
    void init();
    void cleanup();

    void TestIdealServerSendsAndReceives();
    void TestAuthFailed();
    void TestInputBranch();
    void TestDeal();
    void TestConnectLobbyFull();
    void TestDisconnect();
    void TestReconnect();
    void TestValidInvalidBid();
    void TestValidInvalidMove();
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
    spyServerReception = new QSignalSpy(server->bridgeServer, SIGNAL(messageReceived(QString)));
    spyServerSend = new QSignalSpy(server->bridgeServer, SIGNAL(messageSent(QString)));
}

void TestServer::cleanup()
{
    delete server;
    delete spyServerReception;
    delete spyServerSend;
    clients.clear();
    spies.clear();
}

/*
 * Test connection of one client with expected success messages
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
 * Test that the server sends an AUTH_FAILED if the user has invalid credentials
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
 * Test whether the server logic branches correctly according to the message received
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
 * Test whether the server sends card arrays to each client after four have connected
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
 * Test whether the server allows a fifth connection even though a lobby consists of four
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
 * Test whether the server performs the applicable housekeeping when a user disconnects
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
 * Test whether the server performs the applicable housekeeping when a user disconnects
 * */
void TestServer::TestReconnect()
{
    TestDisconnect();

    clientconnection client4(QUrl(QStringLiteral("ws://localhost:159")), false, nullptr, "User4");
    QSignalSpy spy4(&client4, SIGNAL(messageReceived(QString)));
    spy4.wait(50);

    QCOMPARE(Convert_Message_To_Json(spy4.takeAt(0).at(0).toString())["Type"], "CONNECT_SUCCESSFUL");
}

void TestServer::send_bid(QString suit, QString rank, bool out_of_turn)
{
    int from = out_of_turn ? (server->bridgeServer->GS.getPlayerTurn() + 1) % 4 : server->bridgeServer->GS.getPlayerTurn();
    QJsonObject bid_send = clients[from]->CreateJObject(clients[from]->GenerateMessage("BID_SEND"));
    QJsonObject bid = {qMakePair(QString("Suit"), QJsonValue(suit)), qMakePair(QString("Rank"), QJsonValue(rank))};
    bid_send["Bid"] = bid;
    bid_send["Id"] = clients[from]->id;
    clients[from]->SendMessageToServer(clients[from]->CreateJString(bid_send));
}

void TestServer::TestValidInvalidBid()
{
    TestDeal();

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(13).at(0).toString(), "Bid Valid");

    send_bid("NT", "2", true);

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(14).at(0).toString(), "Bid Invalid");

    send_bid("NT", "2");

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(15).at(0).toString(), "Bid Valid");

    send_bid("NT", "2");

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(16).at(0).toString(), "Bid Invalid");

    send_bid("NT", "1");

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(17).at(0).toString(), "Bid Invalid");

    send_bid("NT", "3");

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(18).at(0).toString(), "Bid Valid");

    send_bid("C", "4");

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(19).at(0).toString(), "Bid Valid");

    send_bid("NT", "2");

    spyServerReception->wait(50);
    QCOMPARE(spyServerReception->takeAt(20).at(0).toString(), "Bid Valid");
}

void TestServer::TestValidInvalidMove()
{
    TestValidInvalidBid();

    send_bid("PASS", NULL);
    spyServerReception->wait(50);
    send_bid("PASS", NULL);
    spyServerReception->wait(50);
    send_bid("PASS", NULL);
    spyServerReception->wait(50);

    QVERIFY(server->bridgeServer->GS.getMoveStage() == true);
}

QTEST_MAIN(TestServer)

#include "tst_testserver.moc"
