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

#include "card.h"
#include <serverclient.h>

using namespace std;

enum Teams
{
    NS,
    EW
};

// Note that player with id 0 == North, 1 == East, etc.
enum players
{
    North,
    East,
    South,
    West
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
    QString getPlayerFromId(int id);
    QString getTeamFromId(int id);

    ServerClient *getDealer() const;
    void setDealer(ServerClient *value);

    int getDeclarer() const;
    void setDeclarer(int value);

    int getPlayerTurn() const;
    void setPlayerTurn(int value);

    Card *getCurrentBid() const;
    void setCurrentBid(Card *value);

    int getPassCount() const;
    void setPassCount(int value);

    int getBidRoundCount() const;
    void setBidRoundCount(int value);

    int firstDenominationBids[5][2];
    std::vector<Card*> CurrentTrick;
    int TrickScore[2];

    void Reset(int dealer);

    int nextPlayerTurn();

    int getTrickCount() const;
    void setTrickCount(int value);

private:
    bool BidStage;
    int bidRoundCount = 0;
    int PassCount;
    Card* CurrentBid = NULL;
    ServerClient* dealer = NULL;
    int GameScore[2];
    int PlayerTurn;
    int Declarer;
    int trickCount = 0;
    bool IsVulnerable[2];


signals:

};

#endif // GAMESTATE_H
