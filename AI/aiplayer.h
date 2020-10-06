#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <QObject>
#include <iostream>
#include <QTextStream>
#include <random>
#include "card.h"
#include "gamestate.h"

const int deck_size = 52;   // standard deck size
const int num_players = 4;  // bridge players
const int hand_size = deck_size/num_players;   // bridge hand size

using namespace std;

class AIPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AIPlayer(int ID,QObject *parent = nullptr);

private:
    int PID;
    GameState gs;
    Card* Player_Hand[hand_size];
    QString DetermineMove(GameState gamestate);

    std::array<Card, deck_size> Deck;
    void PrintHand();
    void Shuffle(unsigned seed = 1);
    void Deal();
    void PrintDeck();

signals:



};

#endif // AIPLAYER_H
