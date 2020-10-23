/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement the card class
 * Author: Paul Claasen 18006885
 * Last update: 05/10/2020 Revision 1*/

#include "card.h"

/*
 * Default Card Constructor
 * */
Card::Card()
{

}

/*
 * Card Constructor, given int value and suit
 * */
Card::Card(int val, int suit_) : value(val), suit(suit_)
{

}

/*
 * Print the int value and suit of a card
 * */
void Card::print(QTextStream& out)
{
    out << "Value: " << ValToString(value) << ", Suit: " << SuitToString(suit);
}

/*
 * Return the String representing the value of a card
 * */
QString Card::ValToString(int val)
{
    switch(val)
    {
        case Two:
            return "2";
        break;
        case Three:
            return "3";
        break;
        case Four:
            return "4";
        break;
        case Five:
            return "5";
        break;
        case Six:
            return "6";
        break;
        case Seven:
            return "7";
        break;
        case Eight:
            return "8";
        break;
        case Nine:
            return "9";
        break;
        case Ten:
            return "10";
        break;
        case Jack:
            return "J";
        break;
        case Queen:
            return "Q";
        break;
        case King:
            return "K";
        break;
        case Ace:
            return "A";
        break;
    }
    return "";
}

/*
 * Return the String representing the suit of a card
 * */
QString Card::SuitToString(int suit)
{
    switch(suit)
    {
        case Clubs:
            return "C";
        break;
        case Diamonds:
            return "D";
        break;
        case Hearts:
            return "H";
        break;
        case Spades:
            return "S";
        break;

    }
    return "";
}
