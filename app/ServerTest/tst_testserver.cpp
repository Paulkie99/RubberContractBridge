/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement tests for the server
 * Author: Paul Claasen 18006885
 * Last update: 06/10/2020 Revision 1*/

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
    server = new ServerInterface(false);
    spyServerReception = new QSignalSpy(server->bridgeServer, SIGNAL(messageReceived(QString)));
    spyServerSend = new QSignalSpy(server->bridgeServer, SIGNAL(messageSent(QString)));
}

void TestServer::cleanup()
{
    delete server;
    delete spyServerReception;
    delete spyServerSend;
}

/*
 * Test connection of one client with expected success messages
 * */
void TestServer::TestIdealServerSendsAndReceives()
{
    clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), false); //connect the client to server
    // wait sufficient amount of time for all messages to be sent/received
    spyServerReception->wait(100);
    spyServerSend->wait(100);
    QList<QVariant> args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Hello There"); // first messsage received should be "Hello There"

    args = spyServerSend->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Id\":0,\"Type\":\"CONNECT_SUCCESSFUL\"}"); // Server should reply saying that connection was successful

    args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Alias\":\"Player123\",\"Id\":0,\"Password\":\"password123\",\"Type\":\"CONNECT_REQUEST\"}"); // Server should then receive username and password info

    args = spyServerSend->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Id\":0,\"Type\":\"AUTH_SUCCESSFUL\"}"); // server should reply saying that the user was successfully authenticated
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
    QCOMPARE(args.at(0).toString(), "Hello There"); // first messsage received should be "Hello There"

    args = spyServerSend->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Id\":0,\"Type\":\"CONNECT_SUCCESSFUL\"}"); // Server should reply saying that connection was successful

    args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Alias\":\"Player123\",\"Id\":0,\"Password\":\"\",\"Type\":\"CONNECT_REQUEST\"}"); // Server should then receive username and password info (with empty password)

    args = spyServerSend->takeAt(0); // server should reply saying that the user was could not be authenticated
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "AUTH_UNSUCCESSFUL");
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Description"], "Username/password invalid");
}

/*
 * Test whether the server logic branches correctly according to the message received
 * */
void TestServer::TestInputBranch()
{
    clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), false); //connect the client to server
    // wait sufficient amount of time for all messages to be sent/received
    spyServerReception->wait(100);
    spyServerSend->wait(100);
    QList<QVariant> args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Hello There"); // first messsage received should be "Hello There"

    args = spyServerSend->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Id\":0,\"Type\":\"CONNECT_SUCCESSFUL\"}"); // Server should reply saying that connection was successful

    args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Alias\":\"Player123\",\"Id\":0,\"Password\":\"password123\",\"Type\":\"CONNECT_REQUEST\"}"); // Server should then receive username and password info

    args = spyServerSend->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Id\":0,\"Type\":\"AUTH_SUCCESSFUL\"}"); // server should reply saying that the user was successfully authenticated

    QJsonObject ping = client.CreateJObject(client.GenerateMessage("PING"));
    ping["Id"] = 0;
    client.SendMessageToServer(client.CreateJString(ping)); // PING server
    spyServerSend->wait(50);
    args = spyServerSend->takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "PONG"); // server correctly sent pong

    client.SendMessageToServer(client.GenerateMessage("BID_SEND")); // send bid
    spyServerReception->wait(50);
    args = spyServerReception->takeAt(2);
    QCOMPARE(args.at(0).toString(), "Bid received"); // server received bid

    client.SendMessageToServer(client.GenerateMessage("MOVE_SEND")); // send move
    spyServerReception->wait(50);
    args = spyServerReception->takeAt(3);
    QCOMPARE(args.at(0).toString(), "Move received"); // server received move
}

/*
 * Test whether the server sends card arrays to each client after four have connected
 * */
void TestServer::TestDeal()
{
    clientconnection client1(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy1(&client1, SIGNAL(messageReceived(QString)));
    spy1.wait(100); // allow sufficient time for the client to connect and send/receive initial messages

    clientconnection client2(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy2(&client2, SIGNAL(messageReceived(QString)));
    spy2.wait(100);

    clientconnection client3(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy3(&client3, SIGNAL(messageReceived(QString)));
    spy3.wait(100);

    clientconnection client4(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy4(&client4, SIGNAL(messageReceived(QString)));
    spy4.wait(100);

    spy1.wait(100);
    spy2.wait(100);
    spy3.wait(100);

    QList<QVariant> args = spy1.takeAt(2); // shuffle not enabled, therefore expected that client 1 receives this specific card array
    QCOMPARE(args.at(0).toString(), "{\"Cards\":[{\"Suit\":0,\"Value\":0},{\"Suit\":0,\"Value\":4},{\"Suit\":0,\"Value\":8},{\"Suit\":0,\"Value\":12},{\"Suit\":1,\"Value\":3},{\"Suit\":1,\"Value\":7},{\"Suit\":1,\"Value\":11},{\"Suit\":2,\"Value\":2},{\"Suit\":2,\"Value\":6},{\"Suit\":2,\"Value\":10},{\"Suit\":3,\"Value\":1},{\"Suit\":3,\"Value\":5},{\"Suit\":3,\"Value\":9}],\"Id\":0,\"Type\":\"HAND_DEALT\"}");

    args = spy2.takeAt(2);
    QCOMPARE(args.at(0).toString(), "{\"Cards\":[{\"Suit\":0,\"Value\":1},{\"Suit\":0,\"Value\":5},{\"Suit\":0,\"Value\":9},{\"Suit\":1,\"Value\":0},{\"Suit\":1,\"Value\":4},{\"Suit\":1,\"Value\":8},{\"Suit\":1,\"Value\":12},{\"Suit\":2,\"Value\":3},{\"Suit\":2,\"Value\":7},{\"Suit\":2,\"Value\":11},{\"Suit\":3,\"Value\":2},{\"Suit\":3,\"Value\":6},{\"Suit\":3,\"Value\":10}],\"Id\":1,\"Type\":\"HAND_DEALT\"}");

    args = spy3.takeAt(2);
    QCOMPARE(args.at(0).toString(), "{\"Cards\":[{\"Suit\":0,\"Value\":2},{\"Suit\":0,\"Value\":6},{\"Suit\":0,\"Value\":10},{\"Suit\":1,\"Value\":1},{\"Suit\":1,\"Value\":5},{\"Suit\":1,\"Value\":9},{\"Suit\":2,\"Value\":0},{\"Suit\":2,\"Value\":4},{\"Suit\":2,\"Value\":8},{\"Suit\":2,\"Value\":12},{\"Suit\":3,\"Value\":3},{\"Suit\":3,\"Value\":7},{\"Suit\":3,\"Value\":11}],\"Id\":2,\"Type\":\"HAND_DEALT\"}");

    args = spy4.takeAt(2);
    QCOMPARE(args.at(0).toString(), "{\"Cards\":[{\"Suit\":0,\"Value\":3},{\"Suit\":0,\"Value\":7},{\"Suit\":0,\"Value\":11},{\"Suit\":1,\"Value\":2},{\"Suit\":1,\"Value\":6},{\"Suit\":1,\"Value\":10},{\"Suit\":2,\"Value\":1},{\"Suit\":2,\"Value\":5},{\"Suit\":2,\"Value\":9},{\"Suit\":3,\"Value\":0},{\"Suit\":3,\"Value\":4},{\"Suit\":3,\"Value\":8},{\"Suit\":3,\"Value\":12}],\"Id\":3,\"Type\":\"HAND_DEALT\"}");
}

/*
 * Function testing the shuffle() function of the server
 * */
void TestServer::TestShuffle()
{
    delete server;
    server = new ServerInterface(true); //enable shuffle function

    clientconnection client1(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy1(&client1, SIGNAL(messageReceived(QString)));
    spy1.wait(100);

    clientconnection client2(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy2(&client2, SIGNAL(messageReceived(QString)));
    spy2.wait(100);

    clientconnection client3(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy3(&client3, SIGNAL(messageReceived(QString)));
    spy3.wait(100);

    clientconnection client4(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy4(&client4, SIGNAL(messageReceived(QString)));
    spy4.wait(100);

    spy1.wait(100);
    spy2.wait(100);
    spy3.wait(100);

    QList<QVariant> args = spy1.takeAt(2); // arrays received should now be random
    QVERIFY(args.at(0).toString() != "{\"Cards\":[{\"Suit\":0,\"Value\":0},{\"Suit\":0,\"Value\":4},{\"Suit\":0,\"Value\":8},{\"Suit\":0,\"Value\":12},{\"Suit\":1,\"Value\":3},{\"Suit\":1,\"Value\":7},{\"Suit\":1,\"Value\":11},{\"Suit\":2,\"Value\":2},{\"Suit\":2,\"Value\":6},{\"Suit\":2,\"Value\":10},{\"Suit\":3,\"Value\":1},{\"Suit\":3,\"Value\":5},{\"Suit\":3,\"Value\":9}],\"Id\":0,\"Type\":\"HAND_DEALT\"}");

    args = spy2.takeAt(2);
    QVERIFY(args.at(0).toString() != "{\"Cards\":[{\"Suit\":0,\"Value\":1},{\"Suit\":0,\"Value\":5},{\"Suit\":0,\"Value\":9},{\"Suit\":1,\"Value\":0},{\"Suit\":1,\"Value\":4},{\"Suit\":1,\"Value\":8},{\"Suit\":1,\"Value\":12},{\"Suit\":2,\"Value\":3},{\"Suit\":2,\"Value\":7},{\"Suit\":2,\"Value\":11},{\"Suit\":3,\"Value\":2},{\"Suit\":3,\"Value\":6},{\"Suit\":3,\"Value\":10}],\"Id\":1,\"Type\":\"HAND_DEALT\"}");

    args = spy3.takeAt(2);
    QVERIFY(args.at(0).toString() != "{\"Cards\":[{\"Suit\":0,\"Value\":2},{\"Suit\":0,\"Value\":6},{\"Suit\":0,\"Value\":10},{\"Suit\":1,\"Value\":1},{\"Suit\":1,\"Value\":5},{\"Suit\":1,\"Value\":9},{\"Suit\":2,\"Value\":0},{\"Suit\":2,\"Value\":4},{\"Suit\":2,\"Value\":8},{\"Suit\":2,\"Value\":12},{\"Suit\":3,\"Value\":3},{\"Suit\":3,\"Value\":7},{\"Suit\":3,\"Value\":11}],\"Id\":2,\"Type\":\"HAND_DEALT\"}");

    args = spy4.takeAt(2);
    QVERIFY(args.at(0).toString() != "{\"Cards\":[{\"Suit\":0,\"Value\":3},{\"Suit\":0,\"Value\":7},{\"Suit\":0,\"Value\":11},{\"Suit\":1,\"Value\":2},{\"Suit\":1,\"Value\":6},{\"Suit\":1,\"Value\":10},{\"Suit\":2,\"Value\":1},{\"Suit\":2,\"Value\":5},{\"Suit\":2,\"Value\":9},{\"Suit\":3,\"Value\":0},{\"Suit\":3,\"Value\":4},{\"Suit\":3,\"Value\":8},{\"Suit\":3,\"Value\":12}],\"Id\":3,\"Type\":\"HAND_DEALT\"}");
}

/*
 * Test whether the server allows a fifth connection even though a lobby consists of four
 * */
void TestServer::TestConnectLobbyFull()
{
    clientconnection client1(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy1(&client1, SIGNAL(messageReceived(QString)));
    spy1.wait(100);

    clientconnection client2(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy2(&client2, SIGNAL(messageReceived(QString)));
    spy2.wait(100);

    clientconnection client3(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy3(&client3, SIGNAL(messageReceived(QString)));
    spy3.wait(100);

    clientconnection client4(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy4(&client4, SIGNAL(messageReceived(QString)));
    spy4.wait(100);

    clientconnection client5(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy5(&client5, SIGNAL(messageReceived(QString)));
    spy5.wait(100);

    QList<QVariant> args = spy5.takeAt(0); // Server should send CONNECT_UNSUCCESSFUL to fifth connecting client
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "CONNECT_UNSUCCESSFUL");
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Description"], "LOBBY_FULL");
}

/*
 * Test whether the server performs the applicable housekeeping when a user disconnects
 * */
void TestServer::TestDisconnect()
{

    clientconnection client1(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy1(&client1, SIGNAL(messageReceived(QString)));
    spy1.wait(100);

    clientconnection client2(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy2(&client2, SIGNAL(messageReceived(QString)));
    spy2.wait(100);

    clientconnection client3(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy3(&client3, SIGNAL(messageReceived(QString)));
    spy3.wait(100);

    clientconnection client4(QUrl(QStringLiteral("ws://localhost:159")), false);
    QSignalSpy spy4(&client4, SIGNAL(messageReceived(QString)));
    spy4.wait(100);

    client4.clientSocket->close();

    spyServerReception->wait(100);

    QList<QVariant> args = spyServerReception->takeAt(8);
    QVERIFY2(args.at(0).toString() == ("Client 3 disconnected"), args.at(0).toString().toStdString().c_str());
}

QTEST_MAIN(TestServer)

#include "tst_testserver.moc"
