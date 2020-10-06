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

void TestServer::TestIdealServerSendsAndReceives()
{
    clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), false);
    spyServerReception->wait(100);
    spyServerSend->wait(100);
    QList<QVariant> args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "Hello There");

    args = spyServerSend->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Id\":0,\"Type\":\"CONNECT_SUCCESSFUL\"}");

    args = spyServerReception->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Alias\":\"Player123\",\"Id\":0,\"Password\":\"password123\",\"Type\":\"CONNECT_REQUEST\"}");

    args = spyServerSend->takeAt(0);
    QCOMPARE(args.at(0).toString(), "{\"Id\":0,\"Type\":\"AUTH_SUCCESSFUL\"}");
}

void TestServer::TestDeal()
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

    spy1.wait(100);
    spy2.wait(100);
    spy3.wait(100);

    QList<QVariant> args = spy1.takeAt(2);
    QCOMPARE(args.at(0).toString(), "{\"Cards\":[{\"Suit\":0,\"Value\":0},{\"Suit\":0,\"Value\":4},{\"Suit\":0,\"Value\":8},{\"Suit\":0,\"Value\":12},{\"Suit\":1,\"Value\":3},{\"Suit\":1,\"Value\":7},{\"Suit\":1,\"Value\":11},{\"Suit\":2,\"Value\":2},{\"Suit\":2,\"Value\":6},{\"Suit\":2,\"Value\":10},{\"Suit\":3,\"Value\":1},{\"Suit\":3,\"Value\":5},{\"Suit\":3,\"Value\":9}],\"Id\":0,\"Type\":\"HAND_DEALT\"}");

    args = spy2.takeAt(2);
    QCOMPARE(args.at(0).toString(), "{\"Cards\":[{\"Suit\":0,\"Value\":1},{\"Suit\":0,\"Value\":5},{\"Suit\":0,\"Value\":9},{\"Suit\":1,\"Value\":0},{\"Suit\":1,\"Value\":4},{\"Suit\":1,\"Value\":8},{\"Suit\":1,\"Value\":12},{\"Suit\":2,\"Value\":3},{\"Suit\":2,\"Value\":7},{\"Suit\":2,\"Value\":11},{\"Suit\":3,\"Value\":2},{\"Suit\":3,\"Value\":6},{\"Suit\":3,\"Value\":10}],\"Id\":1,\"Type\":\"HAND_DEALT\"}");

    args = spy3.takeAt(2);
    QCOMPARE(args.at(0).toString(), "{\"Cards\":[{\"Suit\":0,\"Value\":2},{\"Suit\":0,\"Value\":6},{\"Suit\":0,\"Value\":10},{\"Suit\":1,\"Value\":1},{\"Suit\":1,\"Value\":5},{\"Suit\":1,\"Value\":9},{\"Suit\":2,\"Value\":0},{\"Suit\":2,\"Value\":4},{\"Suit\":2,\"Value\":8},{\"Suit\":2,\"Value\":12},{\"Suit\":3,\"Value\":3},{\"Suit\":3,\"Value\":7},{\"Suit\":3,\"Value\":11}],\"Id\":2,\"Type\":\"HAND_DEALT\"}");

    args = spy4.takeAt(2);
    QCOMPARE(args.at(0).toString(), "{\"Cards\":[{\"Suit\":0,\"Value\":3},{\"Suit\":0,\"Value\":7},{\"Suit\":0,\"Value\":11},{\"Suit\":1,\"Value\":2},{\"Suit\":1,\"Value\":6},{\"Suit\":1,\"Value\":10},{\"Suit\":2,\"Value\":1},{\"Suit\":2,\"Value\":5},{\"Suit\":2,\"Value\":9},{\"Suit\":3,\"Value\":0},{\"Suit\":3,\"Value\":4},{\"Suit\":3,\"Value\":8},{\"Suit\":3,\"Value\":12}],\"Id\":3,\"Type\":\"HAND_DEALT\"}");
}

void TestServer::TestShuffle()
{
    delete server;
    server = new ServerInterface(true);

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

    QList<QVariant> args = spy1.takeAt(2);
    QVERIFY(args.at(0).toString() != "{\"Cards\":[{\"Suit\":0,\"Value\":0},{\"Suit\":0,\"Value\":4},{\"Suit\":0,\"Value\":8},{\"Suit\":0,\"Value\":12},{\"Suit\":1,\"Value\":3},{\"Suit\":1,\"Value\":7},{\"Suit\":1,\"Value\":11},{\"Suit\":2,\"Value\":2},{\"Suit\":2,\"Value\":6},{\"Suit\":2,\"Value\":10},{\"Suit\":3,\"Value\":1},{\"Suit\":3,\"Value\":5},{\"Suit\":3,\"Value\":9}],\"Id\":0,\"Type\":\"HAND_DEALT\"}");

    args = spy2.takeAt(2);
    QVERIFY(args.at(0).toString() != "{\"Cards\":[{\"Suit\":0,\"Value\":1},{\"Suit\":0,\"Value\":5},{\"Suit\":0,\"Value\":9},{\"Suit\":1,\"Value\":0},{\"Suit\":1,\"Value\":4},{\"Suit\":1,\"Value\":8},{\"Suit\":1,\"Value\":12},{\"Suit\":2,\"Value\":3},{\"Suit\":2,\"Value\":7},{\"Suit\":2,\"Value\":11},{\"Suit\":3,\"Value\":2},{\"Suit\":3,\"Value\":6},{\"Suit\":3,\"Value\":10}],\"Id\":1,\"Type\":\"HAND_DEALT\"}");

    args = spy3.takeAt(2);
    QVERIFY(args.at(0).toString() != "{\"Cards\":[{\"Suit\":0,\"Value\":2},{\"Suit\":0,\"Value\":6},{\"Suit\":0,\"Value\":10},{\"Suit\":1,\"Value\":1},{\"Suit\":1,\"Value\":5},{\"Suit\":1,\"Value\":9},{\"Suit\":2,\"Value\":0},{\"Suit\":2,\"Value\":4},{\"Suit\":2,\"Value\":8},{\"Suit\":2,\"Value\":12},{\"Suit\":3,\"Value\":3},{\"Suit\":3,\"Value\":7},{\"Suit\":3,\"Value\":11}],\"Id\":2,\"Type\":\"HAND_DEALT\"}");

    args = spy4.takeAt(2);
    QVERIFY(args.at(0).toString() != "{\"Cards\":[{\"Suit\":0,\"Value\":3},{\"Suit\":0,\"Value\":7},{\"Suit\":0,\"Value\":11},{\"Suit\":1,\"Value\":2},{\"Suit\":1,\"Value\":6},{\"Suit\":1,\"Value\":10},{\"Suit\":2,\"Value\":1},{\"Suit\":2,\"Value\":5},{\"Suit\":2,\"Value\":9},{\"Suit\":3,\"Value\":0},{\"Suit\":3,\"Value\":4},{\"Suit\":3,\"Value\":8},{\"Suit\":3,\"Value\":12}],\"Id\":3,\"Type\":\"HAND_DEALT\"}");
}

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

    QList<QVariant> args = spy5.takeAt(0);
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Type"], "CONNECT_UNSUCCESSFUL");
    QCOMPARE(Convert_Message_To_Json(args.at(0).toString())["Description"], "LOBBY_FULL");
}

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
