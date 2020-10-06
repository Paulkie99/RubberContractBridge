//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the AI for the bridge game of EPE321
//Author: Conrad Vos 04564210
//Last update: 07/10/2020 Revision 3
#include "aiplayer.h"

AIPlayer::AIPlayer(int ID, QObject *parent) : QObject(parent)
{
    PID = ID;
    Vulnerable = false;
//    for(int card = 0; card < hand_size; ++card)
//    {
//        Player_Hand[card] = nullptr;
//    }

    cout << "Creating AIPlayer " << PID << endl;

    // Populate the cards in hand with known values
    // value is the number on the card-2, with Jack = 9, Queen = 10, King = 11, Ace = 12
    // suit is the suit, with Clubs = 0, Diamonds = 1, Hearts = 2, Spades = 3
    cards[0][0] = 5; // value
    cards[0][1] = 1; // suit

    cards[1][0] = 9; // value
    cards[1][1] = 1; // suit

    cards[2][0] = 11; // value
    cards[2][1] = 1; // suit

    cards[3][0] = 4; // value
    cards[3][1] = 2; // suit

    cards[4][0] = 8; // value
    cards[4][1] = 0; // suit

    cards[5][0] = 12; // value
    cards[5][1] = 0; // suit

    cards[6][0] = 10; // value
    cards[6][1] = 3; // suit

    cards[7][0] = 12; // value
    cards[7][1] = 3; // suit

    cards[8][0] = 10; // value
    cards[8][1] = 2; // suit

    cards[9][0] = 11; // value
    cards[9][1] = 2; // suit

    cards[10][0] = 9; // value
    cards[10][1] = 3; // suit

    cards[11][0] = 12; // value
    cards[11][1] = 3; // suit

    cards[12][0] = 11; // value
    cards[12][1] = 3; // suit


    /*
     * This following portion is used to generate a deck of cards.
     * This deck is then used to test the bidding and playing logic of the AI.
     * This will be replaced by the hand received from the server when the
     * class is integrated with the server class.
    */
    //Initialise deck - Adapted from PJ Clausen's Server class for functionallity purposes
    cout << "Constructing deck\n";
    // step through the values of the card value and suit enums and add each combination to the deck
    int count = 0;
    for(int suit = Clubs; suit <= Spades; suit++)
        for(int value = Two; value <= Ace; value++)
            Deck[count++] = Card(value, suit);

//    PrintDeck();
//    cout << endl;
    Shuffle(19);
//    cout << endl;
//    PrintDeck();
    Deal();
//    cout << endl;
//    PrintHand();
}


/*
 * A function to set the hand of the AI from the Server directly.
*/
void AIPlayer::SetHand(Card* PH)
{
    for(int card = 0; card < hand_size; ++card)
    {
        Player_Hand[card] = &PH[card];
    }
};

void AIPlayer::SetStatus(bool vul)
{
    Vulnerable = vul;
};

/*
 * Shuffle the deck
 * Adapted from PJ Clausen's Server Class
 * */
void AIPlayer::Shuffle(unsigned seed)
{
    // use 11 as seed for a relatively good hand for no trump
    // use 50 as seed for all four queens and a king
    if(seed == 1) //seed not given (or just a really lame one)
        seed = std::chrono::system_clock::now().time_since_epoch().count();

    cout << "Shuffling deck...\n";
    std::shuffle(Deck.begin(), Deck.end(), std::default_random_engine(seed));
}

/*
 * Adapted from PJ Clausen's Server Class
 * */
void AIPlayer::Deal()
{
    cout << "Dealing...\n";
//    int count = 0; //keep track of card in deck
    for(int card = 0; card < hand_size; ++card)
    {
        Player_Hand[card] = &Deck[card];
    }
}

/*
 * Print every card in the deck
 * Adapted from PJ Clausen's Server Class
 * */
void AIPlayer::PrintDeck()
{
    for(int card = 0; card < deck_size; card++)
    {
        QTextStream out(stdout);
        Deck[card].print(out);
        out << "\n";
    }
}

/*
 * Print current player hands
 * Adapted from PJ Clausen's Server Class
 * */
void AIPlayer::PrintHand()
{
    QTextStream out(stdout);
    out << "Player Hand: \n";
    for(int card = 0; card < hand_size; ++card)
    {
        Player_Hand[card]->print(out);
        out << "\n";
    }
}

int AIPlayer::GetPID()
{
    return PID;
};

QString AIPlayer::Play()
{
    return "Currently Playing";
};


/*
 * When the GameState indicates that the bidding phase is active,
 * the AI will look through the cards in its hand and determine a score
 * for each card based on the enumeration in the card class.
 * The amount it bids will depend on this score. The trump suit will depend on the majority suit
 * in the hand of the AI player.
 * The function returns a QString object, as this will later be used by the Server to validate the move that the AI made.
 */
QString AIPlayer::Bid()
{
    // The total value of the current hand
    // Ace = 4, King = 3, Queen = 2, Jack = 1, remaining = 0
    int HandValues = 0;
    int SuitNums[4] = {0, 0, 0, 0};

    // HighSuits indicate how much high cards there are for a specific suit
    // index 0 is clubs, 1 is diamonds, 2 is hearts and 3 is spades
    int HighSuits[4] = {0, 0, 0, 0};

    // Chosen trump suit...
    // Clubs = 0, Diamonds = 1, Hearts = 2, Spades = 3, NoTrump = 4
    int ChosenSuit = 0;

    // The value of the bid, from 1 to 7, or 0 for a pass
    int BidValue = 0;

/*    for (int i = 0; i < hand_size; i++)
    {
//        cout << "Card Value: " << Player_Hand[i]->value << endl;
//        HandValues += Player_Hand[i]->value;
        if (Player_Hand[i]->value == 12)
        {
            HandValues += 4;
            HighSuits[Player_Hand[i]->suit]++;
        }else
        if (Player_Hand[i]->value == 11)
        {
            HandValues += 3;
            HighSuits[Player_Hand[i]->suit]]++;
        }else
        if (Player_Hand[i]->value == 10)
        {
            HandValues += 2;
            HighSuits[Player_Hand[i]->suit]++;
        }else
        if (Player_Hand[i]->value == 9)
        {
            HandValues += 1;
            HighSuits[Player_Hand[i]->suit]++;
        }

        if (Player_Hand[i]->suit == 0)
        {
            SuitNums[0] += 1;
        }else
        if (Player_Hand[i]->suit == 1)
        {
            SuitNums[1] += 1;
        }else
        if (Player_Hand[i]->suit == 2)
        {
            SuitNums[2] += 1;
        }else
        if (Player_Hand[i]->suit == 3)
        {
            SuitNums[3] += 1;
        }
//        cout << "Batman\n";
    }
*/

    /*
     * Go through each card and count the values and how much high cards there are of each suit.
     */
    for (int i = 0; i < hand_size; i++)
    {
//        cout << "Card Value: " << cards[i][0];
//        cout << "\tCard Suit: " << cards[i][1] << endl;
        if (cards[i][0] == 12)
        {
            HandValues += 4;
            HighSuits[cards[i][1]]++;
        }else
        if (cards[i][0] == 11)
        {
            HandValues += 3;
            HighSuits[cards[i][1]]++;
        }else
        if (cards[i][0] == 10)
        {
            HandValues += 2;
            HighSuits[cards[i][1]]++;
        }else
        if (cards[i][0] == 9)
        {
            HandValues += 1;
            HighSuits[cards[i][1]]++;
        }

        if (cards[i][1] == 0)
        {
            SuitNums[0] += 1;
        }else
        if (cards[i][1] == 1)
        {
            SuitNums[1] += 1;
        }else
        if (cards[i][1] == 2)
        {
            SuitNums[2] += 1;
        }else
        if (cards[i][1] == 3)
        {
            SuitNums[3] += 1;
        }
    }

//    cout << "\n";
//    cout << "HandValues: " << HandValues << endl;
//    cout << "HighSuits: ";
//    cout << "Clubs = " << HighSuits[0] << "\tDiamonds = " << HighSuits[1] << "\tHearts = " << HighSuits[2] << "\tSpades = " << HighSuits[3];
//    cout << "\n";
//    cout << "SuitNums: ";
//    cout << "Clubs = " << SuitNums[0] << "\tDiamonds = " << SuitNums[1] << "\tHearts = " << SuitNums[2] << "\tSpades = " << SuitNums[3];
//    cout << "\n";


    /*
     * This is where the bidding logic takes place.
     * If the HandValues is less than or equal to 12, the AI should pass the bid as it is a bad hand.
     * The values above 12 is divided into 7 regions and the higher value a region is, the higher is the bid amount.
    */
    if (HandValues <= 12) {
        BidValue = 0;
    } else if (HandValues <= 16) {
        BidValue = 1;
    } else if (HandValues <= 19) {
        BidValue = 2;
    } else if (HandValues <= 23) {
        BidValue = 3;
    } else if (HandValues <= 26) {
        BidValue = 4;
    } else if (HandValues <= 30) {
        BidValue = 5;
    } else if (HandValues <= 33) {
        BidValue = 6;
    } else if (HandValues <= 37) {
        BidValue = 7;
    }

    /*
     * Use the HighSuits to determine the trump suit.
     */
    int MaxIndex = 0;
    for (int i = 1; i < 4; i++)
    {
        if (HighSuits[MaxIndex] <= HighSuits[i]) {
            MaxIndex = i;
        }
    }

    /*
     * If the hand is very good but there are not a lot of high cards in one suit,
     * this might indicate that there is a wide spread of suits. Thus a NoTrump is chosen.
     * Otherwise the suit that has the most high cards are chosen as the trump suit.
     */
    if (HighSuits[MaxIndex] < 3 && HandValues > 25) {
        ChosenSuit = 4;
    } else {
        ChosenSuit = MaxIndex;
    }

//    cout << "BidValue: " << BidValue << endl;
//    cout << "ChosenSuit: " << ChosenSuit << endl;

    QString str = "Bid";
    str.append(", Tricks: ");
    str.append(QString::number(BidValue));
    str.append(", Trump: ");
    str.append(QString::number(ChosenSuit));

    return str;
};


QString AIPlayer::DetermineMove(bool bid)
{
//    cout << "Heya\n";
    if (bid)
    {
//        cout << "Hi There\n";
        return Bid();
    }else
    {
        return Play();
    }
};


















