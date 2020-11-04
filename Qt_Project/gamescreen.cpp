/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Author: Ivan Cuyler
 * Last update: 2020/10/27 */

#include "gamescreen.h"
#include "ui_gamescreen.h"
#include "scoreboard.h"
#include "QPixmap"
#include <QJsonArray>
#include <QMessageBox>
#include <iostream>
#include <QThread>
#include "windows.h"
using namespace std;



/* Helper function to load the player cards as well as the dummy's cards
 Once integrated it will receive the actual cards to load from server
 The function receives a push button object and a file path to which the
 push button object icon will be set.*/
void GameScreen::loadCards(QPushButton *pb, QString path)
{
    QPixmap pm(path);
    QIcon ButtonIcon(pm);
    pb->setIcon(ButtonIcon);
    pb->setIconSize(QSize(pb->size()));
}

// Constructor
GameScreen::GameScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    // Prevent the window from being resized
    QWidget::setFixedSize(size());
    // Set QDialog flags to that of a normal window, and not a dialog
    this->setWindowFlags(Qt::Window);
    // Prevent the QTableWidget object cells from being resized
    ui->tableBids->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableBids->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableSequence->horizontalHeader()->setVisible(true);
    //ui->tableSequence->clear();
    // Set the title of the window
    QWidget::setWindowTitle("Auction");
    // Ensure that the correct interface is displayed when joining a game
    ui->stackedWidget->setCurrentIndex(0);
    ui->lblRoundInfo->setVisible(false);
    ui->pushButton_ViewCards->setEnabled(false);
    ui->lblContract->setVisible(false);
    ui->lblDummy->setVisible(false);
    ui->lblDeclarer->setVisible(false);
    ui->lblDouble->setVisible(false);
    ui->lblContractPlay->setVisible(false);
    ui->lblTricksWonEW->setVisible(false);
    ui->lblTricksWonNS->setVisible(false);
    ui->lblPosition->setVisible(false);


    ui->tableSequence->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableSequence->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Disable GUI elements until a BID_REQUEST is received from server
    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);
    ui->pushButton_Play->setVisible(false);

    // Make the moves played push buttons invisible
    ui->pb_Move_1->setVisible(false);
    ui->pb_Move_2->setVisible(false);
    ui->pb_Move_3->setVisible(false);
    ui->pb_Move_4->setVisible(false);
}

// Desctructor
GameScreen::~GameScreen()
{
    delete ui;
}

// If the game is left, for which ever reason, this slot ensure that
// the user is taken back to the main screen.
void GameScreen::on_GameScreen_finished(int result)
{
    clientgs->closed(Userid);
    // Show the parent again, in this case main window
    this->close();
    parentWidget()->show();
}

/* Slot to show the scoreboard. The scoreboard can be viewed at
 any time by pressing this button. The modal approach is used,
 so the game screen will not be destroyed, yet also not usable
 while the scoreboard is displayed.*/
// Implemented by Jacques
void GameScreen::on_pushButton_Score_clicked()
{
    ScoreBoard scoreBoard(this);

        scoreBoard.updateScores(NSarray,EWarray,ArrCount);
        scoreBoard.setModal(true);

        scoreBoard.exec();
}

// Once the auction is over, the pushButton_Play will be made visible.
// For testing purposes this button will remain visible.
void GameScreen::on_pushButton_Play_clicked()
{
    ui->pushButton_Play->setVisible(false);
    ui->pushButton_BackAuction->setVisible(false);
    ui->pushButton_Abandon->setVisible(true);
    // Increase the index of the stacked widget to the Normal Play page.
    ui->stackedWidget->setCurrentIndex(1);
    // Update the title of the window
    QWidget::setWindowTitle("Normal Play");
}

// Close the Game Screen page. The user will be taken back to the Main Screen.
void GameScreen::on_pushButton_Abandon_clicked()
{
    on_GameScreen_finished(0);
}

/* Helper function to load and display cards received from the server. Variable i is used
to distinguish between loading the player's cards (i = 0), or the dummy's cards (i = 1). */
void GameScreen::showCards(int i)
{
    // Make ALL card buttons visible
    visibleAll(true);
    QString paths[13];

    if (i == 0)
    { // Load player cards
        for (int k=0;k<13;k++) {
            if (cards[k] != "") {
                paths[k] = ":/Cards/" + cards[k];
            }

         }
        QPushButton *pb = ui->pb_1;
        loadCards(pb, paths[0]);
        pb = ui->pb_2;
        loadCards(pb, paths[1]);
        pb = ui->pb_3;
        loadCards(pb, paths[2]);
        pb = ui->pb_4;
        loadCards(pb, paths[3]);
        pb = ui->pb_5;
        loadCards(pb, paths[4]);
        pb = ui->pb_6;
        loadCards(pb, paths[5]);
        pb = ui->pb_7;
        loadCards(pb, paths[6]);
        pb = ui->pb_8;
        loadCards(pb, paths[7]);
        pb = ui->pb_9;
        loadCards(pb, paths[8]);
        pb = ui->pb_10;
        loadCards(pb, paths[9]);
        pb = ui->pb_11;
        loadCards(pb, paths[10]);
        pb = ui->pb_12;
        loadCards(pb, paths[11]);
        pb = ui->pb_13;
        loadCards(pb, paths[12]);


        ui->pushButton_ViewCards->setEnabled(true);
        ui->pushButton_BackAuction->setVisible(true);
        ui->pushButton_Abandon->setVisible(false);
    }

    if (i == 1)
    { // Load dummy cards
        if (Dummy[0] != UserPosition[0]) // Don't load the dummy cards if the user is already the dummy
        {
            for (int k=0;k<13;k++) {
                if (cardsDummy[k] != "") {
                    paths[k] = ":/Cards/" + cardsDummy[k];
                }
             }

            QPushButton *pb = ui->pb_14;
            loadCards(pb, paths[0]);
            pb = ui->pb_15;
            loadCards(pb, paths[1]);
            pb = ui->pb_16;
            loadCards(pb, paths[2]);
            pb = ui->pb_17;
            loadCards(pb, paths[3]);
            pb = ui->pb_18;
            loadCards(pb, paths[4]);
            pb = ui->pb_19;
            loadCards(pb, paths[5]);
            pb = ui->pb_20;
            loadCards(pb, paths[6]);
            pb = ui->pb_21;
            loadCards(pb, paths[7]);
            pb = ui->pb_22;
            loadCards(pb, paths[8]);
            pb = ui->pb_23;
            loadCards(pb, paths[9]);
            pb = ui->pb_24;
            loadCards(pb, paths[10]);
            pb = ui->pb_25;
            loadCards(pb, paths[11]);
            pb = ui->pb_26;
            loadCards(pb, paths[12]);
        }
    }
}

/* Helper function that enables/disables the card labels. if i = 0, then the player's cards are
 enabled/disabled. If i = 1, then the dummy's cards are enabled/disabled. If i = 2, then both the
 player and the dummy's cards are disabled. Enabled/disabled is determined by bool en. */
void GameScreen::disableCards(int i, bool en = false)
{
    if (i == 0)
    { // Enable/Disable only the player's cards
        ui->pb_1->setEnabled(en);
        ui->pb_2->setEnabled(en);
        ui->pb_3->setEnabled(en);
        ui->pb_4->setEnabled(en);
        ui->pb_5->setEnabled(en);
        ui->pb_6->setEnabled(en);
        ui->pb_7->setEnabled(en);
        ui->pb_8->setEnabled(en);
        ui->pb_9->setEnabled(en);
        ui->pb_10->setEnabled(en);
        ui->pb_11->setEnabled(en);
        ui->pb_12->setEnabled(en);
        ui->pb_13->setEnabled(en);
    }
    if (i == 1)
    { // Enable/Disable only the dummy's cards
        ui->pb_14->setEnabled(en);
        ui->pb_15->setEnabled(en);
        ui->pb_16->setEnabled(en);
        ui->pb_17->setEnabled(en);
        ui->pb_18->setEnabled(en);
        ui->pb_19->setEnabled(en);
        ui->pb_20->setEnabled(en);
        ui->pb_21->setEnabled(en);
        ui->pb_22->setEnabled(en);
        ui->pb_23->setEnabled(en);
        ui->pb_24->setEnabled(en);
        ui->pb_25->setEnabled(en);
        ui->pb_26->setEnabled(en);
    }
    if (i == 2)
    { // Disable both the dummy's cards and the player's cards
        ui->pb_1->setEnabled(false);
        ui->pb_2->setEnabled(false);
        ui->pb_3->setEnabled(false);
        ui->pb_4->setEnabled(false);
        ui->pb_5->setEnabled(false);
        ui->pb_6->setEnabled(false);
        ui->pb_7->setEnabled(false);
        ui->pb_8->setEnabled(false);
        ui->pb_9->setEnabled(false);
        ui->pb_10->setEnabled(false);
        ui->pb_11->setEnabled(false);
        ui->pb_12->setEnabled(false);
        ui->pb_13->setEnabled(false);
        ui->pb_14->setEnabled(false);
        ui->pb_15->setEnabled(false);
        ui->pb_16->setEnabled(false);
        ui->pb_17->setEnabled(false);
        ui->pb_18->setEnabled(false);
        ui->pb_19->setEnabled(false);
        ui->pb_20->setEnabled(false);
        ui->pb_21->setEnabled(false);
        ui->pb_22->setEnabled(false);
        ui->pb_23->setEnabled(false);
        ui->pb_24->setEnabled(false);
        ui->pb_25->setEnabled(false);
        ui->pb_26->setEnabled(false);
    }
}


// Helper function that sends the bid made by the player to the server.
// NB NOT A SLOT.
void GameScreen::sendBid(QString Suit, QString Rank)
{
    QString mes = clientgs->GenerateMessage("BID_SEND");
    QJsonObject bid = clientgs->CreateJObject(mes);
    // Create new object with updated Suit and Rank
    QJsonObject bid2 = bid["Bid"].toObject();
    bid2["Suit"] = Suit;
    if (Rank == "") {
        bid2["Rank"] = QJsonValue::Null;
    } else {
           bid2["Rank"] = Rank;
        }

    // Set chosen bid Suit and Rank
    bid["Bid"] = bid2;
    bid["Id"] = Userid;

    // Send the updated message to the server. BID_SEND
    clientgs->SendMessageToServer(clientgs->CreateJString(bid));
}

// NOT A SLOT. Function to send a move made by the player
void GameScreen::sendMove(QString Suit, QString Rank)
{
    // If Rank is a 1, is supposed to be a 10
    if (Rank == "1")
    {
        Rank = "10";
    }

    // Follow the same approach as in sendBid, create a new bid object and set the Suit and Rank from there
    QString mes = clientgs->GenerateMessage("MOVE_SEND");
    QJsonObject move = clientgs->CreateJObject(mes);
    QJsonObject move2 = move["Move"].toObject();
    move2["Suit"] = Suit;
    move2["Rank"] = Rank;
    move["Move"] = move2;
    move["Id"] = Userid;

    // Disable card elements
    disableCards(2);
    //Send the updated message to the server
    clientgs->SendMessageToServer(clientgs->CreateJString(move));
}


/* Slot to receive the server info and display in a label. This is the 1st slot to activate in gamescreen.cpp,
 and thus most of the signals and slots will be connected from here. This slot receives a signal from MainWindow
 once authentication is approved. Server info such as the ip, port, password, username, user id and most importantly
the clientconnection object is received through here.*/
void GameScreen::serverInfoSlot(QString ip, QString port, QString pass, clientconnection *client1, QString usern, int ID)
{
    Userid = ID;
    Username = usern;
    ui->lblInfo->setText("IP: " + ip + " Password: " + pass);
    ui->lblInfoPlay->setText("IP: " + ip + " Password: " + pass);
    if(clientgs)
            delete clientgs;
    clientgs = client1;

    // Connect all relevant signals and slots
    connect(clientgs, SIGNAL(bidStartSignal(QJsonObject)),this, SLOT(bidStartSlot(QJsonObject)));
    connect(clientgs, SIGNAL(bidRequestSignal()), this, SLOT(bidRequestSlot()));
    connect(clientgs, SIGNAL(bidUpdateSignal(QJsonObject)), this, SLOT(bidUpdateSlot(QJsonObject)));
    connect(clientgs, SIGNAL(bidEndSignal(QJsonObject)), this, SLOT(bidEndSlot(QJsonObject)));
    connect(clientgs, SIGNAL(playStartSignal(QJsonObject)), this, SLOT(playStartSlot(QJsonObject)));
    connect(clientgs, SIGNAL(lobbyUpdateSignal(QJsonObject)), this, SLOT(lobbyUpdateSlot(QJsonObject)));
    connect(clientgs, SIGNAL(moveRequestSignal(QJsonObject)), this, SLOT(moveRequestSlot(QJsonObject)));
    connect(clientgs, SIGNAL(moveUpdateSignal(QJsonObject)), this, SLOT(moveUpdateSlot(QJsonObject)));
    connect(clientgs, SIGNAL(trickEndSignal(QJsonObject)), this, SLOT(trickEndSlot(QJsonObject)));
    connect(clientgs, SIGNAL(playEndSignal(QJsonObject)), this, SLOT(playEndSlot(QJsonObject)));
    connect(clientgs, SIGNAL(gameEndSignal(QJsonObject)), this, SLOT(gameEndSlot(QJsonObject)));
    connect(clientgs, SIGNAL(disconnectPlayerSignal(QJsonObject)), this, SLOT(disconnectPlayerSlot(QJsonObject)));
    connect(clientgs, SIGNAL(pongSignal(QJsonObject)), this, SLOT(pongSlot(QJsonObject)));
    connect(clientgs, SIGNAL(pingSignal(QJsonObject)), this, SLOT(ping(QJsonObject)));
    connect(clientgs, SIGNAL(scoreSignal(QJsonObject)), this, SLOT(scoreSlot(QJsonObject)));

    row = 0;
}

/* Slot for BID_START signal. The cards array, which holds the cards dealt to the player, is populated
 from here using the passed through QJsonObject cardsdealt object. */
void GameScreen::bidStartSlot(QJsonObject cardsdealt)
{
    ui->tableSequence->clearContents();
   // ui->lblVulnerable->setText("");
    ui->lblContractPlay->setVisible(false);
    ui->lblPoints->setVisible(false);

    Dummy = "not set";
    QJsonValue value = cardsdealt.value("Cards");
    QJsonArray array1 = value.toArray();
    int count = 0;

    // Loop through JSON array and populate cards array
    foreach (const QJsonValue & v, array1){
        for (int k=0;k<v.toObject().value("Rank").toArray().size();k++) {
            cards[count] = v.toObject().value("Suit").toString() + v.toObject().value("Rank")[k].toString();
            count++;
        }
    }

    // Load the cards into GUI. Set the parameter to 0 to indicate it is the user's cards being loaded.
    showCards(0);
    // Disable the player and dummy card objects
    disableCards(2);

    // Make the top cards invisible
    ui->pb_14->setVisible(false);
    ui->pb_15->setVisible(false);
    ui->pb_16->setVisible(false);
    ui->pb_17->setVisible(false);
    ui->pb_18->setVisible(false);
    ui->pb_19->setVisible(false);
    ui->pb_20->setVisible(false);
    ui->pb_21->setVisible(false);
    ui->pb_22->setVisible(false);
    ui->pb_23->setVisible(false);
    ui->pb_24->setVisible(false);
    ui->pb_25->setVisible(false);
    ui->pb_26->setVisible(false);

    // Disable GUI elements until a BID_REQUEST is received from server
    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);
    ui->pushButton_ViewCards->setEnabled(true);

    // Update the opponent labels
    ui->lblOpp1Name->setText(opp1Username);
    ui->lblOpp2Name->setText(opp2Username);

    if (opp1Pos[0] == "N")
    {
        ui->lblOpp1->setText("North");
        ui->lblOpp2->setText("South");
    }
    if (opp1Pos[0] == "E")
    {
        ui->lblOpp1->setText("East");
        ui->lblOpp2->setText("West");
    }
    if (opp1Pos[0] == "S")
    {
        ui->lblOpp1->setText("South");
        ui->lblOpp2->setText("North");
    }
    if (opp1Pos[0] == "W")
    {
        ui->lblOpp1->setText("West");
        ui->lblOpp2->setText("East");
    }

    if (UserPosition[0] == "N")
    {
        UserPosition = "North";
        ui->lblPlayer->setText("North");
        ui->lblTeam->setText("South");
    }
    if (UserPosition[0] == "E")
    {
        UserPosition = "East";
        ui->lblPlayer->setText("East");
        ui->lblTeam->setText("West");
    }
    if (UserPosition[0] == "S")
    {
        UserPosition = "South";
        ui->lblPlayer->setText("South");
        ui->lblTeam->setText("North");
    }
    if (UserPosition[0] == "W")
    {
        UserPosition = "West";
        ui->lblPlayer->setText("West");
        ui->lblTeam->setText("East");
    }
    row = 0;
}

void GameScreen::on_pushButton_ViewCards_clicked()
{
    // Increase the index of the stacked widget to view the cards
    ui->stackedWidget->setCurrentIndex(1);
    // Update the title of the window
    QWidget::setWindowTitle("Player Cards");
}

void GameScreen::on_pushButton_BackAuction_clicked()
{
    // Decrease the index of the stacked widget to go back to the auction
    ui->stackedWidget->setCurrentIndex(0);
    // Update the title of the window
    QWidget::setWindowTitle("Auction");
}

// Event for when a bid is made by the user in tableBids
void GameScreen::on_tableBids_cellClicked(int row, int column)
{
    // The bid rank is just the row + 1
    currentBidRank = QString::number(row+1);

    // Each column corresponds to a specific suit
    switch (column) {
        case 0:
          currentBidSuit = "C";
          break;
        case 1:
          currentBidSuit = "D";
          break;
        case 2:
          currentBidSuit = "H";
          break;
        case 3:
          currentBidSuit = "S";
          break;
        case 4:
          currentBidSuit = "NT";
          break;
    }
}

void GameScreen::on_pushButton_Pass_clicked()
{
    currentBidSuit = "PASS";
    currentBidRank = "";

    // Helper function to send bid to server
    sendBid(currentBidSuit, currentBidRank);
    ui->tableBids->clearSelection();
}

void GameScreen::on_pushButton_Double_clicked()
{
    currentBidSuit = "DOUBLE";
    currentBidRank = "";

    // Helper function to send bid to server
    sendBid(currentBidSuit, currentBidRank);
    ui->tableBids->clearSelection();
}

void GameScreen::on_pushButton_Redouble_clicked()
{
    currentBidSuit = "REDOUBLE";
    currentBidRank = "";

    // Helper function to send bid to server
    sendBid(currentBidSuit, currentBidRank);
    ui->tableBids->clearSelection();
}

void GameScreen::on_pushButton_Bid_clicked()
{
    if (!ui->tableBids->selectedItems().empty()) {
        sendBid(currentBidSuit, currentBidRank);
        ui->pushButton_Bid->setFocus();
        ui->tableBids->clearSelection();
    }
}

/* Slot for when the server requests a bid from the user/client.
   This enables the GUI, allowing a bid to be made. A bid will be made via these GUI elements.
   Once a bid is made, they will be disabled again (from within the function that
   made the bid, e.g. pushbutton Redouble clicked, or pushbutton Bid clicked),
   preventing another bid from being made when it is not the user's turn to do so.*/
void GameScreen::bidRequestSlot()
{
    ui->tableBids->setEnabled(true);
    ui->pushButton_Bid->setEnabled(true);
    ui->pushButton_Double->setEnabled(true);
    ui->pushButton_Pass->setEnabled(true);
    ui->pushButton_Redouble->setEnabled(true);
}

// Slot for updating the bidding table when a player has made a bid
// BID_UPDATE received
void GameScreen::bidUpdateSlot(QJsonObject bid)
{
    // Disable GUI elements until another BID_REQUEST is received from server
    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);

    QString Suit = bid["Bid"].toObject()["Suit"].toString();
    QString Rank = bid["Bid"].toObject()["Rank"].toString();

    int col = 0;

    // Determine the coloumn index depending on position
    if (bid["Player"] == "N") {
        col =0;
    }
     if (bid["Player"] == "E") {
        col = 1;
    }
     if (bid["Player"] == "S") {
        col = 2;
    }
     if (bid["Player"] == "W") {
        col = 3;
    }

    addToTable(Rank + Suit, col);

    // If the last player in the table has made a bid, the row count must be increased
    if (bid["Player"] == "W") {
        row = row + 1;
    }
}

// Helper function to add a bid to the bidding table
void GameScreen::addToTable(QString bid, int col)
{
    QTableWidgetItem* selectedItem = new QTableWidgetItem;
    selectedItem->setText(bid);
    selectedItem->setTextAlignment(4);
    ui->tableSequence->setItem(row,col,selectedItem);

//    if (col == 3)
//    {
//        row = row + 1;
//    }
}

// Helper function that makes all the cards on the table visible
void GameScreen::visibleAll(bool vis)
{
    // User cards
    ui->pb_1->setVisible(vis);
    ui->pb_2->setVisible(vis);
    ui->pb_3->setVisible(vis);
    ui->pb_4->setVisible(vis);
    ui->pb_5->setVisible(vis);
    ui->pb_6->setVisible(vis);
    ui->pb_7->setVisible(vis);
    ui->pb_8->setVisible(vis);
    ui->pb_9->setVisible(vis);
    ui->pb_10->setVisible(vis);
    ui->pb_11->setVisible(vis);
    ui->pb_12->setVisible(vis);
    ui->pb_13->setVisible(vis);

    // If the user is the dummy, then the top cards should not be displayed
    if (Dummy != "not set")
    {
        if (UserPosition[0] == Dummy[0])
        {
            vis = false;
        }
    }

    // Dummy cards
    ui->pb_14->setVisible(vis);
    ui->pb_15->setVisible(vis);
    ui->pb_16->setVisible(vis);
    ui->pb_17->setVisible(vis);
    ui->pb_18->setVisible(vis);
    ui->pb_19->setVisible(vis);
    ui->pb_20->setVisible(vis);
    ui->pb_21->setVisible(vis);
    ui->pb_22->setVisible(vis);
    ui->pb_23->setVisible(vis);
    ui->pb_24->setVisible(vis);
    ui->pb_25->setVisible(vis);
    ui->pb_26->setVisible(vis);
}

// Slot for when the bidding is over. The contract info, dummy & declarer is extracted
// from the JSON object received here.
// BID_END received
void GameScreen::bidEndSlot(QJsonObject contract)
{
    // Declarer helper variables
    QString NDeclarer = "";
    QString SDeclarer = "";
    QString EDeclarer = "";
    QString WDeclarer = "";

    // Dummy helper variables
    QString NDummy = "";
    QString SDummy = "";
    QString EDummy = "";
    QString WDummy = "";

    // Disable GUI elements on bidding screen since bid is now over
    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);
    ui->pushButton_BackAuction->setVisible(false);
    ui->pushButton_ViewCards->setEnabled(false);

    // Extract the contract information from the JSON Object received
    Contract = contract["Contract"].toObject()["Suit"].toString() + contract["Contract"].toObject()["Rank"].toString() ;
    Declarer = contract["Declarer"].toString();
    Dummy = contract["Dummy"].toString();
    Trump = contract["Trump"].toString();
    Double = contract["Contract"].toObject()["IsDouble"].toBool();
    Redouble = contract["Contract"].toObject()["IsRedouble"].toBool();

    // Set the label display properties
    ui->lblContract->setVisible(true);
    ui->lblDummy->setVisible(true);
    ui->lblDeclarer->setVisible(true);
    ui->lblDouble->setVisible(true);
    ui->lblContractPlay->setVisible(true);
    ui->lblPoints->setVisible(true);
    // Enable the play button. Allow the user to click to go to the next screen
    ui->pushButton_Play->setVisible(true);

    // Update GUI elements with new information
    ui->lblContract->setText("Contract: " + Contract);
    ui->lblDeclarer->setText("Declarer: " + Declarer);
    ui->lblDummy->setText("Dummy: " + Dummy);
    ui->lblContractPlay->setText("Contract: " + Contract);

    // Take into account if Double/Redouble has been called
    if (Double == true && Redouble == true) {
        ui->lblDouble->setText("Points: Redouble");
        ui->lblPoints->setText("Points: Redouble");
    }
    if (Double == true && Redouble == false) {
        ui->lblDouble->setText("Points: Double");
        ui->lblPoints->setText("Points: Double");
    }
    if (Double == false && Redouble == false) {
        ui->lblDouble->setText("Points: Normal");
        ui->lblPoints->setText("Points: Normal");
    }

    // Set the declarer helper variables
    if (Declarer[0] == "N") {
        NDeclarer = " (Declarer)";
        }
    if (Declarer[0] == "E") {
        EDeclarer = " (Declarer)";
        }
    if (Declarer[0] == "S") {
        SDeclarer = " (Declarer)";
        }
    if (Declarer[0] == "W") {
        WDeclarer = " (Declarer)";
        }

    // Set the dummy helper variables
    if (Dummy[0] == "N") {
        NDummy = " (Dummy)";
        }
    if (Dummy[0] == "E") {
        EDummy = " (Dummy)";
        }
    if (Dummy[0] == "S") {
        SDummy = " (Dummy)";
        }
    if (Dummy[0] == "W") {
        WDummy = " (Dummy)";
        }

    // Update the user's info labels first
    ui->lblPlayer->setText(UserPosition);
    ui->lblNamePlayer->setText(Username);

    if (Dummy[0] == UserPosition[0])
    {
        UserPosition = UserPosition + " (Dummy)";
        ui->lblPlayer->setText(UserPosition);

        // Make the dummy buttons invisible
        ui->pb_14->setVisible(false);
        ui->pb_15->setVisible(false);
        ui->pb_16->setVisible(false);
        ui->pb_17->setVisible(false);
        ui->pb_18->setVisible(false);
        ui->pb_19->setVisible(false);
        ui->pb_20->setVisible(false);
        ui->pb_21->setVisible(false);
        ui->pb_22->setVisible(false);
        ui->pb_23->setVisible(false);
        ui->pb_24->setVisible(false);
        ui->pb_25->setVisible(false);
        ui->pb_26->setVisible(false);
    }

    if (Declarer[0] == UserPosition[0])
    {
        ui->lblPlayer->setText(UserPosition + " (Declarer)");
    }

    // Do the user's teammate
    if (UserPosition[0] == "N")
    {
        teamPos = "South" + SDummy + SDeclarer;
        teamUsername = SouthAlias;

        // Get the opponent's info
        opp1Pos = "East" + EDummy + EDeclarer;
        opp1Username = EastAlias;
        opp2Pos = "West" + WDummy + WDeclarer;
        opp2Username = WestAlias;
    }
    if (UserPosition[0] == "S")
    {
        teamPos = "North" + NDummy + NDeclarer;
        teamUsername = NorthAlias;

        opp1Pos = "East" + EDummy + EDeclarer;
        opp1Username = EastAlias;
        opp2Pos = "West" + WDummy + WDeclarer;
        opp2Username = WestAlias;
    }
    if (UserPosition[0] == "E")
    {
        teamPos = "West" + WDummy + WDeclarer;
        teamUsername = WestAlias;

        opp1Pos = "North" + NDummy + NDeclarer;
        opp1Username = NorthAlias;
        opp2Pos = "South" + SDummy + SDeclarer;
        opp2Username = SouthAlias;
    }
    if (UserPosition[0] == "W")
    {
        teamPos = "East" + EDummy + EDeclarer;
        teamUsername = EastAlias;

        opp1Pos = "North" + NDummy + NDeclarer;
        opp1Username = NorthAlias;
        opp2Pos = "South" + SDummy + SDeclarer;
        opp2Username = SouthAlias;
    }

    // Update the teammate's labels
    ui->lblTeam->setText(teamPos);
    ui->lblNameTeam->setText(teamUsername);

    // Update the opponent labels
    ui->lblOpp1->setText(opp1Pos);
    ui->lblOpp1Name->setText(opp1Username);
    ui->lblOpp2->setText(opp2Pos);
    ui->lblOpp2Name->setText(opp2Username);
}

int tempcount = 0;
/* Slot for MOVE_UPDATE. This slot will update the display showing the card played by a player.
 Depending on who the dummy and declarer is (and in which team the are, the top dummy cards might
 have to be made invisible if the declarer from the other team played from there, hence the two large
 if statements. */
// MOVE_UPDATE received
void GameScreen::moveUpdateSlot(QJsonObject move)
{
    ui->lblRoundInfo->setVisible(false);

    QString Suit = move["Move"].toObject()["Suit"].toString();
    QString Rank = move["Move"].toObject()["Rank"].toString();
    QString cardplayed = Suit + Rank;

    for (int k=0;k<13;k++)
    {
        // If a card was played from the dummy's hand, the appropriate button should be made invisible
        if (cardsDummy[k] == cardplayed)
        {
            switch (k) {
                case 0:
                  ui->pb_14->setVisible(false);
                  break;
                case 1:
                  ui->pb_15->setVisible(false);
                  break;
                case 2:
                  ui->pb_16->setVisible(false);
                  break;
                case 3:
                  ui->pb_17->setVisible(false);
                  break;
                case 4:
                  ui->pb_18->setVisible(false);
                  break;
                case 5:
                  ui->pb_19->setVisible(false);
                  break;
                case 6:
                  ui->pb_20->setVisible(false);
                  break;
                case 7:
                  ui->pb_21->setVisible(false);
                  break;
                case 8:
                  ui->pb_22->setVisible(false);
                  break;
                case 9:
                  ui->pb_23->setVisible(false);
                  break;
                case 10:
                  ui->pb_24->setVisible(false);
                  break;
                case 11:
                  ui->pb_25->setVisible(false);
                  break;
                case 12:
                  ui->pb_26->setVisible(false);
                  break;
            }
            break;
        }
    }

    for (int k=0;k<13;k++)
    {
        // The appropriate user card played by the declarer (user's teammate) must be made invisible
        if (cards[k] == cardplayed)
        {
            switch (k) {
                case 0:
                  ui->pb_1->setVisible(false);
                  break;
                case 1:
                  ui->pb_2->setVisible(false);
                  break;
                case 2:
                  ui->pb_3->setVisible(false);
                  break;
                case 3:
                  ui->pb_4->setVisible(false);
                  break;
                case 4:
                  ui->pb_5->setVisible(false);
                  break;
                case 5:
                  ui->pb_6->setVisible(false);
                  break;
                case 6:
                  ui->pb_7->setVisible(false);
                  break;
                case 7:
                  ui->pb_8->setVisible(false);
                  break;
                case 8:
                  ui->pb_9->setVisible(false);
                  break;
                case 9:
                  ui->pb_10->setVisible(false);
                  break;
                case 10:
                  ui->pb_11->setVisible(false);
                  break;
                case 11:
                  ui->pb_12->setVisible(false);
                  break;
                case 12:
                  ui->pb_13->setVisible(false);
                  break;
            }
            break;
        }
    }


    /* If statements to display which ever card was played on the board. The moveCounter counter determines
     which display button to load next in the correct order. Once it reaches 3, it is reset to 0 (in trickEndSlot)
     as the trick is over.*/
    if (moveCounter == 0)
    { // Load into 1st move button
        ui->pb_Move_1->setEnabled(true);
        ui->pb_Move_1->setVisible(true);
        loadCards(ui->pb_Move_1, ":/Cards/" + Suit +Rank);
        moveCounter = moveCounter + 1;
    }
    else if (moveCounter == 1)
    { // Load into 2nd move button
        ui->pb_Move_2->setEnabled(true);
        ui->pb_Move_2->setVisible(true);
        loadCards(ui->pb_Move_2, ":/Cards/" + Suit + Rank);
        moveCounter++;
    }
    else if (moveCounter == 2)
    { // Load into 3rd move button
        ui->pb_Move_3->setEnabled(true);
        ui->pb_Move_3->setVisible(true);
        loadCards(ui->pb_Move_3, ":/Cards/" + Suit + Rank);
        moveCounter++;
    }
    else if (moveCounter == 3)
    { // Load into 4th move button
        ui->pb_Move_4->setEnabled(true);
        ui->pb_Move_4->setVisible(true);
        loadCards(ui->pb_Move_4, ":/Cards/" + Suit + Rank);
        moveCounter++;
    }
   // QThread::sleep(2);
}

// Slot for when TRICK_END is received. The appropriate GUI elements need to be reset to their original states.
// TRICK_END received
void GameScreen::trickEndSlot(QJsonObject trick)
{
    //QThread::sleep(2);
    //Sleep(1000);
    // Reset move counter of current trick
    moveCounter = 0;



    // Disable all cards
    disableCards(2);

    ui->lblRoundInfo->setVisible(true);
    ui->lblRoundInfo->setText(trick["WinningPartnership"].toString() + " won the trick");

    if (trick["WinningPartnership"] == "NS")
    {
        countNStricks++;
    }
    if (trick["WinningPartnership"] == "EW")
    {
        countEWtricks++;
    }

    ui->lblTricksWonEW->setText("Tricks won by EW: " + QString::number(countEWtricks));
    ui->lblTricksWonNS->setText("Tricks won by NS: " + QString::number(countNStricks));

    // Reset move buttons
    ui->pb_Move_1->setIcon(QIcon());
    ui->pb_Move_1->setVisible(false);
    ui->pb_Move_2->setIcon(QIcon());
    ui->pb_Move_2->setVisible(false);
    ui->pb_Move_3->setIcon(QIcon());
    ui->pb_Move_3->setVisible(false);
    ui->pb_Move_4->setIcon(QIcon());
    ui->pb_Move_4->setVisible(false);
}

/* Slot for "PLAY_END". The user will return to the bidding screen and new cards dealt. The relevent GUI
  elements are reset to their original states.*/
// PLAY_END received
void GameScreen::playEndSlot(QJsonObject play)
{
    countEWtricks = 0;
    countNStricks = 0;
    Dummy ="not set";
    // Make ALL card buttons visible again. Including dummy cards (for now)
    visibleAll(true);
    // Decrease the index of the stacked widget to go back to the auction
    ui->stackedWidget->setCurrentIndex(0);
    // Update the title of the window
    QWidget::setWindowTitle("Auction");

    // Reset GUI elements
    ui->lblRoundInfo->setVisible(false);
    ui->tableSequence->clearContents();
    ui->tableSequence->horizontalHeader()->setVisible(true);

    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);
    ui->pushButton_ViewCards->setEnabled(false);
    ui->lblContract->setVisible(false);
    ui->lblDummy->setVisible(false);
    ui->lblDeclarer->setVisible(false);
    ui->lblDouble->setVisible(false);
    ui->lblContractPlay->setVisible(false);
    ui->pushButton_Play->setVisible(false);
    ui->lblTricksWonEW->setVisible(false);
    ui->lblTricksWonNS->setVisible(false);
    ui->lblPoints->setVisible(false);

//    if(play["Id"].toInt() == Userid)
//    {
//        QMessageBox over;
//        over.information(0,"Round Over",play["WinningPartnership"].toString() + " won the round");
//        over.setFixedSize(500,200);
//    }
}

// Implemented by Jacques
void GameScreen::scoreSlot(QJsonObject scores)
{
    QJsonObject NS = scores["NSscores"].toObject();
    QJsonObject EW = scores["EWscores"].toObject();

    NSarray[ArrCount] = NS;
    EWarray[ArrCount] = EW;
    ArrCount++;

    QString vul = "";
    QString nvul = "None";
    if(scores["NSscores"].toObject()["vulnerable"].toInt() == 1)
    {
        vul = vul + "NS";
        nvul = "";
    }
    if(scores["EWscores"].toObject()["vulnerable"].toInt() == 1)
    {
        vul = vul + "EW";
        nvul = "";
    }

    ui->lblVulnerable->setVisible(true);
    ui->lblVulnerable->setText("Vulnerable: " + vul + nvul);

    ScoreBoard scoreBoard(this);

    scoreBoard.updateScores(NSarray,EWarray,ArrCount);
    scoreBoard.setModal(true);

    scoreBoard.exec();
}

// Slot for DISCONNECT_PLAYER. All players will leave the match.
// DISCONNECTED_PLAYER received
void GameScreen::disconnectPlayerSlot(QJsonObject disc)
{
//    QString playerdisc = disc["PlayerPos"].toString();
//    QMessageBox over;
//    over.critical(0,"Player Disconnect",playerdisc + " was disconnected. Leaving the game.");
//    over.setFixedSize(500,200);

    UserPosition = "";
    Username = "";
    ui->tableSequence->clear();
    ui->lblTeam->setText("");
    ui->lblNameTeam->setText("");
    ui->lblOpp1->setText("");
    ui->lblOpp1Name->setText("");
    ui->lblOpp2->setText("");
    ui->lblOpp2Name->setText("");
    on_GameScreen_finished(1);
}

// Slot activates after successfully connecting to server. The "update" object
// contains the positions and aliases of all connected players.
// LOBBY_UPDATE received
void GameScreen::lobbyUpdateSlot(QJsonObject update)
{
    ui->lblVulnerable->setText("Vulnerable: None");
    ui->lblPosition->setVisible(true);
    QJsonValue value = update.value("PlayerPositions");
    QJsonArray arr = value.toArray();

    // Extract each position's alias
    foreach (const QJsonValue & v, arr)
    {
    if (v.toObject().value("Position").toString() == "N") {
        NorthAlias = v.toObject().value("Alias").toString();
        continue;
    }
    if (v.toObject().value("Position").toString() == "S") {
        SouthAlias = v.toObject().value("Alias").toString();
        continue;
    }
    if (v.toObject().value("Position").toString() == "E") {
        EastAlias = v.toObject().value("Alias").toString();
        continue;
    }
    if (v.toObject().value("Position").toString() == "W") {
        WestAlias = v.toObject().value("Alias").toString();
        continue;
    }
    }

    // Check which position the user is
    if (NorthAlias == Username) {
        UserPosition = "North";
    }
    if (SouthAlias == Username) {
        UserPosition = "South";
    }
    if (EastAlias == Username) {
        UserPosition = "East";
    }
    if (WestAlias == Username) {
        UserPosition = "West";
    }

    ui->lblPosition->setText("Position: " + UserPosition);

    // Update the user's GUI elements
    ui->lblNamePlayer->setText(Username);
    ui->lblPlayer->setText(UserPosition);

    if (UserPosition[0] == "N")
    {
        teamPos = "South";
        teamUsername = SouthAlias;
    }
    if (UserPosition[0] == "S")
    {
        teamPos = "North";
        teamUsername = NorthAlias;
    }
    if (UserPosition[0] == "E")
    {
        teamPos = "West";
        teamUsername = WestAlias;
    }
    if (UserPosition[0] == "W")
    {
        teamPos = "East";
        teamUsername = EastAlias;
    }

    // Update the teammate's labels
    ui->lblTeam->setText(teamPos);
    ui->lblNameTeam->setText(teamUsername);

    // Update the opponent labels
    ui->lblOpp1->setText("");
    ui->lblOpp1Name->setText(opp1Username);
    ui->lblOpp2->setText("");
    ui->lblOpp2Name->setText(opp2Username);

    // Set dummy labels to invisible
    bool visible = false;
    ui->pb_14->setVisible(visible);
    ui->pb_15->setVisible(visible);
    ui->pb_16->setVisible(visible);
    ui->pb_17->setVisible(visible);
    ui->pb_18->setVisible(visible);
    ui->pb_19->setVisible(visible);
    ui->pb_20->setVisible(visible);
    ui->pb_21->setVisible(visible);
    ui->pb_22->setVisible(visible);
    ui->pb_23->setVisible(visible);
    ui->pb_24->setVisible(visible);
    ui->pb_25->setVisible(visible);
    ui->pb_26->setVisible(visible);

    // Send PLAYER_READY message to server
    QString mes = clientgs->GenerateMessage("PLAYER_READY");
    QJsonObject temp = clientgs->CreateJObject(mes);
    temp["Id"] = Userid;
    mes = clientgs->CreateJString(temp);
    clientgs->SendMessageToServer(mes);
}

// GAME_END recieved
void GameScreen::gameEndSlot(QJsonObject end)
{
    QMessageBox over;
    over.information(0,"Game Over",end["WinningPartnership"].toString() + " won the game");
    over.setFixedSize(500,200);

    this->close();
}

// PING signal emitted
void GameScreen::ping()
{
   // Send ping to server
    QString mes = clientgs->GenerateMessage("PONG");
    QJsonObject obj = clientgs->CreateJObject(mes);
    obj["Id"] = Userid;
    clientgs->SendMessageToServer(clientgs->CreateJString(obj));
}

// PONG received
void GameScreen::pongSlot(QJsonObject pong)
{
    QString reply = pong["Type"].toString();
}

// Slot for when the PLAY_START message is received from the server. The QJsonObject
// received contains the dummy cards and will populate the dummy buttons.
// PLAY_START received
void GameScreen::playStartSlot(QJsonObject ob)
{
    ui->lblTricksWonEW->setVisible(true);
    ui->lblTricksWonNS->setVisible(true);
    ui->lblTricksWonEW->setText("");
    ui->lblTricksWonNS->setText("");

    ui->lblRoundInfo->setVisible(false);
    QJsonValue value = ob.value("DummyCards");
    QJsonArray array1 = value.toArray();
    int count = 0;

    // Extract and populate the cardsDummy array from the received object
    foreach (const QJsonValue & v, array1){
        for (int k=0;k<v.toObject().value("Rank").toArray().size();k++) {
            cardsDummy[count] = v.toObject().value("Suit").toString() + v.toObject().value("Rank")[k].toString();
            count++;
        }
    }

    // Only load the dummy cards if the user is NOT the dummy - otherwise the same cards would appear twice on the screen
    if (UserPosition[0] != Dummy[0])
    {
        // Load the dummy cards into GUI. Set parameter to 1 to indicate it's the dummy cards being loaded
       showCards(1);
    }

    // Make all the card buttons visible
    visibleAll(true);

    // Disable all the cards
    disableCards(2);
}

/* Slot for when a MOVE_REQUEST signal is received from the server. This slot function will
 enable/disable the relevent card labels depending on if the player cards should be played,
 or the dummy cards. Because these components are now enabled and thus clickable, the relevent
 card played will be sent back to the server from within the component on_clicked slot. */
// MOVE_REQUEST received
void GameScreen::moveRequestSlot(QJsonObject request)
{
    //Sleep(1000);
    ui->lblRoundInfo->setVisible(false);

    // Check where the card played should be from
    if (request["MoveDummy"] == false)
    { // Move must be made from player cards. Enable player cards
        disableCards(0, true);
    }
    if (request["MoveDummy"] == true)
    { // Move must be made from dummy cards. Enable dummy cards
        if (Dummy[0] != UserPosition[0]) {
            disableCards(1, true);
        }
        else { // If the user is the dummy, and the dummy cards must be played, the user's
              //  teammate must make a move, not the user.
            disableCards(0, false);
        }

    }
}

/* The slots below are for each individual card push button clicked. The corresponding card represented
 by a push button is stored in the corresponding index in the cards/dummyCards array.*/
void GameScreen::on_pb_1_clicked()
{
    sendMove(cards[0].at(0), cards[0].at(1));
}

void GameScreen::on_pb_2_clicked()
{
    sendMove(cards[1].at(0), cards[1].at(1));
}

void GameScreen::on_pb_3_clicked()
{
    sendMove(cards[2].at(0), cards[2].at(1));
}

void GameScreen::on_pb_4_clicked()
{
    sendMove(cards[3].at(0), cards[3].at(1));
}

void GameScreen::on_pb_5_clicked()
{
    sendMove(cards[4].at(0), cards[4].at(1));
}

void GameScreen::on_pb_6_clicked()
{
    sendMove(cards[5].at(0), cards[5].at(1));
}

void GameScreen::on_pb_7_clicked()
{
    sendMove(cards[6].at(0), cards[6].at(1));
}

void GameScreen::on_pb_8_clicked()
{
    sendMove(cards[7].at(0), cards[7].at(1));
}

void GameScreen::on_pb_9_clicked()
{
    sendMove(cards[8].at(0), cards[8].at(1));
}

void GameScreen::on_pb_10_clicked()
{
    sendMove(cards[9].at(0), cards[9].at(1));
}

void GameScreen::on_pb_11_clicked()
{
    sendMove(cards[10].at(0), cards[10].at(1));
}

void GameScreen::on_pb_12_clicked()
{
    sendMove(cards[11].at(0), cards[11].at(1));
}

void GameScreen::on_pb_13_clicked()
{
    sendMove(cards[12].at(0), cards[12].at(1));
}

void GameScreen::on_pb_14_clicked()
{
    sendMove(cardsDummy[0].at(0), cardsDummy[0].at(1));
}

void GameScreen::on_pb_15_clicked()
{
    sendMove(cardsDummy[1].at(0), cardsDummy[1].at(1));
}

void GameScreen::on_pb_16_clicked()
{
    sendMove(cardsDummy[2].at(0), cardsDummy[2].at(1));
}

void GameScreen::on_pb_17_clicked()
{
    sendMove(cardsDummy[3].at(0), cardsDummy[3].at(1));
}

void GameScreen::on_pb_18_clicked()
{
    sendMove(cardsDummy[4].at(0), cardsDummy[4].at(1));
}

void GameScreen::on_pb_19_clicked()
{
    sendMove(cardsDummy[5].at(0), cardsDummy[5].at(1));
}

void GameScreen::on_pb_20_clicked()
{
    sendMove(cardsDummy[6].at(0), cardsDummy[6].at(1));
}

void GameScreen::on_pb_21_clicked()
{
    sendMove(cardsDummy[7].at(0), cardsDummy[7].at(1));
}

void GameScreen::on_pb_22_clicked()
{
    sendMove(cardsDummy[8].at(0), cardsDummy[8].at(1));
}

void GameScreen::on_pb_23_clicked()
{
    sendMove(cardsDummy[9].at(0), cardsDummy[9].at(1));
}

void GameScreen::on_pb_24_clicked()
{
    sendMove(cardsDummy[10].at(0), cardsDummy[10].at(1));
}

void GameScreen::on_pb_25_clicked()
{
    sendMove(cardsDummy[11].at(0), cardsDummy[11].at(1));
}

void GameScreen::on_pb_26_clicked()
{
    sendMove(cardsDummy[12].at(0), cardsDummy[12].at(1));
}

void GameScreen::on_GameScreen_destroyed()
{
    on_GameScreen_finished(0);
}
