#include "inputvalidator.h"
#include <server.h>

InputValidator::InputValidator(Server* server)
{
    this->server = server;
}

/*
 * This function checks if the given id is in range, and if the websocket at the specified id is non-null
 * */
bool InputValidator::isValidSocketId(int id, bool isFirstConnection)
{
    if(isFirstConnection)
    {
        if(0 <= id && id < num_players)
            return true;
    }
    else if(0 <= id && id < num_players && server->ConnectedClients[id].clientSocket)
            return true;

    qWarning() << "Invalid socket id: " << id;
    return false;
}

/*
 * Function used to validate a bid
 * */
bool InputValidator::isValidBid(int id, int val, int suit)
{
    if(!isValidSocketId(id))
        return false;

    if(!isEnumsContainCard(val, suit))
        return false;

    //TODO: Add validation logic based on GS (last bid, number of passes, etc)

    //else
    return true;
}

/*
 * Function used to validate a move (played card)
 * */
bool InputValidator::isValidMove(int id, int val, int suit)
{
    if(!isValidCardInHand(id, val, suit))
    {
        if(server->GS.getDeclarer() == id)
        {
            if(!isValidCardInHand((id + 2) % num_players, val, suit))
                return false;
        }
        else
        {
            return false;
        }
    }

    //TODO: Add validation logic based on GS (trump card, lead suit, etc)

    //else
    return true;
}

/*
 * Function to check whether card values are valid
 * */
bool InputValidator::isEnumsContainCard(int val, int suit)
{
    if(val > Ace || val < Two) // check if the value is within the values enum
        return false;

    if(suit > Spades || suit < Clubs) // check if the suit is within the suits enum
        return false;

    //else
    return true;
}

/*
 * Function to check whether the given card is in the given player's (specified by id) hand
 * */
bool InputValidator::isValidCardInHand(int id, int val, int suit)
{
    if(!isValidSocketId(id))  
            return false;

    if(!isEnumsContainCard(val, suit))
        return false;

    bool found = false;
    int player = id;
    for(int card = 0; card <= Ace; ++card)
    {
        if(server->Player_Hands[card][player])
            if(server->Player_Hands[card][player]->value == val)
                if(server->Player_Hands[card][player]->suit == suit)
                    return true;
    }
    return found;
}
