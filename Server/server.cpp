//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the server for the bridge game of EPE321
//Author: Paul Claasen 18006885
//Last update: 04/10/2020 Revision 1

#include "server.h"

const QString JPath = "../JFILES/";

//Constructor for the server, including server name, sslmode and parent object
Server::Server(const QString &serverName, SslMode secureMode, QObject *parent) : QWebSocketServer(serverName, secureMode, parent)
{
    qInfo() << "Constructing server";
    ConnectedClients = NULL; //no users connected yet
    connectedClients = 0;
    connect(this, SIGNAL(newConnection()), //connect the QWebSocketServer::newConnection() signal to the acceptConnection() slot, to store connecting QWebSockets
            this, SLOT(acceptConnection()));
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

bool Server::Authenticate(QString username, QString password)
{
    //criteria for username and password?
    if(username != "" && password != "")
        return true;
    return false;
}

//This function accepts a new connection by storing the corresponding QWebSocket in an array
void Server::acceptConnection()
{
    qInfo() << "Client " << connectedClients << " connecting.";

    //if no users have connected before, create the QWebSocket array
    if(ConnectedClients == NULL)
        ConnectedClients = new QWebSocket*[4];

    ConnectedClients[connectedClients] = nextPendingConnection(); //add the connecting QWebSocket to the array
    connect(ConnectedClients[connectedClients++], SIGNAL(textMessageReceived(QString)),
            this, SLOT(ValidateInput(QString))); //connect the connecting QWebSocket textMessageReceived function to the validateInput function
}

//This function receives messages from clients and calls the relevant validation function based on the message type
void Server::ValidateInput(QString message)
{
        emit messageReceived(message);
        QJsonObject msg = Convert_Message_To_Json(message);
        QString type = msg["Type"].toString();
        qInfo() << "Validating message: " << type;

        if(type == "CONNECT_REQUEST")
        {
            if(!Authenticate(msg["Alias"].toString(), msg["Password"].toString()))
            {
                QJsonObject error = Convert_Message_To_Json(GenerateMessage("CONNECT_UNSUCCESSFUL"));
                error["Description"] = "Username/password invalid";
            }
        }
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
//    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
//    QJsonObject jObject = d.object();
//    return(jObject);
}
