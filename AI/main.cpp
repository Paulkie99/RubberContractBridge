//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the AI for the bridge game of EPE321
//Author: Conrad Vos 04564210
//Last update: 07/10/2020 Revision 4
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
    GameState gs;

//    GameState gs2 = gs;
    cout << "gs: \n";
    gs.PrintGS();
//    cout << "gs2: \n";
//    gs2.PrintGS();

    gs.IncreasePassCount();
    gs.SetBidStage(true);
    gs.setDeclarer(3);
    gs.setPlayerTurn(1);
    gs.setBidRoundCount(0);
    cout << "gs: \n";
    gs.PrintGS();
//    cout << "gs2: \n";
//    gs2.PrintGS();
//    gs->PrintGS();
//    gs->IncreasePassCount();
//    gs->PrintGS();
//    gs->ClearPassCount();
//    gs->PrintGS();

    Card* AIHand[13];
    AIHand[0] = new Card(5, 2);
    AIHand[1] = new Card(9, 0);
    AIHand[2] = new Card(11, 2);
    AIHand[3] = new Card(4, 2);
    AIHand[4] = new Card(5, 3);
    AIHand[5] = new Card(9, 2);
    AIHand[6] = new Card(10, 3);
    AIHand[7] = new Card(12, 3);
    AIHand[8] = new Card(10, 2);
    AIHand[9] = new Card(11, 2);
    AIHand[10] = new Card(9, 3);
    AIHand[11] = new Card(12, 3);
    AIHand[12] = new Card(11, 3);
    cout << "AI Card Objects Hand: \n";
    for (int i = 0; i < 13; i++){
        AIHand[i]->print();
    }
//    AIHand[0]->print();

    AI->SetHand(AIHand);
    cout << "\nMain CardsInHand: \n";
    for (int i = 0; i < int(AI->CardsInHand.size()); i++) {
        AI->CardsInHand[i]->print();
    }
    Card* playedCard = AI->CardsInHand[5];
    cout << "\nPlayed Card: ";
    playedCard->print();
    AI->RemoveCard(5);
    AI->RemoveCard(2);
    AI->RemoveCard(5);
    AI->RemoveCard(3);
    AI->RemoveCard(0);
    cout << "\n\nAfter Remove Hand: \n";
    AI->PrintHand();
    cout << "\nPlayed Card After Remove: ";
    playedCard->print();

    cout << "\nStart AI bid/play\n\n";

//    cout << "Value: " << AI->cards[0][0] << ", Suit: " << AI->cards[0][1] << endl;

//    AI->PrintHand();
//    QTextStream out(stdout);
//    AI->Player_Hand[6]->print(out);
//    cout << endl;
//    cout << AI->Player_Hand[0] << endl;
//    cout << AI->Player_Hand[1] << endl;

//    cout << AI->DetermineMove(true, NULL).toStdString();
    cout << AI->DetermineMove(gs).toStdString();
    cout << endl;

    cout << "\nChange to play stage\n\n";
    gs.SetBidStage(false);
    gs.trumpSuit = 3;
//    gs->PrintGS();

    // Trick cards in form [value][suit]
//    int trick[4][2] = {{8,1},{-1,-1},{-1,-1},{-1,-1}};
//    AI->TrumpSuit = 0;

//    cout << AI->DetermineMove(false, trick).toStdString();
    cout << AI->DetermineMove(gs).toStdString();

//    AI->PrintHand();

    cout << "\n\n";
    cout << "Bye World!\n" << endl;
    delete AI;

    MainWindow w;
    w.show();
    return a.exec();
}
