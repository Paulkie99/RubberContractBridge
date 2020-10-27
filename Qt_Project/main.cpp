//#include "mainwindow.h"
//#include "clientconnection.h"
//#include <QApplication>
////Code used to implement the client side for the bridge game of EPE321
////Author: Jacques Human 18223916
////Last update: 05/10/2020
////#include <QCoreApplication>
//#include <QtCore/QCommandLineParser>
//#include <QtCore/QCommandLineOption>
///*
// This project serves as the client side connection of the project. The clientconnection class (.h and .cpp ) will be integrated with the
// main project to form the client side of communication. The class is included and a object is instantiated. After the object is created, it can be used to send and receive messages to and
// from the server.
// */

//int main(int argc, char *argv[])
//{
////    QApplication a(argc, argv);
////    MainWindow w;
////    //QCoreApplication a(argc, argv);
////    //clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), true); //example of how object is created
////    w.show();
////    return a.exec();
//}

#include "testgamescreen.cpp"
#include "testmainwindow.cpp"
#include <QTest>
#include <QApplication>
int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
    {
        TestMainWindow *test2 = new TestMainWindow;
        QTest::qExec(test2, argc, argv);
    }
    {
//        TestGameScreen *test1 = new TestGameScreen;
//        QTest::qExec(test1, argc, argv);
    }
        return a.exec();
    //return status;
}
