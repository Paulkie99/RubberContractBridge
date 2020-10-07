//Code used to implement the client side for the bridge game of EPE321
//Author: Jacques Human 18223916
//Last update: 05/10/2020
#include "clientconnection.h"
#include <QtCore/QDebug>
#include <QSslError>
#include <QList>

/*
 The following function is the constructor of the clientconnection class. This constructor creates a clientconnection object.
 The constructor receives a url, debug and parent parameter. The url that is passed in is the url of the server that will be connected to.
 This will allow the client side to connect to the correct server. The debug boolean value allows for a debug mode that displays messages to
 test functionality. The constructor also links the socket properties with functions such as onConnected etc. The constructor also opens
 the url and connection.
 */

clientconnection::clientconnection(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    ConnectUrl(url),
    debugOn(debug)
{
    if (debugOn)
        qDebug() << "WebSocket server:" << url;
    clientSocket = new QWebSocket();
    connect(clientSocket, &QWebSocket::connected, this, &clientconnection::onConnected);
    connect(clientSocket, &QWebSocket::aboutToClose, this, &clientconnection::closed);
   // QList<QSslCertificate> cert = QSslCertificate::fromPath(QLatin1String("C:/Users/User/localhost.cert"));
    //QSslError certerror(QSslError::SelfSignedCertificate, cert.at(0));
    //QList<QSslError> expect;
    //expect.append(certerror);
   // clientSocket.ignoreSslErrors(expect);
    clientSocket->open(QUrl(url));
}

/*
This function is used to handle incomming messages from the server. If a message is received from the server, this function will trigger.
This function displays the received message to tests functionality but will be integrated into the rest of the client application. This means that
test conditions can be placed to interperet the kind of message and the proper actions will be performed by the client side depending on the message.
For example a MOVE REQUEST can be received from the server, the function can call another function on the client side to provide a move.
 */
void clientconnection::onTextMessageReceived(QString message)
{
    emit messageReceived(message);

   // if (debugOn)
    //    qDebug() << "Message received:" << message;
    QJsonObject msgr = CreateJObject(message);
    QString type = msgr["Type"].toString();
   // qDebug() << "Message Type: " << type;
    QStringList msgTypes;
    msgTypes <<"CONNECT_UNSUCCESSFUL" <<"CONNECT_SUCCESSFUL" << "LOBBY_UPDATE" << "BID_START" << "BID_REQUEST" << "BID_UPDATE" << "BID_END" << "PLAY_START" << "MOVE_REQUEST" << "MOVE_UPDATE" << "TRICK_END" <<"PLAY_END" <<"SCORE" << "PING"<<"PONG" <<"DISCONNECT_PLAYER" <<"AUTH_UNSUCCESSFUL" <<"AUTH_SUCCESSFUL" << "HAND_DEALT";

    switch(msgTypes.indexOf(type))
    {
      case 0:
        qDebug() << "Client Received Message Type: " << msgTypes[0];
        break;

      case 1: //CONNECT_SUCCESSFUL
    {
        qDebug() << "Client Received Message Type: " << msgTypes[1];
//        SendMessageToServer()
        id = msgr["Id"].toInt();
        QJsonObject connect = CreateJObject(GenerateMessage("CONNECT_REQUEST"));
        connect["Id"] = id;
        if(debugOn)
        {
            connect["Password"] = "";
        }
        SendMessageToServer(CreateJString(connect));
        break;
    }

      case 2:
        qDebug() << "Client Received Message Type: " << msgTypes[2];
        break;

    case 3:
        qDebug() << "Client Received Message Type: " << msgTypes[3];
      break;

    case 4:
        qDebug() << "Client Received Message Type: " << msgTypes[4];
      break;

    case 5:
        qDebug() << "Client Received Message Type: " << msgTypes[5];
      break;

    case 6:
        qDebug() << "Client Received Message Type: " << msgTypes[6];
      break;

    case 7:
        qDebug() << "Client Received Message Type: " << msgTypes[7];
      break;

    case 8:
        qDebug() << "Client Received Message Type: " << msgTypes[8];
      break;

    case 9:
        qDebug() << "Client Received Message Type: " << msgTypes[9];
      break;

    case 10:
        qDebug() << "Client Received Message Type: " << msgTypes[10];
      break;

    case 11:
        qDebug() << "Client Received Message Type: " << msgTypes[11];
      break;

    case 12:
        qDebug() << "Client Received Message Type: " << msgTypes[12];
      break;

    case 13:
        qDebug() << "Client Received Message Type: " << msgTypes[13];
      break;

    case 14:
        qDebug() << "Client Received Message Type: " << msgTypes[14];
      break;

    case 15:
        qDebug() << "Client Received Message Type: " << msgTypes[15];
      break;

    case 16:
        qDebug() << "Client Received Message Type: " << msgTypes[16];
      break;

    case 17:
        qDebug() << "Client Received Message Type: " << msgTypes[17];
      break;

    case 18:
        qDebug() << "Client Received Message Type: " << msgTypes[18];
      break;

    case 19:
        qDebug() << "Client Received Message Type: " << msgTypes[19];
        qDebug() << "Message: " << CreateJString(msgr);
      break;
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
    connect(clientSocket, &QWebSocket::textMessageReceived,
            this, &clientconnection::onTextMessageReceived);
    SendMessageToServer("Hello There");



}

/*
 This function is used to send messages to teh server. It receives a message as parameter and invokes the sendTextMessage function of
 the websocket. This will be used extensively throughout the client side of the project.
 */
void clientconnection::SendMessageToServer(QString msg)
{
    qDebug() << "Client sending message: " << msg;
    clientSocket->sendTextMessage(msg);
}


void clientconnection::closed()
{
    QJsonObject disc = CreateJObject(GenerateMessage("DISCONNECT_PLAYER"));
    disc["Id"] = id;
    SendMessageToServer(CreateJString(disc));
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
    QString path = "../JFILES/";
    path = path + type + ".json";
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
//    qInfo() << "Generating message: " << val;
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
