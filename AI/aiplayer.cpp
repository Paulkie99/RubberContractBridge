#include "aiplayer.h"

AIPlayer::AIPlayer(int ID, QObject *parent) : QObject(parent)
{
    PID = ID;
    for(int card = 0; card < hand_size; ++card)
    {
        Player_Hand[card] = NULL;
    }
    cout << "Hello from AIPlayer " << PID << "!\n";

    //Initialise deck - Adapted from PJ Clausen's Server class for functionallity purposes
    cout << "Constructing deck\n";
    int count = 0;
    for(int suit = Clubs; suit <= Spades; suit++)   // step through the values of the card value and suit enums and add each combination to the deck
        for(int value = Two; value <= Ace; value++)
            Deck[count++] = Card(value, suit);
    PrintDeck();
    cout << endl;
    Shuffle();
    cout << endl;
    PrintDeck();
    Deal();
    cout << endl;
    PrintHand();
}

/*
 * Shuffle the deck
 * Adapted from PJ Clausen's Server Class
 * */
void AIPlayer::Shuffle(unsigned seed)
{
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
    int count = 0; //keep track of card in deck
    for(int card = 0; card < hand_size; ++card)
    {
        Player_Hand[card] = &Deck[count++];
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





