//Jacques Human 18223916
//JSON message system example
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDir>
//#include "TestJFile.cpp"



QString GenerateMessage(QString);
QJsonObject CreateJObject(QString value);
QString CreateJString(QJsonObject &jobj);
void TestMessageGen(QString msg);
void TestObjectCreation(QJsonObject obj);
void TestObjectToString(QString conv);

int main(int argc, char *argv[])
{
       QCoreApplication a(argc, argv);
       QString msg; //json object is created
       msg = GenerateMessage("CONNECT_REQUEST"); //example of message generation
       TestMessageGen(msg);
       QJsonObject tobject= CreateJObject(msg);
       TestObjectCreation(tobject);
       QString vals = CreateJString(tobject);
       TestObjectToString(vals);
       // TestJFile tes;
      //  tes.testCreation(msg,"CONNECT_REQUEST");


      // qDebug() << msg["Type"].toString(); //example of how to access elements in json object



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

QString GenerateMessage(QString type)
{
    QString val;
    QFile file;
    QString path = "../JFILES/";
    path = path + type + ".json";
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    //qInfo() << "Generating message: " << val;
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

QJsonObject CreateJObject(QString value)
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

QString CreateJString(QJsonObject &jobj)
{
    QJsonDocument doc(jobj);
    QString Jstring(doc.toJson(QJsonDocument::Compact));
    return(Jstring);
}

/*
 The following functions are used for testing. They receive a parameter of a certain type and print information that can only be printed if it is the correct
type of parameter. For example a string can simply be displayed but an object cannot...so if strings are tested but the functions were faulty and did not create
a string, the program would throw errors in the console
 */

void TestMessageGen(QString msg)
{
    qDebug() <<msg;
}
void TestObjectCreation(QJsonObject obj)
{
    qDebug() << obj["Type"].toString();
    qDebug() << obj["Id"].toString();

}
void TestObjectToString(QString conv)
{
    qDebug() <<conv;
}
