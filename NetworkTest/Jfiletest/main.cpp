//Jacques Human 18223916
//JSON message system example
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDir>

QJsonObject GenerateMessage(QString);

int main(int argc, char *argv[])
{
       QCoreApplication a(argc, argv);
       QJsonObject msg; //json object is created
       msg = GenerateMessage("CONNECT_REQUEST"); //example of message generation
       qDebug() << msg["Type"].toString(); //example of how to access elements in json object



    return a.exec();
}




/*
 *
 *
 The generate message function is used to generate a QJsonObject from a generic
message template that is stored in a json file. For example if the client needs to
send a CONNECT_REQUEST message as stated in the communication protocol, this function can be called to generate a QJsonObject
with the correct format of a CONNECT_REQUEST message. The object can then be further modified and the generic field values
can be changed to reflect the neccessary information. The object can then be sent over the network to the server (or the object can be
converted to teh format that will be sent of the network)

The function takes a string parameter. This parameter is named after the message type that must be generated. So if a CONNECT_REQUEST
must be sent, the parameter must be CONNECT_REQUEST. If it is a BID_START message, the parameter is BID_START etc.
*/

QJsonObject GenerateMessage(QString type)
{
    QString val;
    QFile file;
    QString path = "../JFILES/"; //this path needs to change to where the json files are stored
    path = path + type+".json";   //full path is created here by passing in the parameter
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    qWarning() << val;
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jObject = d.object();
    return(jObject);
}
