//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the server for the bridge game of EPE321
//Author: Conrad Vos 04564210
//Last update: 02/10/2020 Revision 2
#include "gamestate.h"

GameState::GameState(QObject *parent) : QObject(parent)
{
    BidStage = true;
    PassCount = 0;
    for (int i = 0; i < int(sizeof(TrickScore)); i++)
    {
        TrickScore[i] = 0;
    }
    for (int i = 0; i < int(sizeof(CurrentTrick)); i++)
    {

        CurrentTrick[i] = nullptr;
    }
    Contract = 0;
    Trump = 0;
    for (int i = 0; i < int(sizeof(GameScore)); i++)
    {
        GameScore[i] = 0;
    }
    for (int i = 0; i < int(sizeof(Teams)); i++)
    {
        for (int j = 0; j < int(sizeof(Teams[i])); j++)
        {
            Teams[i][j] = 0;
        }
    }
    PlayerTurn = 0;
    Declarer = 0;
    Double = false;

    cout << "Hello From GameState!\n\n";
}

void GameState::PrintGS()
{
    cout << "The Current State of the Game: \n";
    cout << "Bidding Stage: ";
    if (BidStage)
    {
        cout << "True\n";
    }else
    {
        cout << "False\n";
    }
    cout << "PassCount: " << PassCount << endl;

    cout << "\n";
};

void GameState::SetBidStage(bool BS)
{
    BidStage = BS;
};

bool GameState::GetBidStage()
{
    return BidStage;
};

void GameState::IncreasePassCount()
{
    PassCount++;
};

void GameState::ClearPassCount()
{
    PassCount = 0;
};
