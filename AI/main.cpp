//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the AI for the bridge game of EPE321
//Author: Conrad Vos 04564210
//Last update: 07/10/2020 Revision 2
#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QtDebug>
#include "aiplayer.h"
#include "gamestate.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cout << "Hello World!\n";

    AIPlayer* AI = new AIPlayer(1);
    cout << endl;
//    GameState gs;

//    GameState gs2 = gs;
//    cout << "gs: \n";
//    gs.PrintGS();
//    cout << "gs2: \n";
//    gs2.PrintGS();
//    gs.IncreasePassCount();
//    cout << "gs: \n";
//    gs.PrintGS();
//    cout << "gs2: \n";
//    gs2.PrintGS();
//    gs->PrintGS();
//    gs->IncreasePassCount();
//    gs->PrintGS();
//    gs->ClearPassCount();
//    gs->PrintGS();

    cout << "\nStart Code\n";

//    cout << "Value: " << AI->cards[0][0] << ", Suit: " << AI->cards[0][1] << endl;

//    AI->PrintHand();
//    QTextStream out(stdout);
//    AI->Player_Hand[6]->print(out);
//    cout << endl;
//    cout << AI->Player_Hand[0] << endl;
//    cout << AI->Player_Hand[1] << endl;

    cout << AI->DetermineMove(true).toStdString();
//    cout << AI->DetermineMove(true);
    cout << endl;

//    cout << "Change to play stage";
//    gs.SetBidStage(false);
//    gs->PrintGS();
//    cout << "\n\n";

//    cout << AI.DetermineMove(gs).toStdString();
//    cout << AI->DetermineMove(gs);

    cout << "\n\n";
    cout << "Bye World!\n" << endl;
    delete AI;

    MainWindow w;
    w.show();
    return a.exec();
}
