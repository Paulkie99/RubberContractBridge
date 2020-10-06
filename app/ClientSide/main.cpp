//Code used to implement the client side for the bridge game of EPE321
//Author: Jacques Human 18223916
//Last update: 05/10/2020
#include <QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "clientconnection.h"

/*
 This project serves as the client side connection of the project. The clientconnection class (.h and .cpp ) will be integrated with the
 main project to form the client side of communication. The class is included and a object is instantiated. After the object is created, it can be used to send and receive messages to and
 from the server.
 */


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), false); //example of how object is created
    return a.exec();
}
