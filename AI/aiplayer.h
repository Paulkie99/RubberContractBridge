//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the AI for the bridge game of EPE321
//Author: Conrad Vos 04564210
//Last update: 07/10/2020 Revision 3
#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <QObject>
#include <iostream>
#include <QTextStream>
#include <random>
#include <string>
#include "card.h"
#include "gamestate.h"
//#include "testcustom.h"


const int deck_size = 52;   // standard deck size
const int num_players = 4;  // bridge players
const int hand_size = deck_size/num_players;   // bridge hand size

using namespace std;

class AIPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AIPlayer(int ID,QObject *parent = nullptr);
//    string DetermineMove(GameState gs);
//    QString DetermineMove(GameState *gs);
    QString DetermineMove(bool bid);

    void SetHand(Card* PH);
    void SetStatus(bool vul);
    void PrintHand();
    void Shuffle(unsigned seed = 1);
    void Deal();
    void PrintDeck();
    int GetPID();
    Card* Player_Hand[hand_size];

    // array to simulate cards in hand;
    int cards[hand_size][2];

private:
    int PID;
    GameState *gamestate = NULL;
//    Card* Player_Hand[hand_size];
    std::array<Card, deck_size> Deck;
    bool Vulnerable;


    QString Play();
    QString Bid();

signals:



};

#endif // AIPLAYER_H
