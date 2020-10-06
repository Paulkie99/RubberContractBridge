#include <QApplication>
#include <iostream>
#include "aiplayer.h"
#include "gamestate.h"

using namespace std;

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

//    AIPlayer x(1);
    GameState x;
    x.PrintGS();
    x.IncreasePassCount();
    x.PrintGS();
    x.IncreasePassCount();
    x.PrintGS();
    x.ClearPassCount();
    x.PrintGS();
    x.SetBidStage(false);
    x.PrintGS();

    cout << "Hello World!\n" << endl;
    return app.exec();
}
