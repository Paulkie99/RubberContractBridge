#include <QtTest/QtTest>
#include <QCoreApplication>
#include "gamescreen.h"
#include "ui_gamescreen.h"

class TestGameScreen: public QObject
{
    Q_OBJECT
public:
   virtual ~TestGameScreen(){}

private:
    GameScreen *gs = new GameScreen;

private slots:
    void toUpper();
    void testPlayerCardsLoading();
    void testDummyCardsLoading();
    void testPositionDisplay();
    void bidButtons();
    void bidCellClicked();
};

void TestGameScreen::toUpper()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

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

void TestGameScreen::testPositionDisplay()
{
    gs->setUsername("P4");
    QJsonObject bidend = gs->returnJson("BID_END");
    QJsonObject lobby = gs->returnJson("LOBBY_UPDATE");
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

void TestGameScreen::bidButtons()
{

//    int xPos = gs->ui->tableBids->columnViewportPosition( 2 ) + 5;
//    int yPos = gs->ui->tableBids->rowViewportPosition( 3 ) + 10;

//    QRect rect = gs->ui->tableBids->visualItemRect(gs->ui->tableBids->item(2,2));
//    QTest::mouseClick(gs->ui->tableBids->viewport(), Qt::LeftButton, 0, rect.center());
//    QTest::qWait( 1000 );
//    QTest::mouseDClick(gs->ui->tableBids->viewport(), Qt::LeftButton, 0, rect.center());
////    QTest::mouseDClick(gs->ui->tableBids->viewport(), Qt::LeftButton, NULL, QPoint(xPos, yPos));
//    QTest::qWait( 1000 );
//    QTest::keyClick( gs->ui->tableBids, Qt::Key_End );
   // QVERIFY(gs->ui->tableBids->selectedItems().isEmpty() == false);


    QTest::mouseClick(gs->ui->pushButton_Pass, Qt::LeftButton);
    QVERIFY(gs->ui->tableBids->selectedItems().isEmpty() == true);
    QVERIFY(gs->ui->tableBids->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Bid->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Double->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Pass->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Redouble->isEnabled() == false);

    QTest::mouseClick(gs->ui->pushButton_Double, Qt::LeftButton);
    QVERIFY(gs->ui->tableBids->selectedItems().isEmpty() == true);
    QVERIFY(gs->ui->tableBids->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Bid->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Double->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Pass->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Redouble->isEnabled() == false);

    QTest::mouseClick(gs->ui->pushButton_Redouble, Qt::LeftButton);
    QVERIFY(gs->ui->tableBids->selectedItems().isEmpty() == true);
    QVERIFY(gs->ui->tableBids->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Bid->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Double->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Pass->isEnabled() == false);
    QVERIFY(gs->ui->pushButton_Redouble->isEnabled() == false);

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

void TestGameScreen::bidCellClicked()
{
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

QTEST_MAIN(TestGameScreen)
#include "testgamescreen.moc"
