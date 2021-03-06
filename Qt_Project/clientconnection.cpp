//Code used to implement the client side for the bridge game of EPE321
//Author: Jacques Human 18223916
//Last update: 05/10/2020
#include "clientconnection.h"
#include <QtCore/QDebug>
#include <QList>
#include <QSslError>
#include <iostream>
#include "windows.h"
/*
 The following function is the constructor of the clientconnection class. This constructor creates a clientconnection object.
 The constructor receives a url, debug and parent parameter. The url that is passed in is the url of the server that will be connected to.
 This will allow the client side to connect to the correct server. The debug boolean value allows for a debug mode that displays messages to
 test functionality. The constructor also links the socket properties with functions such as onConnected etc. The constructor also opens
 the url and connection.
 */

clientconnection::clientconnection(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent), ConnectUrl(url), debugOn(debug)
{
    if (debugOn)
        qDebug() << "WebSocket server:" << url;
    connect(&clientSocket, &QWebSocket::connected, this, &clientconnection::onConnected);
    connect(&clientSocket, QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this, &clientconnection::onSslErrors);
//    connect(&clientSocket, &QWebSocket::disconnected, this, &clientconnection::closed);
//    QList<QSslCertificate> cert = QSslCertificate::fromPath(QLatin1String(":/localhost.cert"));
//    QSslError certerror(QSslError::SelfSignedCertificate, cert.at(0));
//    QList<QSslError> expect;
//    expect.append(certerror);
//    clientSocket.ignoreSslErrors(expect);
    QSslConfiguration conf = clientSocket.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1_0);
    clientSocket.setSslConfiguration(conf);
    clientSocket.ignoreSslErrors();
    clientSocket.open(QUrl(url));
}


/*
This function is used to handle incomming messages from the server. If a message is received from the server, this function will trigger.
This function displays the received message to tests functionality but will be integrated into the rest of the client application. This means that
test conditions can be placed to interperet the kind of message and the proper actions will be performed by the client side depending on the message.
For example a MOVE REQUEST can be received from the server, the function can call another function on the client side to provide a move.
 */
void clientconnection::onTextMessageReceived(QString message)
{
   // if (debugOn)
    //    qDebug() << "Message received:" << message;
    QJsonObject msgr = CreateJObject(message);
    QString type = msgr["Type"].toString();
    // qDebug() << "Message Type: " << type;
    QStringList msgTypes;
    msgTypes <<"CONNECT_UNSUCCESSFUL" <<"CONNECT_SUCCESSFUL" << "LOBBY_UPDATE" << "BID_START" << "BID_REQUEST" << "BID_UPDATE" << "BID_END" << "PLAY_START" << "MOVE_REQUEST" << "MOVE_UPDATE" << "TRICK_END" <<"PLAY_END" <<"SCORE" << "PING"<<"PONG" <<"DISCONNECT_PLAYER"<<"AUTH_SUCCESSFUL"<<"AUTH_UNSUCCESSFUL"<<"GAME_END";

    switch(msgTypes.indexOf(type)) //Switch block that determines the type of message that was received.
    {
      case 0:
        { // CONNECT_UNSUCCESSFUL
        qDebug() << "Message Type: " << msgTypes[0];
        emit connectUnsuccessfulSignal(CreateJObject(message));
        break;
        }
      case 1:
    {
        // CONNECT_SUCCESSFUL
        qDebug() << "Message Type: " << msgTypes[1];
        emit connectSuccessfullSignal(CreateJObject(message));
        break;
    }
      case 2:
    {
        // LOBBY_UPDATE
        qDebug() << "Message Type: " << msgTypes[2];
        emit lobbyUpdateSignal(CreateJObject(message));
        break;
    }
    case 3:
        {
            // BID_START
            qDebug() << "Message Type: " << msgTypes[3];

           // QString mes = GenerateMessage("BID_START");
            QJsonObject bids = CreateJObject(message);
            emit bidStartSignal(bids);
            break;
        }
    case 4:
    {
        // BID_REQUEST
        qDebug() << "Message Type: " << msgTypes[4];
        emit bidRequestSignal();
        break;
    }
    case 5:
    {
        // BID_UPDATE
        qDebug() << "Message Type: " << msgTypes[5];
        emit bidUpdateSignal(CreateJObject(message));
        break;
    }
    case 6:
    {
        // BID_END
        qDebug() << "Message Type: " << msgTypes[6];
        emit bidEndSignal(CreateJObject(message));
        break;
    }
    case 7:
    {
        // PLAY_START
        qDebug() << "Message Type: " << msgTypes[7];
        QJsonObject bids = CreateJObject(message);
        emit playStartSignal(bids);
        break;
    }
    case 8:
    {
        // MOVE_REQUEST
        qDebug() << "Message Type: " << msgTypes[8];
        emit moveRequestSignal(CreateJObject(message));
      break;
    }
    case 9:
    {
        // MOVE_UPDATE
        qDebug() << "Message Type: " << msgTypes[9];
        emit moveUpdateSignal(CreateJObject(message));
      break;
    }
    case 10:
    {
        // TRICK_END
        qDebug() << "Message Type: " << msgTypes[10];
        //Sleep(1000);
        emit trickEndSignal(CreateJObject(message));
      break;
    }
    case 11:
    {
        // PLAY_END
        qDebug() << "Message Type: " << msgTypes[11];
        emit playEndSignal(CreateJObject(message));
      break;
    }
    case 12:
    {
        qDebug() << "Message Type: " << msgTypes[12];
        emit scoreSignal(msgr);
      break;
    }
    case 13:
    {
        // PING
        qDebug() << "Message Type: " << msgTypes[13];
        emit pingSignal(CreateJObject(message));
        break;
    }
    case 14:
    {
        // PONG
        qDebug() << "Message Type: " << msgTypes[14];
        emit pongSignal(CreateJObject(message));
        break;
    }
    case 15:
    {
        // DISCONNECT_PLAYER
        qDebug() << "Message Type: " << msgTypes[15];
        emit disconnectPlayerSignal(CreateJObject(message));
      break;
    }
    case 16:
    {
        // AUTH_SUCCESSFUL
        qDebug() << "Message Type: " << msgTypes[16];
        emit authSuccessfulSignal();
      break;
    }
    case 17:
    {
        // AUTH_UNSUCCESSFUL
        qDebug() << "Message Type: " << msgTypes[16];
        emit authUnsuccessfulSignal(CreateJObject(message));
      break;
    }
    case 18:
    {
        //GAME_END
        qDebug() << "Message Type: " << msgTypes[17];
        emit gameEndSignal(CreateJObject(message));
        break;
    }


    }
}


/*
This function is triggered when the client successfully connected to the server. This function further links the socket properties with functions
in this class. This function will also display connected if the debug mode is enabled. At the moment the function also sends Hello There to the server
as a test of functionality.
 */

void clientconnection::onConnected()
{
    if (debugOn)
        qDebug() << "WebSocket connected";
    connect(&clientSocket, &QWebSocket::textMessageReceived,
            this, &clientconnection::onTextMessageReceived);
    SendMessageToServer("Hello There");

}

/*
 This function is used to send messages to teh server. It receives a message as parameter and invokes the sendTextMessage function of
 the websocket. This will be used extensively throughout the client side of the project.
 */
void clientconnection::SendMessageToServer(QString msg)
{
    qDebug() <<"Sending message" <<msg;
    clientSocket.sendTextMessage(msg);
}



/*
 This function is used to generate a message from a json file template. My (Jacques Human) code for the message structure for communication was
adapted here for use in the client side communication. The function receives the type of message as parameter and generates a message using the appropriate
json file. This function now only returns a string as a string will be sent over to the server. A function that converts a string to json object is also
written.
 */
QString clientconnection::GenerateMessage(QString type)
{
    QString val;
    QFile file;

    /* Note (Ivan Cuyler): The JFILES folder needs to be in the direct parent directory of
       the project. For some reason it won't work if it is in the same folder.*/
    QString path = ":/JFILES/";
    path = path + type + ".json";
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    qInfo() << "Generating message: " << val;
    return val;
//    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
//    QJsonObject jObject = d.object();
//    return(jObject);
}

/*
 This function creates a QJsonObject from a string. This is useful because an objects properties can easily be modified.
 For example a CONNECT_REQUEST can be generated by the GenerateMessage function and then converted here to an object. The objects properties like
 Type and Id can be modified. The object can be converted back into a string and sent over the network to the server.
 */

QJsonObject clientconnection::CreateJObject(QString value)
{
  QJsonDocument doc = QJsonDocument::fromJson(value.toUtf8());
  QJsonObject jObject = doc.object();
  return(jObject);
}

/*
 This function is used to convert a QJsonObject back to a Qstring. Qstrings is the format in which messages are sent over the network to the server.
 It is thus important to have this function that formats a json object to a string. The function that does the opposite is just as important as it will
 decode a received message to a json object.
 */

QString clientconnection::CreateJString(QJsonObject &jobj)
{
    QJsonDocument doc(jobj);
    QString Jstring(doc.toJson(QJsonDocument::Compact));
    return(Jstring);
}

void clientconnection::closed(int id)
{
    Q_UNUSED(id);
    QJsonObject disc = CreateJObject(GenerateMessage("DISCONNECT_PLAYER"));
    disc["Id"] = id;
    SendMessageToServer(CreateJString(disc));
//    clientSocket.close();
}

void clientconnection::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);

    clientSocket.ignoreSslErrors();
}
