/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Author: Ivan Cuyler
 * Last update: 2020/10/27 */

#include <QtTest/QtTest>
#include <QCoreApplication>
#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <iostream>

class TestGameScreen: public QObject
{
    Q_OBJECT
public:
   virtual ~TestGameScreen(){}

private:
    GameScreen *gs = new GameScreen;

private slots:
    void testPlayerCardsLoading();
    void testDummyCardsLoading();
    void testPositionDisplay();
    void testbidButtons();
    void testbidCellClicked();
    void testCardPlayed();
};


// Test the extraction, saving and loading of the player's card upon BID_START received
void TestGameScreen::testPlayerCardsLoading()
{
    // Test that player cards are loaded. Populate the cards array first as well
    gs->bidStartSlot(gs->returnJson("BID_START"));
    QVERIFY(gs->ui->pb_1->icon().isNull() == false);
    QVERIFY(gs->ui->pb_2->icon().isNull() == false);
    QVERIFY(gs->ui->pb_3->icon().isNull() == false);
    QVERIFY(gs->ui->pb_4->icon().isNull() == false);
    QVERIFY(gs->ui->pb_5->icon().isNull() == false);
    QVERIFY(gs->ui->pb_6->icon().isNull() == false);
    QVERIFY(gs->ui->pb_7->icon().isNull() == false);
    QVERIFY(gs->ui->pb_8->icon().isNull() == false);
    QVERIFY(gs->ui->pb_9->icon().isNull() == false);
    QVERIFY(gs->ui->pb_10->icon().isNull() == false);
    QVERIFY(gs->ui->pb_11->icon().isNull() == false);
    QVERIFY(gs->ui->pb_12->icon().isNull() == false);
    QVERIFY(gs->ui->pb_13->icon().isNull() == false);
}

// Test the extracction, saving and loading of the dummy's cards upon PLAY_START received
void TestGameScreen::testDummyCardsLoading()
{
    // Load the dummy's cards
    gs->playStartSlot(gs->returnJson("PLAY_START"));
    QVERIFY(gs->ui->pb_1->icon().isNull() == false);
    QVERIFY(gs->ui->pb_2->icon().isNull() == false);
    QVERIFY(gs->ui->pb_3->icon().isNull() == false);
    QVERIFY(gs->ui->pb_4->icon().isNull() == false);
    QVERIFY(gs->ui->pb_5->icon().isNull() == false);
    QVERIFY(gs->ui->pb_6->icon().isNull() == false);
    QVERIFY(gs->ui->pb_7->icon().isNull() == false);
    QVERIFY(gs->ui->pb_8->icon().isNull() == false);
    QVERIFY(gs->ui->pb_9->icon().isNull() == false);
    QVERIFY(gs->ui->pb_10->icon().isNull() == false);
    QVERIFY(gs->ui->pb_11->icon().isNull() == false);
    QVERIFY(gs->ui->pb_12->icon().isNull() == false);
    QVERIFY(gs->ui->pb_13->icon().isNull() == false);
}

// Test that the position labels are correctly updated
void TestGameScreen::testPositionDisplay()
{
    // Set the user's username
    gs->setUsername("P4");
    // Generate JSON objects
    QJsonObject bidend = gs->returnJson("BID_END");
    QJsonObject lobby = gs->returnJson("LOBBY_UPDATE");
    // Simulate the label update functions
    gs->lobbyUpdateSlot(lobby);
    gs->bidEndSlot(bidend);

    // Test the default cases
    QCOMPARE(gs->ui->lblTeam->text(), "North (Declarer)");
    QCOMPARE(gs->getTeamPosition(), "North (Declarer)");

    QCOMPARE(gs->ui->lblPlayer->text(), "South (Dummy)");
    QCOMPARE(gs->getUserPosition(), "South (Dummy)");

    QCOMPARE(gs->ui->lblOpp1->text(), "East");
    QCOMPARE(gs->getOpp1Position(), "East");

    QCOMPARE(gs->ui->lblOpp2->text(), "West");
    QCOMPARE(gs->getOpp2Position(), "West");

    // Change the user's position and team
    gs->setUsername("P3");
    gs->lobbyUpdateSlot(lobby);
    gs->bidEndSlot(bidend);

    // Test new cases
    QCOMPARE(gs->ui->lblTeam->text(), "East");
    QCOMPARE(gs->getTeamPosition(), "East");

    QCOMPARE(gs->ui->lblPlayer->text(), "West");
    QCOMPARE(gs->getUserPosition(), "West");

    QCOMPARE(gs->ui->lblOpp1->text(), "North (Declarer)");
    QCOMPARE(gs->getOpp1Position(), "North (Declarer)");

    QCOMPARE(gs->ui->lblOpp2->text(), "South (Dummy)");
    QCOMPARE(gs->getOpp2Position(), "South (Dummy)");
}

// Test the correct functionality of the bidding buttons on the Auction screen
void TestGameScreen::testbidButtons()
{
    // Simulate a mouse click on the Pass bidding option
    QTest::mouseClick(gs->ui->pushButton_Pass, Qt::LeftButton);
    QVERIFY(gs->ui->tableBids->selectedItems().isEmpty() == true);
    QVERIFY(gs->ui->tableBids->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Bid->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Double->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Pass->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Redouble->isEnabled() == false);

    // Simulate a mouse click on the Double bidding option
    QTest::mouseClick(gs->ui->pushButton_Double, Qt::LeftButton);
    QVERIFY(gs->ui->tableBids->selectedItems().isEmpty() == true);
    QVERIFY(gs->ui->tableBids->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Bid->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Double->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Pass->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Redouble->isEnabled() == false);

    // Simulate a mouse click on the Redouble bidding option
    QTest::mouseClick(gs->ui->pushButton_Redouble, Qt::LeftButton);
    QVERIFY(gs->ui->tableBids->selectedItems().isEmpty() == true);
    QVERIFY(gs->ui->tableBids->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Bid->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Double->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Pass->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Redouble->isEnabled() == false);

    // Simulate a mouse click on the normal Bid option
    QTest::mouseClick(gs->ui->pushButton_Bid, Qt::LeftButton);
    QVERIFY(gs->ui->tableBids->selectedItems().isEmpty() == true);
    QVERIFY(gs->ui->tableBids->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Bid->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Double->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Pass->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Redouble->isEnabled() == false);

    // Simulate a BID_REQUEST signal received that must re-enable bidding elements
    gs->bidRequestSlot();
    QVERIFY(gs->ui->tableBids->isEnabled() == true);
    QVERIFY(gs->ui->pushButton_Bid->isEnabled() == true);
    QVERIFY(gs->ui->pushButton_Double->isEnabled() == true);
    QVERIFY(gs->ui->pushButton_Pass->isEnabled() == true);
    QVERIFY(gs->ui->pushButton_Redouble->isEnabled() == true);
}

// Test the correct extraction of a bid made by the user from the bidding table
void TestGameScreen::testbidCellClicked()
{
    // Simulate a click on the cell (2, 0)
    gs->on_tableBids_cellClicked(2, 0);
    QCOMPARE(gs->getBid(), "C3");

    gs->on_tableBids_cellClicked(0, 4);
    QCOMPARE(gs->getBid(), "NT1");

    // Boundary condition
    gs->on_tableBids_cellClicked(6, 4);
    QCOMPARE(gs->getBid(), "NT7");

    gs->on_tableBids_cellClicked(3, 2);
    QCOMPARE(gs->getBid(), "H4");

    // Boundary condition
    gs->on_tableBids_cellClicked(0, 0);
    QCOMPARE(gs->getBid(), "C1");
}

// Test the correct GUI updating of the user clicking on a card to play it
void TestGameScreen::testCardPlayed()
{
    // Load user cards
    gs->bidStartSlot(gs->returnJson("BID_START"));

    // Generate a MOVE_UPDATE JSON
    QJsonObject move = gs->returnJson("MOVE_UPDATE");

    // Simulate a card being clicked and selected to play
    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_1, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"H2");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_2, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"H7");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_3, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"S5");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_4, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"SA");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_5, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"S6");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_6, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"C6");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_7, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"CJ");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_8, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"CQ");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_9, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"CK");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_10, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"D2");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_11, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"D9");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_12, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"D10");

    gs->visibleAll(true);
    gs->disableCards(0, true);
    QTest::mouseClick(gs->ui->pb_13, Qt::LeftButton);
    QCOMPARE(gs->getMove(),"DK");
}

//QTEST_MAIN(TestGameScreen)
#include "testgamescreen.moc"
