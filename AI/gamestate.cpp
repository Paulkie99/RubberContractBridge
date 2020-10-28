//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the AI for the bridge game of EPE321
//Author: Conrad Vos 04564210
//Last update: 02/10/2020 Revision 5
#include "gamestate.h"

GameState::GameState()
{
    for (int i = 0; i < 2; i++)
    {
        TrickScore[i] = 0;
    }

    CurrentTrick.clear();

    for (int i = 0; i < 2; i++)
    {
        RubberScore[i] = 0;
    }

    for (int i = 0; i < 2; i++)
    {
        underTheLine[i] = 0;
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            firstDenominationBids[i][j] = -1;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        IsVulnerable[i] = false;
    }

    qInfo() << "Created GameState";
}

GameState::GameState(const GameState& gs)
{
    BidStage = gs.BidStage;
    MoveStage = gs.MoveStage;
    PassCount = gs.PassCount;
    PlayerTurn = gs.PlayerTurn;
    Declarer = gs.Declarer;
    honorsCount = gs.honorsCount;
    honorsId = gs.honorsId;
    isGameOver = gs.isGameOver;
    bidRoundCount = gs.bidRoundCount;
    CurrentBid = gs.CurrentBid;
//    dealer = gs.dealer;
    trickCount = gs.trickCount;

    for (int i = 0; i < 2; i++)
    {
        TrickScore[i] = gs.TrickScore[i];
    }

    CurrentTrick = gs.CurrentTrick;

    for (int i = 0; i < 2; i++)
    {
        RubberScore[i] = gs.RubberScore[i];
    }
    for (int i = 0; i < 2; i++)
    {
        underTheLine[i] = gs.underTheLine[i];
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            firstDenominationBids[i][j] = gs.firstDenominationBids[i][j];
        }
    }
    for (int i = 0; i < 2; i++)
    {
        IsVulnerable[i] = gs.IsVulnerable[i];
    }
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
    cout << "Play Stage: ";
    if (MoveStage)
    {
        cout << "True\n";
    }else
    {
        cout << "False\n";
    }
    cout << "bidRoundCount: " << bidRoundCount << endl;
    cout << "PassCount: " << PassCount << endl;
//    cout << "CurrentBid: ";
//    QTextStream out(stdout);
//    CurrentBid->print(out);
//    cout << endl;
    cout << "PlayerTurn: " << PlayerTurn << endl;
    cout << "Declarer: " << Declarer << endl;
    cout << "trickCount: " << trickCount << endl;
    cout << "dummyPlayer: " << dummyPlayer << endl;


    cout << "\n";

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

//ServerClient *GameState::getDealer() const
//{
//    return dealer;
//}

//void GameState::setDealer(ServerClient *value)
//{
//    dealer = value;
//}

int GameState::getDeclarer() const
{
    return Declarer;
}

void GameState::setDeclarer(int value)
{
    Declarer = value;
    dummyPlayer = (value + 2) % 4;
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
    BidStage = true;
    MoveStage = false;
    PassCount = 0;
    PlayerTurn = dealer;
    Declarer = -1;
    honorsCount = 0;
    honorsId = -1;
    isGameOver = false;
    bidRoundCount = 0;
    CurrentBid = NULL;
    trickCount = 0;

    for (int i = 0; i < 2; i++)
    {
        TrickScore[i] = 0;
    }

    CurrentTrick.clear();
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            firstDenominationBids[i][j] = -1;
        }
    }
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
}

bool GameState::getMoveStage() const
{
    return MoveStage;
}

void GameState::setMoveStage(bool value)
{
    MoveStage = value;
};

int GameState::getDummyPlayer() const
{
    return dummyPlayer;
};

void GameState::setDummyPlayer(int id)
{
    dummyPlayer = id;
};
