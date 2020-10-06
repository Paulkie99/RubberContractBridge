#include "mainwindow.h"
#include <iostream>
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cout << "Hello World!\n";
    MainWindow w;
    w.show();
    return a.exec();
}
