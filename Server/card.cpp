//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the server for the bridge game of EPE321
//Author: Paul Claasen 18006885
//Last update: 05/10/2020 Revision 1

#include "card.h"

Card::Card()
{

}

Card::Card(int val, int suit_) : value(val), suit(suit_)
{

}

void Card::print(QTextStream& out)
{
    out << "Value: " << ValToString(value) << ", Suit: " << SuitToString(suit);
}

QString Card::ValToString(int val)
{
    switch(val)
    {
        case Two:
            return "Two";
        break;
        case Three:
            return "Three";
        break;
        case Four:
            return "Four";
        break;
        case Five:
            return "Five";
        break;
        case Six:
            return "Six";
        break;
        case Seven:
            return "Seven";
        break;
        case Eight:
            return "Eight";
        break;
        case Nine:
            return "Nine";
        break;
        case Ten:
            return "Ten";
        break;
        case Jack:
            return "Jack";
        break;
        case Queen:
            return "Queen";
        break;
        case King:
            return "King";
        break;
        case Ace:
            return "Ace";
        break;
    }
    return "";
}

QString Card::SuitToString(int suit)
{
    switch(suit)
    {
        case Clubs:
            return "Clubs";
        break;
        case Diamonds:
            return "Diamonds";
        break;
        case Hearts:
            return "Hearts";
        break;
        case Spades:
            return "Spades";
        break;

    }
    return "";
}
