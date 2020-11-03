/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement tests for the server
 * Author: Conrad Vos
 * Last update: 28/10/2020 Revision 2
*/

#include <aiplayer.h>
#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class TestAI : public QObject
{
    Q_OBJECT

public:
    TestAI();
    ~TestAI();

private:
    AIPlayer* player;
    Card* AIHand1[13];
    GameState* gs;

private slots:
    void initTestCase();
    void init();
    void cleanup();

    void DynamicArray();
    void LeadPlayer();
    void PlayLeadingSuit();
    void PlayTrumpSuit();
    void PlayNoSuit();
    void CalcHandPoints();
    void PassBidLowPoint();
    void BidCorrect();
    void GameStateAttributes();
};

TestAI::TestAI()
{

}

TestAI::~TestAI()
{

}

void TestAI::initTestCase()
{
}

/*
 * For each test, create a new AI
 * */
void TestAI::init()
{
//    qInfo() << "\n";
    player = new AIPlayer(0);
    AIHand1[0] = new Card(5, 2);
    AIHand1[1] = new Card(9, 0);
    AIHand1[2] = new Card(11, 2);
    AIHand1[3] = new Card(4, 2);
    AIHand1[4] = new Card(5, 3);
    AIHand1[5] = new Card(9, 2);
    AIHand1[6] = new Card(10, 3);
    AIHand1[7] = new Card(12, 2);
    AIHand1[8] = new Card(10, 2);
    AIHand1[9] = new Card(11, 2);
    AIHand1[10] = new Card(9, 3);
    AIHand1[11] = new Card(8, 3);
    AIHand1[12] = new Card(7, 3);
    player->SetHand(AIHand1);
    gs = new GameState();
}

/*
 * After each test, delete AI
 * */
void TestAI::cleanup()
{
    delete player;
    for (int i = 0; i < 13; i++){
        delete AIHand1[i];
    }
    delete gs;
}

/*
 * Unit test for the cards array.
 * Checks if length correct and if card correclty removed.
*/
void TestAI::DynamicArray()
{
    Card* AIHand2[13];
    AIHand2[0] = new Card(5, 2);
    AIHand2[1] = new Card(9, 0);
    AIHand2[2] = new Card(11, 2);
    AIHand2[3] = new Card(4, 2);
    AIHand2[4] = new Card(5, 3);
    AIHand2[5] = new Card(9, 2);
    AIHand2[6] = new Card(10, 3);
    AIHand2[7] = new Card(12, 2);
    AIHand2[8] = new Card(10, 2);
    AIHand2[9] = new Card(11, 2);
    AIHand2[10] = new Card(9, 3);
    AIHand2[11] = new Card(12, 3);
    AIHand2[12] = new Card(11, 3);

    QCOMPARE(player->CardsInHand[4]->value,AIHand2[4]->value);
    QCOMPARE(player->CardsInHand.size(), 13);
    qInfo() << "Length before remove: " << player->CardsInHand.size();
    qInfo() << "In Hand: " << player->CardsInHand[4]->value << ", Tested against: " << AIHand2[4]->value;

    player->RemoveCard(4);

    qInfo() << "Length after remove: " << player->CardsInHand.size();
    qInfo() << "After Remove In Hand: " << player->CardsInHand[4]->value << ", previous test against: " << AIHand2[4]->value;
    qInfo() << "After Remove In Hand: " << player->CardsInHand[4]->value << ", now test against: " << AIHand2[5]->value;
    QCOMPARE(player->CardsInHand[4]->value,AIHand2[5]->value);
    QCOMPARE(player->CardsInHand.size(), 12);
}

/*
 * Test whether the correct card is played when the leading player.
*/
void TestAI::LeadPlayer()
{
    qInfo() << "Card that should be played: Value = 12, Suit = 3";
    qInfo() << "Size of the current trick: " << gs->CurrentTrick.size();
    gs->SetBidStage(false);
    gs->setMoveStage(true);
    QString str = player->DetermineMove(*gs);
    qInfo() << "Received card: " << str;
    QCOMPARE(str, "Play; Selected Card: Value = 12, Suit = 2");
}

/*
 * Test whether the AI plays the most suitable card from the leading suit
*/
void TestAI::PlayLeadingSuit()
{
    gs->SetBidStage(false);
    gs->setMoveStage(true);
    Card* card1 = new Card(6,3);
    gs->CurrentTrick.push_back(card1);
    qInfo() << "Card that should be played: Value = 10, Suit = 3";
    qInfo() << "Size of the current trick: " << gs->CurrentTrick.size();
    QString str = player->DetermineMove(*gs);
    qInfo() << "Received card: " << str;
    QCOMPARE(str, "Play; Selected Card: Value = 10, Suit = 3");

    Card* card2 = new Card(12,3);
    gs->CurrentTrick.push_back(card2);
    qInfo() << "Card that should be played: Value = 5, Suit = 3";
    qInfo() << "Size of the current trick: " << gs->CurrentTrick.size();
    QString str2 = player->DetermineMove(*gs);
    qInfo() << "Received card: " << str2;
    QCOMPARE(str2, "Play; Selected Card: Value = 5, Suit = 3");

    delete card1;
    delete card2;
}

/*
 * Test whether the AI plays the most suitable card from the trump suit
*/
void TestAI::PlayTrumpSuit()
{
    gs->SetBidStage(false);
    gs->setMoveStage(true);
    gs->trumpSuit = 2;
    Card* card1 = new Card(6,1);
    gs->CurrentTrick.push_back(card1);
    qInfo() << "Card that should be played: Value = 4, Suit = 2";
    qInfo() << "Size of the current trick: " << gs->CurrentTrick.size();
    QString str = player->DetermineMove(*gs);
    qInfo() << "Received card: " << str;
    QCOMPARE(str, "Play; Selected Card: Value = 4, Suit = 2");
    delete card1;
}

/*
 * Test whether the AI plays the most suitable card if it does not have a leading suit card
 * or a trump suit card.
*/
void TestAI::PlayNoSuit()
{
    gs->SetBidStage(false);
    gs->setMoveStage(true);
    gs->trumpSuit = 1;
    Card* card1 = new Card(6,1);
    gs->CurrentTrick.push_back(card1);
    qInfo() << "Card that should be played: Value = 4, Suit = 2";
    qInfo() << "Size of the current trick: " << gs->CurrentTrick.size();
    QString str = player->DetermineMove(*gs);
    qInfo() << "Received card: " << str;
    QCOMPARE(str, "Play; Selected Card: Value = 4, Suit = 2");
    delete card1;
}

/*
 * Test whether the points for the hand for bidding is calculated correctly.
*/
void TestAI::CalcHandPoints()
{
    gs->SetBidStage(true);
    gs->setMoveStage(false);
    player->DetermineMove(*gs);
    int value = player->getHandValues();
    qInfo() << "Expected value = 17";
    QCOMPARE(value,17);
}

/*
 * Test whether the AI will pass the BID if the HandPoints are too low.
*/
void TestAI::PassBidLowPoint()
{
    Card* AIHand2[13];
    AIHand2[0] = new Card(5, 2);
    AIHand2[1] = new Card(9, 0);
    AIHand2[2] = new Card(2, 2);
    AIHand2[3] = new Card(0, 2);
    AIHand2[4] = new Card(6, 3);
    AIHand2[5] = new Card(4, 2);
    AIHand2[6] = new Card(1, 3);
    AIHand2[7] = new Card(1, 2);
    AIHand2[8] = new Card(3, 2);
    AIHand2[9] = new Card(8, 2);
    AIHand2[10] = new Card(4, 3);
    AIHand2[11] = new Card(7, 3);
    AIHand2[12] = new Card(2, 3);
    player->SetHand(AIHand2);
    gs->SetBidStage(true);
    gs->setMoveStage(false);
    QString str = player->DetermineMove(*gs);
    int value = player->getHandValues();
    qInfo() << "Calculated HandsValue: " << value;
    QCOMPARE(str, "Bid; Pass;");
}

/*
 * Test whether the AI bids correctly
*/
void TestAI::BidCorrect()
{
    gs->SetBidStage(true);
    gs->setMoveStage(false);
    QString str = player->DetermineMove(*gs);
    int value = player->getHandValues();
    qInfo() << "Calculated HandsValue: " << value;
    int BidValue = 0;
    if (value <= 12) {
        BidValue = 0;
    } else if (value <= 16) {
        BidValue = 1;
    } else if (value <= 19) {
        BidValue = 2;
    } else if (value <= 23) {
        BidValue = 3;
    } else if (value <= 26) {
        BidValue = 4;
    } else if (value <= 30) {
        BidValue = 5;
    } else if (value <= 33) {
        BidValue = 6;
    } else if (value <= 37) {
        BidValue = 7;
    }
    qInfo() << "Expected BidValue: " << BidValue;
    qInfo() << "Bid most numerous suit more than 3, else NoTrump. For this: 2";
    QCOMPARE(str,"Bid; Tricks: 2; Trump: 2;");
}

/*
 * Test whether the GameState class manipulates the attributes correctly
*/
void TestAI::GameStateAttributes()
{
    QCOMPARE(gs->GetBidStage(), false);
    gs->SetBidStage(true);
    QCOMPARE(gs->GetBidStage(), true);

    QCOMPARE(gs->getMoveStage(), false);
    gs->setMoveStage(true);
    QCOMPARE(gs->getMoveStage(), true);

    QCOMPARE(gs->getPassCount(), 0);
    gs->setPassCount(2);
    QCOMPARE(gs->getPassCount(), 2);
    gs->IncreasePassCount();
    QCOMPARE(gs->getPassCount(), 3);
}

QTEST_MAIN(TestAI)

#include "tst_testai.moc"
