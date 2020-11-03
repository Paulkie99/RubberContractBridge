//Declaration
//1. I understand what plagiarism is and am aware of the University’s policy in this regard.
//2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
//printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
//departmental requirements.

//Code used to implement the AI for the bridge game of EPE321
//Author: Conrad Vos 04564210
//Last update: 07/10/2020 Revision 8
#include "aiplayer.h"

AIPlayer::AIPlayer(const QUrl &url, QObject *parent) : QObject(parent), ConnectUrl(url)
{
    PID = -1;
    Vulnerable = false;
    NumInHand = 13;
    TrumpSuit = -1;
    CardsInHand.clear();
    CardsInDummyHand.clear();
    CurrTrick.clear();
    bidReq = false;
    bidCount = 0;

    qInfo() << "Creating AIPlayer " << PID;

    // Populate the cards in hand with known values
    // value is the number on the card-2, with Jack = 9, Queen = 10, King = 11, Ace = 12
    // suit is the suit, with Clubs = 0, Diamonds = 1, Hearts = 2, Spades = 3
    /*
    cards[0][0] = 5; // value
    cards[0][1] = 2; // suit

    cards[1][0] = 9; // value
    cards[1][1] = 0; // suit

    cards[2][0] = 11; // value
    cards[2][1] = 2; // suit

    cards[3][0] = 4; // value
    cards[3][1] = 2; // suit

    cards[4][0] = 5; // value
    cards[4][1] = 3; // suit

    cards[5][0] = 12; // value
    cards[5][1] = 2; // suit

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
    */

    for (int i = 0; i < 4; i++)
    {
        trick[i][0] = 0;
        trick[i][1] = 0;
    }

    connect(&aiSocket, &QWebSocket::connected, this, &AIPlayer::onConnected);
    connect(&aiSocket, &QWebSocket::disconnected, this, &AIPlayer::closed);
    aiSocket.open(QUrl(url));
}


/*
 * A function to set the hand of the AI from the Server directly.
*/
/*void AIPlayer::SetHand(Card* PH[13])
{
    for(int card = 0; card < hand_size; ++card)
    {
        Player_Hand[card] = PH[card];
    }
    for (int i = 0; i < hand_size; i++) {
        CardsInHand.push_back(Player_Hand[i]);
    }
};*/

void AIPlayer::SetHand()
{
    for (int i = 0; i < hand_size; i++) {
        CardsInHand.push_back(Player_Hand[i]);
    }
};

/*
 * A function to set the hand of the dummy from the Server directly.
*/
void AIPlayer::SetDummyHand()
{
    for (int i = 0; i < hand_size; i++) {
        CardsInDummyHand.push_back(Dummy_Hand[i]);
    }
};



/*
 *Remove the card at the given index from AI cards
*/
void AIPlayer::RemoveCard(int index)
{
    CardsInHand.erase(CardsInHand.begin()+index);
};

/*
 *Remove the card at the given index from dummy cards
*/
void AIPlayer::RemoveDummyCard(int index)
{
    CardsInDummyHand.erase(CardsInDummyHand.begin()+index);
};

void AIPlayer::SetStatus(bool vul)
{
    Vulnerable = vul;
};

/*
 * Print current player hands
 * Adapted from PJ Clausen's Server Class
 * */
void AIPlayer::PrintHand()
{
    QTextStream out(stdout);
    out << "Player Hand: \n";
    for(int card = 0; card < int(CardsInHand.size()); ++card)
    {
//        Player_Hand[card]->print(out);
        CardsInHand[card]->print(out);
        out << "\n";
    }
}

int AIPlayer::GetPID()
{
    return PID;
};


/*
 * When the GameState indicates that the bid phase is over,
 * the AI player will begin play when it is indicated that it needs to
 * make a move by the server.
 */
/*QString AIPlayer::Play(int trk[][2])
{

    for (int i = 0; i < hand_size; i++)
    {
        cout << "Index: " << i;
        cout << "\tCard Value: " << cards[i][0];
        cout << "\tCard Suit: " << cards[i][1] << endl;
    }
    cout << "\nTrump Suit " << TrumpSuit << endl;
    cout << "\nTrick Array:\n";
    for (int i = 0; i < 4; i++)
    {
        cout << trk[i][0];
        cout << trk[i][1];
        cout << endl;
    }


    int SelectedCard[2];


    // If the AI is starting the trick, play the highest value card.
    if (trk[0][0] == -1){
        int MaxIndex = 0;
        for (int i = 0; i < NumInHand; i++)
        {
            if (cards[MaxIndex][0] <= cards[i][0]){
                MaxIndex = i;
            }
        }
        SelectedCard[0] = cards[MaxIndex][0];
        SelectedCard[1] = cards[MaxIndex][1];

        // implement when array is made dynamic
//        for (int i = MaxIndex; i < NumInHand; i++)
//        {
//            cards[i] = cards[i+1];
//        }

    } else {
        // If it is not the first to go, it should follow the lead suit, unless it can't,
        // then it will go for the trump suit and if it does not have that, it will go for
        // the lowest value card.
        int LeadSuit = trk[0][1];
        // indexes of cards that are the same as the lead suit
        int LeadIndexes[NumInHand];
        for (int i = 0; i < NumInHand; i++)
        {
            LeadIndexes[i] = -1;
        }

        int count = 0; // number of indexes
        for (int i = 0; i < NumInHand; i++)
        {
            if (cards[i][1] == LeadSuit) {
                LeadIndexes[count] = i;
                count++;
//                cout << "index: " << i << endl;
            }
        }

        int MaxIndex = -1;

        int count2 = 0;
        for (int i = 0; i < count; i++)
        {
            if (cards[LeadIndexes[count2]][0] <= cards[LeadIndexes[i]][0]) {
                MaxIndex = LeadIndexes[i];
                count2 = i;
//                cout << "Max: " << MaxIndex << endl;
            }
        }


        // Show the cards in hand if there are cards of the lead suit in the hand
//        for (int i = 0; i < count; i++)
//        {
//            cout << "Cards of Lead Suit in hand: " << cards[LeadIndexes[i]][0]<<endl;
//        }

//        cout << "Highest Card of lead suit: " << cards[LeadIndexes[MaxIndex]][0]<<endl;

//        cout << "MaxIndex: " << MaxIndex << endl;

        //If there are cards from the lead suit, play the highest card
        if (MaxIndex != -1) {
            SelectedCard[0] = cards[MaxIndex][0];
            SelectedCard[1] = cards[MaxIndex][1];
        } else
        {
            // If there are no suit of the lead suit in hand, check if there is a trump card
            // and play the smallest trump card
            int TrumpIndexes[NumInHand];
            for (int i = 0; i < NumInHand; i++)
            {
                TrumpIndexes[i] = -1;
            }
            int count3 = 0; // number of indexes
            for (int i = 0; i < NumInHand; i++)
            {
                if (cards[i][1] == TrumpSuit) {
                    TrumpIndexes[count3] = i;
                    count3++;
//                    cout << "index: " << i << endl;
                }
            }
            int MinIndex = -1;
            int count4 = 0;
            for (int i = 0; i < count3; i++)
            {
                if (cards[TrumpIndexes[count4]][0] >= cards[TrumpIndexes[i]][0]) {
                    MinIndex = TrumpIndexes[i];
                    count4 = i;
//                    cout << "Min: " << MinIndex << endl;
                }
            }

            //If a trump card is found:
            if (MinIndex != -1) {
                SelectedCard[0] = cards[MinIndex][0];
                SelectedCard[1] = cards[MinIndex][1];
            } else {
                // If no trump card is found, play the smallest card in the hand
                MinIndex = 0;
                for (int i = 1; i < NumInHand; i++)
                {
                    if (cards[MinIndex][0] >= cards[i][0]) {
                        MinIndex = i;
                    }
                }
                SelectedCard[0] = cards[MinIndex][0];
                SelectedCard[1] = cards[MinIndex][1];
            }
        }

    }

    // Return the QString object
    QString str = "Play; Selected Card: Value = ";
    str.append(QString::number(SelectedCard[0]));
    str.append(", Suit = ");
    str.append(QString::number(SelectedCard[1]));


    return str;
};
*/



/*
 * When the GameState indicates that the bid phase is over,
 * the AI player will begin play when it is indicated that it needs to
 * make a move by the server.
 * Using the dynamic CardsInHand vector.
 */
QString AIPlayer::Play(int trk[][2])
{

    for (int i = 0; i < int(CardsInHand.size()); i++)
    {
        cout << "Index: " << i;
        cout << "\tCard Value: " << CardsInHand[i]->value;
        cout << "\tCard Suit: " << CardsInHand[i]->suit << endl;
    }
    cout << "\nTrump Suit " << TrumpSuit << endl;
    cout << "\nTrick Array:\n";
    for (int i = 0; i < 4; i++)
    {
        cout << trk[i][0];
        cout << trk[i][1];
        cout << endl << endl;
    }



//    int SelectedCard[2];
    Card* SelectedCard;


    // If the AI is starting the trick, play the highest value card.
    if (trk[0][0] == -1){
        int MaxIndex = 0;
        for (int i = 0; i < int(CardsInHand.size()); i++)
        {
            if (CardsInHand[MaxIndex]->value <= CardsInHand[i]->value){
                MaxIndex = i;
            }
        }
        SelectedCard = CardsInHand[MaxIndex];
        RemoveCard(MaxIndex);
    } else {

        // If it is not the first to go, it should follow the lead suit, unless it can't,
        // then it will go for the trump suit and if it does not have that, it will go for
        // the lowest value card.
        int LeadSuit = trk[0][1];
        // indexes of cards that are the same as the lead suit
        int LeadIndexes[int(CardsInHand.size())];
        for (int i = 0; i < int(CardsInHand.size()); i++)
        {
            LeadIndexes[i] = -1;
        }

        int count = 0; // number of indexes
        for (int i = 0; i < int(CardsInHand.size()); i++)
        {
            if (CardsInHand[i]->suit == LeadSuit) {
                LeadIndexes[count] = i;
                count++;
//                cout << "index: " << i << endl;
            }
        }

        int MaxIndex = -1;
        int MinIndex = -1;

        int count2 = 0;
        int countMinLead = 0;
        for (int i = 0; i < count; i++)
        {
            if (CardsInHand[LeadIndexes[count2]]->value <= CardsInHand[LeadIndexes[i]]->value) {
                MaxIndex = LeadIndexes[i];
                count2 = i;
//                cout << "Max: " << MaxIndex << endl;
            }
            if (CardsInHand[LeadIndexes[countMinLead]]->value >= CardsInHand[LeadIndexes[i]]->value) {
                MinIndex = LeadIndexes[i];
                countMinLead = i;
            }
        }




        // If there are cards from the lead suit, play the highest card if it is higher than the
        // previously played cards, otherwise play the lowest card of the lead suit.
        if (MaxIndex != -1) {

//            cout << "Min in Has Lead: " << MinIndex << endl;
//            cout << "Max in Has Lead: " << MaxIndex << endl;

            for (int i = 0; i < 4; i++){
                if (trk[i][1] == CardsInHand[MaxIndex]->suit){
                    if (trk[i][0] >= CardsInHand[MaxIndex]->value){
                        SelectedCard = CardsInHand[MinIndex];
                        RemoveCard(MinIndex);
                    } else {
                        SelectedCard = CardsInHand[MaxIndex];
                        RemoveCard(MaxIndex);
                    }
                }
            }
//            SelectedCard = CardsInHand[MaxIndex];
//            RemoveCard(MaxIndex);
        } else
        {

            // If there are no suit of the lead suit in hand, check if there is a trump card
            // and play the smallest trump card
            int TrumpIndexes[int(CardsInHand.size())];
            for (int i = 0; i < int(CardsInHand.size()); i++)
            {
                TrumpIndexes[i] = -1;
            }
            int count3 = 0; // number of indexes
            for (int i = 0; i < int(CardsInHand.size()); i++)
            {
                if (CardsInHand[i]->suit == TrumpSuit) {
                    TrumpIndexes[count3] = i;
                    count3++;
//                    cout << "index: " << i << endl;
                }
            }
            int MinIndex = -1;
            int count4 = 0;
            for (int i = 0; i < count3; i++)
            {
                if (CardsInHand[TrumpIndexes[count4]]->value >= CardsInHand[TrumpIndexes[i]]->value) {
                    MinIndex = TrumpIndexes[i];
                    count4 = i;
//                    cout << "Min: " << MinIndex << endl;
                }
            }

            // If a trump card is found:
            if (MinIndex != -1) {
                SelectedCard = CardsInHand[MinIndex];
                RemoveCard(MinIndex);
            } else {
                // If no trump card is found, play the smallest card in the hand
                MinIndex = 0;
                for (int i = 1; i < int(CardsInHand.size()); i++)
                {
                    if (CardsInHand[MinIndex]->value >= CardsInHand[i]->value) {
                        MinIndex = i;
                    }
                }
                SelectedCard = CardsInHand[MinIndex];
                RemoveCard(MinIndex);
            }
        }

    }

    // Return the QString object
    QString str = "Play; Selected Card: Value = ";
    str.append(QString::number(SelectedCard->value));
    str.append(", Suit = ");
    str.append(QString::number(SelectedCard->suit));

    QString mes = GenerateMessage("MOVE_SEND");
    QJsonObject move = CreateJObject(mes);
    // Create new object with updated Suit and Rank
    QJsonObject move2 = move["Move"].toObject();

    if (SelectedCard->suit == 0){
        move2["Suit"] = "C";
    }else if (SelectedCard->suit == 1){
        move2["Suit"] = "D";
    }else if (SelectedCard->suit == 2){
        move2["Suit"] = "H";
    }else if (SelectedCard->suit == 3){
        move2["Suit"] = "S";
    }


    move2["Rank"] = QString::number(SelectedCard->value);
    move["Move"] = move2;
    move["Id"] = PID;

    return CreateJString(move);
};



/*
 * When the GameState indicates that the bid phase is over,
 * the AI player will begin play when it is indicated that it needs to
 * make a move by the server.
 * Using the dummy hand.
 */
QString AIPlayer::PlayDummy(int trk[][2])
{

    for (int i = 0; i < int(CardsInDummyHand.size()); i++)
    {
        cout << "Index: " << i;
        cout << "\tCard Value: " << CardsInDummyHand[i]->value;
        cout << "\tCard Suit: " << CardsInDummyHand[i]->suit << endl;
    }
    cout << "\nTrump Suit " << TrumpSuit << endl;
    cout << "\nTrick Array:\n";
    for (int i = 0; i < 4; i++)
    {
        cout << trk[i][0];
        cout << trk[i][1];
        cout << endl << endl;
    }



//    int SelectedCard[2];
    Card* SelectedCard;

    /*
     * If the AI is starting the trick, play the highest value card.
    */
    if (trk[0][0] == -1){
        int MaxIndex = 0;
        for (int i = 0; i < int(CardsInDummyHand.size()); i++)
        {
            if (CardsInDummyHand[MaxIndex]->value <= CardsInDummyHand[i]->value){
                MaxIndex = i;
            }
        }
        SelectedCard = CardsInDummyHand[MaxIndex];
        RemoveCard(MaxIndex);
    } else {
        /*
         * If it is not the first to go, it should follow the lead suit, unless it can't,
         * then it will go for the trump suit and if it does not have that, it will go for
         * the lowest value card.
        */
        int LeadSuit = trk[0][1];
        // indexes of cards that are the same as the lead suit
        int LeadIndexes[int(CardsInDummyHand.size())];
        for (int i = 0; i < int(CardsInDummyHand.size()); i++)
        {
            LeadIndexes[i] = -1;
        }

        int count = 0; // number of indexes
        for (int i = 0; i < int(CardsInDummyHand.size()); i++)
        {
            if (CardsInDummyHand[i]->suit == LeadSuit) {
                LeadIndexes[count] = i;
                count++;
//                cout << "index: " << i << endl;
            }
        }

        int MaxIndex = -1;
        int MinIndex = -1;

        int count2 = 0;
        int countMinLead = 0;
        for (int i = 0; i < count; i++)
        {
            if (CardsInDummyHand[LeadIndexes[count2]]->value <= CardsInDummyHand[LeadIndexes[i]]->value) {
                MaxIndex = LeadIndexes[i];
                count2 = i;
//                cout << "Max: " << MaxIndex << endl;
            }
            if (CardsInDummyHand[LeadIndexes[countMinLead]]->value >= CardsInDummyHand[LeadIndexes[i]]->value) {
                MinIndex = LeadIndexes[i];
                countMinLead = i;
            }
        }



        /*
         * If there are cards from the lead suit, play the highest card if it is higher than the
         * previously played cards, otherwise play the lowest card of the lead suit.
        */
        if (MaxIndex != -1) {

//            cout << "Min in Has Lead: " << MinIndex << endl;
//            cout << "Max in Has Lead: " << MaxIndex << endl;

            for (int i = 0; i < 4; i++){
                if (trk[i][1] == CardsInDummyHand[MaxIndex]->suit){
                    if (trk[i][0] >= CardsInDummyHand[MaxIndex]->value){
                        SelectedCard = CardsInDummyHand[MinIndex];
                        RemoveCard(MinIndex);
                    } else {
                        SelectedCard = CardsInDummyHand[MaxIndex];
                        RemoveCard(MaxIndex);
                    }
                }
            }
//            SelectedCard = CardsInHand[MaxIndex];
//            RemoveCard(MaxIndex);
        } else
        {
            /*
             * If there are no suit of the lead suit in hand, check if there is a trump card
             * and play the smallest trump card
            */
            int TrumpIndexes[int(CardsInDummyHand.size())];
            for (int i = 0; i < int(CardsInDummyHand.size()); i++)
            {
                TrumpIndexes[i] = -1;
            }
            int count3 = 0; // number of indexes
            for (int i = 0; i < int(CardsInDummyHand.size()); i++)
            {
                if (CardsInDummyHand[i]->suit == TrumpSuit) {
                    TrumpIndexes[count3] = i;
                    count3++;
//                    cout << "index: " << i << endl;
                }
            }
            int MinIndex = -1;
            int count4 = 0;
            for (int i = 0; i < count3; i++)
            {
                if (CardsInDummyHand[TrumpIndexes[count4]]->value >= CardsInDummyHand[TrumpIndexes[i]]->value) {
                    MinIndex = TrumpIndexes[i];
                    count4 = i;
//                    cout << "Min: " << MinIndex << endl;
                }
            }
            /*
             * If a trump card is found:
            */
            if (MinIndex != -1) {
                SelectedCard = CardsInDummyHand[MinIndex];
                RemoveCard(MinIndex);
            } else {
                /*
                 * If no trump card is found, play the smallest card in the hand
                */
                MinIndex = 0;
                for (int i = 1; i < int(CardsInDummyHand.size()); i++)
                {
                    if (CardsInDummyHand[MinIndex]->value >= CardsInDummyHand[i]->value) {
                        MinIndex = i;
                    }
                }
                SelectedCard = CardsInDummyHand[MinIndex];
                RemoveCard(MinIndex);
            }
        }

    }

    // Return the QString object
    QString str = "Play; Selected Card: Value = ";
    str.append(QString::number(SelectedCard->value));
    str.append(", Suit = ");
    str.append(QString::number(SelectedCard->suit));

    QString mes = GenerateMessage("MOVE_SEND");
    QJsonObject move = CreateJObject(mes);
    // Create new object with updated Suit and Rank
    QJsonObject move2 = move["Move"].toObject();

    if (SelectedCard->suit == 0){
        move2["Suit"] = "C";
    }else if (SelectedCard->suit == 1){
        move2["Suit"] = "D";
    }else if (SelectedCard->suit == 2){
        move2["Suit"] = "H";
    }else if (SelectedCard->suit == 3){
        move2["Suit"] = "S";
    }

    move2["Rank"] = QString::number(SelectedCard->value);
    move["Move"] = move2;
    move["Id"] = PID;

    return CreateJString(move);
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

    /*
     * This is the same as the loop below, except it uses the random Card objects array.
    */
    for (int i = 0; i < hand_size; i++)
    {
//        cout << "Card Value: " << Player_Hand[i]->value << endl;
//        HandValues += Player_Hand[i]->value;
        if (Player_Hand[i]->value == 13)
        {
            HandValues += 4;
            HighSuits[Player_Hand[i]->suit]++;
        }else
        if (Player_Hand[i]->value == 12)
        {
            HandValues += 3;
            HighSuits[Player_Hand[i]->suit]++;
        }else
        if (Player_Hand[i]->value == 11)
        {
            HandValues += 2;
            HighSuits[Player_Hand[i]->suit]++;
        }else
        if (Player_Hand[i]->value == 10)
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


    /*
     * Go through each card and count the values and how much high cards there are of each suit.
     */
/*    for (int i = 0; i < hand_size; i++)
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
    */

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

    QString str;
    if (BidValue > 0) {
        str = "Bid; ";
        str.append("Tricks: ");
        str.append(QString::number(BidValue));
        str.append("; Trump: ");
        str.append(QString::number(ChosenSuit));
        str.append(";");
    } else {
        str = "Bid; Pass; Pass;";
    }

    QString mes = GenerateMessage("BID_SEND");
    QJsonObject bid = CreateJObject(mes);
    // Create new object with updated Suit and Rank
    QJsonObject bid2 = bid["Bid"].toObject();

    if (BidValue > 0){
        if (ChosenSuit == 0){
            bid2["Suit"] = "C";
        }else if (ChosenSuit == 1){
            bid2["Suit"] = "D";
        }else if (ChosenSuit == 2){
            bid2["Suit"] = "H";
        }else if (ChosenSuit == 3){
            bid2["Suit"] = "S";
        }else if (ChosenSuit == 4){
            bid2["Suit"] = "NT";
        }
    } else {
        bid2["Suit"] = "PASS";
    }


    if (BidValue == 0) {
        bid2["Rank"] = QJsonValue::Null;
    } else {
           bid2["Rank"] = QString::number(BidValue);
        }

    // Set chosen bid Suit and Rank
    bid["Bid"] = bid2;
    bid["Id"] = PID;

    return CreateJString(bid);
};


/*
 * Determine whether to play or bid
*/
/*QString AIPlayer::DetermineMove(GameState& gs)
{
    if (gs.GetBidStage())
    {
        if (gs.getBidRoundCount() < 1){
            return Bid();
        } else {
            QString str = "Bid; Pass; Pass;";
            return str;
        }

    }else
    {
        cout << "\nBLAH BLAH BLAH\n";
        int trk[4][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        for (int i = 0; i < int(gs.CurrentTrick.size()); i++){
            trk[i][0] = gs.CurrentTrick[i]->value;
            trk[i][1] = gs.CurrentTrick[i]->suit;
        }
        TrumpSuit = gs.trumpSuit;

        return Play(trk);
    }
    return NULL;
};*/



/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/



/*
This function is used to handle incomming messages from the server. If a message is received from the server, this function will trigger.
This function displays the received message to tests functionality but will be integrated into the rest of the client application. This means that
test conditions can be placed to interperet the kind of message and the proper actions will be performed by the client side depending on the message.
For example a MOVE REQUEST can be received from the server, the function can call another function on the client side to provide a move.
 */
void AIPlayer::onTextMessageReceived(QString message)
{
    // if (debugOn)
    //    qDebug() << "Message received:" << message;
    QJsonObject msgr = CreateJObject(message);
    QString type = msgr["Type"].toString();
    // qDebug() << "Message Type: " << type;
    QStringList msgTypes;
    msgTypes <<"CONNECT_UNSUCCESSFUL" <<"CONNECT_SUCCESSFUL" << "LOBBY_UPDATE" << "BID_START" << "BID_REQUEST" << "BID_UPDATE" << "BID_END" << "PLAY_START" << "MOVE_REQUEST" << "MOVE_UPDATE" << "TRICK_END" <<"PLAY_END" <<"SCORE" << "PING"<<"PONG" <<"DISCONNECT_PLAYER"<<"AUTH_SUCCESSFUL"<<"AUTH_UNSUCCESSFUL"<<"GAME_END";

    switch(msgTypes.indexOf(type)) //Switch block that determines the type of message that was received.
    {
        case 0:
            { // CONNECT_UNSUCCESSFUL
            qDebug() << "Message Type: " << msgTypes[0];
    //        emit connectUnsuccessfulSignal(CreateJObject(message));
            break;
            }
        case 1:
        {
            // CONNECT_SUCCESSFUL
            qDebug() << "Message Type: " << msgTypes[1];
    //        emit connectSuccessfullSignal(CreateJObject(message));
    //        QString Id = msgr["Id"].toString();
            PID = msgr["Id"].toInt();

            QString msg = GenerateMessage("CONNECT_REQUEST");
            QJsonObject jmes = CreateJObject(msg);
            jmes["Id"] = QString::number(PID);
            QString password = "123";
            QString username = "AI";
            QString id = QString::number(PID);
            username.append(QString::number(PID));
            jmes["Password"] = password;
            jmes["Alias"] = username;
            jmes["Id"] = PID;

            QString qmes = CreateJString(jmes);
            SendMessageToServer(qmes);

            break;
        }
        case 2:
        {
            // LOBBY_UPDATE
            qDebug() << "Message Type: " << msgTypes[2];
    //        emit lobbyUpdateSignal(CreateJObject(message));
            break;
        }
        case 3:
        {
            CurrTrick.clear();
            // BID_START
            qDebug() << "Message Type: " << msgTypes[3];

            QJsonValue value = msgr.value("Cards");
            QJsonArray array1 = value.toArray();
            int count = 0;

            for (int i = 0; i < 13; i++){
                Player_Hand[i] = NULL;
            }

            // Loop through JSON array and populate cards array
            foreach (const QJsonValue & v, array1){
                for (int k=0;k<v.toObject().value("Rank").toArray().size();k++) {
    //                cards[count] = v.toObject().value("Suit").toString() + v.toObject().value("Rank")[k].toString();
                    int value = -1;
                    int suit = -1;
                    QString newSuit = v.toObject().value("Suit").toString();
                    if (newSuit == "C"){
                        suit = 0;
                    } else if (newSuit == "D") {
                        suit = 1;
                    }else if (newSuit == "H") {
                        suit = 2;
                    }else if (newSuit == "S") {
                        suit = 3;
                    }
                    QString newVal = v.toObject().value("Rank")[k].toString();
                    if (newVal == "2"){
                        value = 1;
                    }else if (newVal == "3") {
                        value = 2;
                    }else if (newVal == "4") {
                        value = 3;
                    }else if (newVal == "5") {
                        value = 4;
                    }else if (newVal == "6") {
                        value = 5;
                    }else if (newVal == "7") {
                        value = 6;
                    }else if (newVal == "8") {
                        value = 7;
                    }else if (newVal == "9") {
                        value = 8;
                    }else if (newVal == "10") {
                        value = 9;
                    }else if (newVal == "J") {
                        value = 10;
                    }else if (newVal == "Q") {
                        value = 11;
                    }else if (newVal == "K") {
                        value = 12;
                    }else if (newVal == "A") {
                        value = 13;
                    }

                    Player_Hand[count] = new Card(value, suit);
                    count++;
                }
            }
            SetHand();
            break;
        }
        case 4:
        {
            // BID_REQUEST
            qDebug() << "Message Type: " << msgTypes[4];
            QString bidString;

            if (!bidReq){
                bidString = Bid();
            } else {
                QString mes = GenerateMessage("BID_SEND");
                QJsonObject bid = CreateJObject(mes);
                QJsonObject bid2 = bid["Bid"].toObject();
                bid2["Suit"] = "PASS";
                bid2["Rank"] = QJsonValue::Null;
                bid["Bid"] = bid2;
                bid["Id"] = PID;
                bidString = CreateJString(bid);
            }

            SendMessageToServer(bidString);

            bidReq = true;
            bidCount++;

            break;
        }
        case 5:
        {
            // BID_UPDATE
            qDebug() << "Message Type: " << msgTypes[5];
    //        emit bidUpdateSignal(CreateJObject(message));
            break;
        }
        case 6:
        {
            // BID_END
            qDebug() << "Message Type: " << msgTypes[6];
            QString TrumpSuitString = msgr["Trump"].toString();
            if (TrumpSuitString == "C"){
                TrumpSuit = 0;
            }else if (TrumpSuitString == "D"){
                TrumpSuit = 1;
            }else if (TrumpSuitString == "H"){
                TrumpSuit = 2;
            }else if (TrumpSuitString == "S"){
                TrumpSuit = 3;
            }else {
                TrumpSuit = -1;
            }
            break;
        }
        case 7:
        {
            // PLAY_START
            CurrTrick.clear();
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 2; j++){
                    trick[i][j] = -1;
                }
            }
            qDebug() << "Message Type: " << msgTypes[7];
            QJsonValue value = msgr.value("DummyCards");
            QJsonArray array1 = value.toArray();
            int count = 0;

            for (int i = 0; i < 13; i++){
                Dummy_Hand[i] = NULL;
            }

            // Loop through JSON array and populate cards array
            foreach (const QJsonValue & v, array1){
                for (int k=0;k<v.toObject().value("Rank").toArray().size();k++) {
    //                cards[count] = v.toObject().value("Suit").toString() + v.toObject().value("Rank")[k].toString();
                    int value = -1;
                    int suit = -1;
                    QString newSuit = v.toObject().value("Suit").toString();
                    if (newSuit == "C"){
                        suit = 0;
                    } else if (newSuit == "D") {
                        suit = 1;
                    }else if (newSuit == "H") {
                        suit = 2;
                    }else if (newSuit == "S") {
                        suit = 3;
                    }
                    QString newVal = v.toObject().value("Rank")[k].toString();
                    if (newVal == "2"){
                        value = 1;
                    }else if (newVal == "3") {
                        value = 2;
                    }else if (newVal == "4") {
                        value = 3;
                    }else if (newVal == "5") {
                        value = 4;
                    }else if (newVal == "6") {
                        value = 5;
                    }else if (newVal == "7") {
                        value = 6;
                    }else if (newVal == "8") {
                        value = 7;
                    }else if (newVal == "9") {
                        value = 8;
                    }else if (newVal == "10") {
                        value = 9;
                    }else if (newVal == "J") {
                        value = 10;
                    }else if (newVal == "Q") {
                        value = 11;
                    }else if (newVal == "K") {
                        value = 12;
                    }else if (newVal == "A") {
                        value = 13;
                    }

                    Dummy_Hand[count] = new Card(value, suit);
                    count++;
                }
            }
            SetDummyHand();
            break;
        }
        case 8:
        {
            // MOVE_REQUEST
            qDebug() << "Message Type: " << msgTypes[8];

            QString PlayString;
            int trk[4][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
            for (int i = 0; i < int(CurrTrick.size()); i++){
                trk[i][0] = CurrTrick[i]->value;
                trk[i][1] = CurrTrick[i]->suit;
            }

            if (msgr["MoveDummy"] == false) {
                PlayString = Play(trk);
            } else {
                PlayString = PlayDummy(trk);
            }

            SendMessageToServer(PlayString);

            break;
        }
        case 9:
        {
            // MOVE_UPDATE
            qDebug() << "Message Type: " << msgTypes[9];
            QString Suit = msgr["Move"].toObject()["Suit"].toString();
            QString Rank = msgr["Move"].toObject()["Rank"].toString();
//            QString cardplayed = Suit + Rank;
            int suit = -1;
            int value = -1;

            if (Suit == "C"){
                suit = 0;
            } else if (Suit == "D") {
                suit = 1;
            }else if (Suit == "H") {
                suit = 2;
            }else if (Suit == "S") {
                suit = 3;
            }

            if (Rank == "2"){
                value = 1;
            }else if (Rank == "3") {
                value = 2;
            }else if (Rank == "4") {
                value = 3;
            }else if (Rank == "5") {
                value = 4;
            }else if (Rank == "6") {
                value = 5;
            }else if (Rank == "7") {
                value = 6;
            }else if (Rank == "8") {
                value = 7;
            }else if (Rank == "9") {
                value = 8;
            }else if (Rank == "10") {
                value = 9;
            }else if (Rank == "J") {
                value = 10;
            }else if (Rank == "Q") {
                value = 11;
            }else if (Rank == "K") {
                value = 12;
            }else if (Rank == "A") {
                value = 13;
            }

            Card* card = new Card(value,suit);
            CurrTrick.push_back(card);


          break;
        }
        case 10:
        {
            // TRICK_END
            qDebug() << "Message Type: " << msgTypes[10];
            CurrTrick.clear();
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 2; j++){
                    trick[i][j] = -1;
                }
            }
          break;
        }
        case 11:
        {
            // PLAY_END
            qDebug() << "Message Type: " << msgTypes[11];
    //        emit playEndSignal(CreateJObject(message));
          break;
        }
        case 12:
        {
            qDebug() << "Message Type: " << msgTypes[12];
    //        emit scoreSignal(msgr);
          break;
        }
        case 13:
        {
            // PING
            qDebug() << "Message Type: " << msgTypes[13];
            break;
        }
        case 14:
        {
            // PONG
            qDebug() << "Message Type: " << msgTypes[14];
    //        emit pongSignal(CreateJObject(message));
            break;
        }
        case 15:
        {
            // DISCONNECT_PLAYER
            qDebug() << "Message Type: " << msgTypes[15];
    //        emit disconnectPlayerSignal(CreateJObject(message));
          break;
        }
        case 16:
        {
            // AUTH_SUCCESSFUL
            qDebug() << "Message Type: " << msgTypes[16];
    //        emit authSuccessfulSignal();
          break;
        }
        case 17:
        {
            // AUTH_UNSUCCESSFUL
            qDebug() << "Message Type: " << msgTypes[16];
    //        emit authUnsuccessfulSignal(CreateJObject(message));
          break;
        }
        case 18:
        {
            //GAME_END
            qDebug() << "Message Type: " << msgTypes[17];
    //        emit gameEndSignal(CreateJObject(message));
            break;
        }


    }
}

/*
 This function is used to generate a message from a json file template. My (Jacques Human) code for the message structure for communication was
adapted here for use in the client side communication. The function receives the type of message as parameter and generates a message using the appropriate
json file. This function now only returns a string as a string will be sent over to the server. A function that converts a string to json object is also
written.
 */
QString AIPlayer::GenerateMessage(QString type)
{
    QString val;
    QFile file;

    /* Note (Ivan Cuyler): The JFILES folder needs to be in the direct parent directory of
       the project. For some reason it won't work if it is in the same folder.*/
    QString path = ":/JFILES/";
    path = path + type + ".json";
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    qInfo() << "Generating message: " << val;
    return val;
//    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
//    QJsonObject jObject = d.object();
//    return(jObject);
}


/*
 This function creates a QJsonObject from a string. This is useful because an objects properties can easily be modified.
 For example a CONNECT_REQUEST can be generated by the GenerateMessage function and then converted here to an object. The objects properties like
 Type and Id can be modified. The object can be converted back into a string and sent over the network to the server.
 */
QJsonObject AIPlayer::CreateJObject(QString value)
{
  QJsonDocument doc = QJsonDocument::fromJson(value.toUtf8());
  QJsonObject jObject = doc.object();
  return(jObject);
}

/*
 This function is used to convert a QJsonObject back to a Qstring. Qstrings is the format in which messages are sent over the network to the server.
 It is thus important to have this function that formats a json object to a string. The function that does the opposite is just as important as it will
 decode a received message to a json object.
 */
QString AIPlayer::CreateJString(QJsonObject &jobj)
{
    QJsonDocument doc(jobj);
    QString Jstring(doc.toJson(QJsonDocument::Compact));
    return(Jstring);
}


void AIPlayer::onConnected()
{
//    if (debugOn)
//        qDebug() << "WebSocket connected";
    connect(&aiSocket, &QWebSocket::textMessageReceived,
            this, &AIPlayer::onTextMessageReceived);
    SendMessageToServer("Hello There From AI");

}

/*
 This function is used to send messages to teh server. It receives a message as parameter and invokes the sendTextMessage function of
 the websocket. This will be used extensively throughout the client side of the project.
 */
void AIPlayer::SendMessageToServer(QString msg)
{
    qDebug() <<"Sending message" <<msg;
    aiSocket.sendTextMessage(msg);
}

void AIPlayer::closed()
{
    QJsonObject disc = CreateJObject(GenerateMessage("DISCONNECT_PLAYER"));
    disc["Id"] = PID;
    SendMessageToServer(CreateJString(disc));
    aiSocket.close();
}

