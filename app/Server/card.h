/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* This class represents a card object and includes convenient print functions.
 * Author: Paul Claasen 18006885
 * Last update: 05/10/2020 Revision 1*/

#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QTextStream> // printing to stdout

// Enum of the card ranks in ascending order -> this makes a statement like Ace > Ten valid.
enum Card_Vals
{
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

// Enum of suit values in order of ascending rank, once again Spades > Hearts is validified.
enum Suit_Vals
{
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

class Card
{
public:
    Card();
    Card(int val, int suit_);

    int value;
    int suit;

    void print(QTextStream& out);
    QString ValToString(int val);
    QString SuitToString(int suit);
};

#endif // CARD_H
