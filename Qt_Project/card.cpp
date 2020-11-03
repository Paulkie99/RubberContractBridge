/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement the card class
 * Author: Paul Claasen 18006885
 * Last update: 25/10/2020 Revision 3*/

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
void Card::print()
{
    cout << "Value: " << ValToString(value).toStdString() << ", Suit: " << SuitToString(suit).toStdString() << endl;
}
/*
 * Return the String representing the value of a card
 * */
QString Card::ValToString(int val)
{
    if(val == -1)
        val = this->value;

    switch(val)
    {
        case One:
            return "1";
        break;
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
    if(suit == -1)
        suit = this->suit;

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
        case NT:
            return "NT";
        break;
    }
    return "";
}

int Card::StringToValue(QString str)
{
    if(str == "1")
        return One;
    else if(str == "2")
        return Two;
    else if(str == "3")
        return Three;
    else if(str == "4")
        return Four;
    else if(str == "5")
        return Five;
    else if(str == "6")
        return Six;
    else if(str == "7")
        return Seven;
    else if(str == "8")
        return Eight;
    else if(str == "9")
        return Nine;
    else if(str == "10")
        return Ten;
    else if(str == "J")
        return Jack;
    else if(str == "Q")
        return Queen;
    else if(str == "K")
        return King;
    else if(str == "A")
        return Ace;
    return -1;
}

int Card::StringToSuit(QString str)
{
    if(str == "C")
        return Clubs;
    else if(str == "H")
        return Hearts;
    else if(str == "D")
        return Diamonds;
    else if(str == "S")
        return Spades;
    else if(str == "NT")
        return NT;
    else if(str == "DOUBLE")
        return Double;
    else if(str == "REDOUBLE")
        return Redouble;
    else if(str == "PASS")
        return Pass;
    return -1;
}
