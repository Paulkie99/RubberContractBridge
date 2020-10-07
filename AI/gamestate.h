//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the AI for the bridge game of EPE321
//Author: Conrad Vos 04564210
//Last update: 02/10/2020 Revision 3
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>
#include "card.h"

using namespace std;

enum Teams
{
    NS,
    EW
};

class GameState : public QObject
{
    Q_OBJECT
public:
    explicit GameState(QObject *parent = nullptr);
    GameState(const GameState& gs, QObject *parent = nullptr);
//    ~GameState();

    void PrintGS();
    void SetBidStage(bool BS);
    bool GetBidStage();
    void IncreasePassCount();
    void ClearPassCount();


private:
    bool BidStage;
    int PassCount;
    int TrickScore[2];
    Card* CurrentTrick[4];
    int Contract;
    int Trump;
    int GameScore[2];
    int Teams[2][2];
    int PlayerTurn;
    int Declarer;
    bool Double;
    bool IsVulnerable[2];


signals:

};

#endif // GAMESTATE_H
