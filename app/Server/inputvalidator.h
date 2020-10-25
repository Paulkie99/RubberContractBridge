#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <card.h>
#include <QDebug>

class Server;
const int num_players = 4;  // bridge players
const int deck_size = 52;   // standard deck size
const int hand_size = deck_size/num_players;   // bridge hand size

class InputValidator
{
public:
    InputValidator(Server* server);
    bool isValidSocketId(int id, bool isFirstConnection=false);
    bool isValidBid(int id, int val, int suit);
    bool isValidMove(int id, int val, int suit);
    bool isEnumsContainCard(int val, int suit);
    bool isValidCardInHand(int id, int val, int suit);
    bool isValidFollowSuit(int id, int suit);

private:
    Server* server;
};

#endif // INPUTVALIDATOR_H
