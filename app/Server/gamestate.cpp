//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the AI for the bridge game of EPE321
//Author: Conrad Vos 04564210
//Last update: 02/10/2020 Revision 3
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
        CurrentTrick[i] = NULL;
    }
    for (int i = 0; i < int(sizeof(GameScore)); i++)
    {
        GameScore[i] = 0;
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            firstDenominationBids[i][j] = -1;
        }
    }
    PlayerTurn = 0;
    Declarer = 0;
    for (int i = 0; i < int(sizeof(IsVulnerable)); i++)
    {
        IsVulnerable[i] = false;
    }

//    cout << "Hello From GameState!\n\n";
}

GameState::GameState(const GameState& gs, QObject *parent) : QObject(parent)
{
    BidStage = gs.BidStage;
    PassCount = gs.PassCount;
    for (int i = 0; i < int(sizeof(TrickScore)); i++)
    {
        TrickScore[i] = gs.TrickScore[i];
    }
    for (int i = 0; i < int(sizeof(CurrentTrick)); i++)
    {

        CurrentTrick[i] = gs.CurrentTrick[i];
    }
    for (int i = 0; i < int(sizeof(GameScore)); i++)
    {
        GameScore[i] = gs.GameScore[i];
    }
//    for (int i = 0; i < int(sizeof(Teams)); i++)
//    {
//        for (int j = 0; j < int(sizeof(Teams[i])); j++)
//        {
//            Teams[i][j] = gs.Teams[i][j];
//        }
//    }
    PlayerTurn = gs.PlayerTurn;
    Declarer = gs.Declarer;
    for (int i = 0; i < int(sizeof(IsVulnerable)); i++)
    {
        IsVulnerable[i] = gs.IsVulnerable[i];
    }
}


void GameState::PrintGS()
{
//    cout << "The Current State of the Game: \n";
//    cout << "Bidding Stage: ";
//    if (BidStage)
//    {
//        cout << "True\n";
//    }else
//    {
//        cout << "False\n";
//    }
//    cout << "PassCount: " << PassCount << endl;

//    cout << "\n";

//    QTextStream out(stdout);
//    out << "GameState: \n";

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
}

QString GameState::getPlayerFromId(int id)
{
    switch (id) {
    case 0:
        return "N";
    case 1:
        return "E";
    case 2:
        return "S";
    case 3:
        return "W";
    default:
        return "";
    }
}

QString GameState::getTeamFromId(int id)
{
    if(id % 2 == 0)
        return "NS";
    else
        return "EW";
}

ServerClient *GameState::getDealer() const
{
    return dealer;
}

void GameState::setDealer(ServerClient *value)
{
    dealer = value;
}

int GameState::getDeclarer() const
{
    return Declarer;
}

void GameState::setDeclarer(int value)
{
    Declarer = value;
}

int GameState::getPlayerTurn() const
{
    return PlayerTurn;
}

void GameState::setPlayerTurn(int value)
{
    PlayerTurn = value;
}

Card *GameState::getCurrentBid() const
{
    return CurrentBid;
}

void GameState::setCurrentBid(Card *value)
{
    CurrentBid = value;
}

int GameState::getPassCount() const
{
    return PassCount;
}

void GameState::setPassCount(int value)
{
    PassCount = value;
}

int GameState::getBidRoundCount() const
{
    return bidRoundCount;
}

void GameState::setBidRoundCount(int value)
{
    bidRoundCount = value;
}

void GameState::Reset(int dealer)
{
    SetBidStage(true);
    setPlayerTurn(dealer);
    setBidRoundCount(0);
    setCurrentBid(NULL);
    setDeclarer(-1);
    setPassCount(0);
}

int GameState::nextPlayerTurn()
{
    return (PlayerTurn + 1) % 4;
}

int GameState::getTrickCount() const
{
    return trickCount;
}

void GameState::setTrickCount(int value)
{
    trickCount = value;
};
