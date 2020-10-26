#include "gamescreen.h"
#include "ui_gamescreen.h"
#include "scoreboard.h"
#include "QPixmap"
#include <QJsonArray>
#include <QMessageBox>
#include <iostream>
using namespace std;

// Establish connection to the server
//clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), true);
/* Declare a pointer clientconnection object that points to the original
   client object established in mainwindow.*/
clientconnection* clientgs;
// cards is the user's cards
QString cards[13];
// cardsDummy is the dummy's cards
QString cardsDummy[13];
QString currentBidSuit;
QString currentBidRank;
int counter = 0;
int row = 0;
int Userid = 0;
QString Username;
QString NorthAlias;
QString SouthAlias;
QString WestAlias;
QString EastAlias;
QString UserPosition;
QString Declarer;
QString Dummy;
QString Trump;
bool Double = false;
bool Redouble = false;
QString Contract;
// moveCounter holds how many cards have been played in the current round
int moveCounter = 0;
QString teamPos;
QString teamUsername;
QString opp1Pos;
QString opp1Username;
QString opp2Pos;
QString opp2Username;

/* Function to load the player cards as well as the dummy's cards
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
    // The pushButton_Play will only be visible once the auction is over,
    // however for testing purposes it should remain visible as it will
    // allow access to the Normal Play screen.
    //ui->pushButton_Play->setVisible(false);

    // Make the moves played push buttons invisible
    ui->pb_Move_1->setVisible(false);
    ui->pb_Move_2->setVisible(false);
    ui->pb_Move_3->setVisible(false);
    ui->pb_Move_4->setVisible(false);
    //clientgs = clienttoets;
    // Connect all relevant signals and slots
//    connect(clientgs, SIGNAL(bidStartSignal(QJsonObject)),this, SLOT(bidStartSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(bidRequestSignal()), this, SLOT(bidRequestSlot()));
//    connect(clientgs, SIGNAL(bidUpdateSignal(QJsonObject)), this, SLOT(bidUpdateSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(bidEndSignal(QJsonObject)), this, SLOT(bidEndSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(playStartSignal(QJsonObject)), this, SLOT(playStartSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(lobbyUpdateSignal(QJsonObject)), this, SLOT(lobbyUpdateSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(moveRequestSignal(QJsonObject)), this, SLOT(moveRequestSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(moveUpdateSignal(QJsonObject)), this, SLOT(moveUpdateSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(trickEndSignal(QJsonObject)), this, SLOT(trickEndSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(playEndSignal(QJsonObject)), this, SLOT(playEndSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(gameEndSignal(QJsonObject)), this, SLOT(gameEndSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(disconnectPlayerSignal(QJsonObject)), this, SLOT(disconnectPlayerSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(pongSignal(QJsonObject)), this, SLOT(pongSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(scoreSignal(QJsonObject)), this, SLOT(scoreSlot(QJsonObject)));

    // Code to grey out a cell (0, 1). Will be used to indicate which bids will
    // be valid and which not with integration.
    //  QColor col;
    //  col.setRgb(100, 100, 100);

//      QTableWidgetItem* selectedItem2 = new QTableWidgetItem;
//      selectedItem2->setText("zxczc");
//      ui->tableSequence->setItem(1,1,selectedItem2);


//    QString mes = clientgs->GenerateMessage("BID_START");
//    //QJsonObject bids = client.CreateJObject(mes);
//    clientgs->SendMessageToServer(mes);
}



GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::connectSlots()
{
//    // Connect all relevant signals and slots
//    connect(clientgs, SIGNAL(bidStartSignal(QJsonObject)),this, SLOT(bidStartSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(bidRequestSignal()), this, SLOT(bidRequestSlot()));
//    connect(clientgs, SIGNAL(bidUpdateSignal(QJsonObject)), this, SLOT(bidUpdateSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(bidEndSignal(QJsonObject)), this, SLOT(bidEndSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(playStartSignal(QJsonObject)), this, SLOT(playStartSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(lobbyUpdateSignal(QJsonObject)), this, SLOT(lobbyUpdateSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(moveRequestSignal(QJsonObject)), this, SLOT(moveRequestSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(moveUpdateSignal(QJsonObject)), this, SLOT(moveUpdateSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(trickEndSignal(QJsonObject)), this, SLOT(trickEndSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(playEndSignal(QJsonObject)), this, SLOT(playEndSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(gameEndSignal(QJsonObject)), this, SLOT(gameEndSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(disconnectPlayerSignal(QJsonObject)), this, SLOT(disconnectPlayerSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(pongSignal(QJsonObject)), this, SLOT(pongSlot(QJsonObject)));
//    connect(clientgs, SIGNAL(scoreSignal(QJsonObject)), this, SLOT(scoreSlot(QJsonObject)));
}

// If the game is left, for which ever reason, this slot ensure that
// the user is taken back to the main screen.
void GameScreen::on_GameScreen_finished(int result)
{
    // Show the parent again, in this case main window
    parentWidget()->show();
}

// Slot to show the scoreboard. The scoreboard can be viewed at
// any time by pressing this button. The modal approach is used,
// so the game screen will not be destroyed, yet also not usable
// while the scoreboard is displayed.
void GameScreen::on_pushButton_Score_clicked()
{
    // Create new instance of scoreBoard, set parent as this
    // (Game Screen dialog)
//    ScoreBoard scoreBoard(this);
//    // Use modal approach
//    scoreBoard.setModal(true);
//    scoreBoard.exec();
//    ScoreBoard *sb = new ScoreBoard(this);
//    sb->show();
//    sb->updateScores()
}

// Once the auction is over, the pushButton_Play will be made visible.
// For testing purposes this button will remain visible.
void GameScreen::on_pushButton_Play_clicked()
{
    //connect(clientgs, SIGNAL(playStartSignal(QJsonObject)), this, SLOT(playStartSlot(QJsonObject)));
    ui->pushButton_BackAuction->setVisible(false);
    ui->pushButton_Abandon->setVisible(true);
    // Increase the index of the stacked widget to the Normal Play
    // page.
    ui->stackedWidget->setCurrentIndex(1);
    // Update the title of the window
    QWidget::setWindowTitle("Normal Play");

    // Simulate the PLAY_START message received from the server
    QString mes = clientgs->GenerateMessage("PLAY_START");
    clientgs->SendMessageToServer(mes);
    clientgs->onTextMessageReceived(mes);

    mes = clientgs->GenerateMessage("SCORE");
    clientgs->onTextMessageReceived(mes);
}


// Close the Game Screen page.
// The user will be taken back to the Main Screen.
void GameScreen::on_pushButton_Abandon_clicked()
{
    this->close();
}

/* Helper function to load and display cards received from the server. Variable i is used
to distinguish between loading the player's cards (i = 0), or the dummy's cards (i = 1). */
void GameScreen::showCards(int i)
{
    visibleAll();
    QString paths[13];

    if (i == 0)
    { // Load player cards
        for (int k=0;k<13;k++) {
            if (cards[k] != "") {
                paths[k] = "../Cards/" + cards[k];
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
        if (Dummy != UserPosition[0]) // Don't load the dummy cards if the user is already the dummy
        {
            for (int k=0;k<13;k++) {
                if (cardsDummy[k] != "") {
                    paths[k] = "../Cards/" + cardsDummy[k];
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

// Helper function that enables/disables the card labels. if i = 0, then the player's cards are
// enabled/disabled. If i = 1, then the dummy's cards are enabled/disabled. If i = 2, then both the
// player and the dummy's cards are disabled. Enabled/disabled is determined by bool en.
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
    QJsonObject bid2 = bid["Bid"].toObject();
    bid2["Suit"] = Suit;
    if (Rank == "") {
        bid2["Rank"] = NULL;
    } else {
           bid2["Rank"] = Rank;
        }

    bid["Bid"] = bid2;
    bid["Id"] = Userid;

    // Disable GUI elements until another BID_REQUEST is received from server
    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);
    //Send the updated message to the server
    clientgs->SendMessageToServer(clientgs->CreateJString(bid));

    // DEBUG Code simulating 3 bids that have to be made by the user
    if (counter < 4) {
        // Temp debug code to test BID_REQUEST with bidRequestSignal/Slot
        cout<<QString::number(counter).toStdString()<<endl;
        mes = clientgs->GenerateMessage("BID_REQUEST");
        clientgs->onTextMessageReceived(mes);
        counter++;
    }


}

// NOT A SLOT. Function to send a move made by the player
void GameScreen::sendMove(QString Suit, QString Rank)
{
    QString mes = clientgs->GenerateMessage("MOVE_SEND");
    QJsonObject move = clientgs->CreateJObject(mes);
    QJsonObject move2 = move["Bid"].toObject();
    move2["Suit"] = Suit;
    move2["Rank"] = Rank;
    move["Bid"] = move2;
    move["Id"] = Userid;
    // Disable card elements
    disableCards(2);
    //Send the updated message to the server
    clientgs->SendMessageToServer(clientgs->CreateJString(move));
}


// Slot to receive the server info and display in a label. This is the 1st slot to activate in gamescree.cpp,
// and thus most of the signals and slots will be connected from here.
void GameScreen::serverInfoSlot(QString ip, QString port, QString pass, clientconnection *client1, QString usern, int ID)
{

    Userid = ID;
    Username = usern;
    ui->lblInfo->setText("IP: " + ip + " Port Number: " + port + " Password: " + pass);
    clientgs = client1;

//    clientconnection *client2 = new clientconnection(QUrl(QStringLiteral("ws://localhost:159")), true);
//    clientgs = client2;
    //connectSlots();
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
    connect(clientgs, SIGNAL(scoreSignal(QJsonObject)), this, SLOT(scoreSlot(QJsonObject)));
cout<<"422 serverinfoslot"<<endl;
    // Debug code
    QString mes = clientgs->GenerateMessage("BID_END");
    // Temp debug code. NEE VERKEERD, HAAL NET UIT SODRA KLAAR --> In reality this must be clientgs->sendToServer(
    clientgs->onTextMessageReceived(mes);

//    mes = clientgs->GenerateMessage("PLAY_START");
//    clientgs->onTextMessageReceived(mes);
    //disableCards(1, true);
    // Debug code to test that the bids are placed in the correct cells
//    QJsonObject temp = clientgs->CreateJObject(mes);
//    temp["Player"] = "W";
//    mes = clientgs->CreateJString(temp);
//    clientgs->onTextMessageReceived(mes);

//    temp["Player"] = "N";
//    mes = clientgs->CreateJString(temp);
//    clientgs->onTextMessageReceived(mes);

//    temp["Player"] = "E";
//    mes = clientgs->CreateJString(temp);
//    clientgs->onTextMessageReceived(mes);

//    temp["Player"] = "S";
//    mes = clientgs->CreateJString(temp);
//    clientgs->onTextMessageReceived(mes);

}

/* Slot for BID_START signal */
void GameScreen::bidStartSlot(QJsonObject cardsdealt)
{
    QJsonValue value = cardsdealt.value("Cards");
    QJsonArray array1 = value.toArray();
    int count = 0;

    foreach (const QJsonValue & v, array1){
        for (int k=0;k<v.toObject().value("Rank").toArray().size();k++) {
            cards[count] = v.toObject().value("Suit").toString() + v.toObject().value("Rank")[k].toString();
            count++;
        }
    }

    cout<<"Player Cards: ";
    // Temp debug code
    for (int k=0;k<13;k++) {
        cout<<cards[k].toStdString()<<", ";
    }
    cout<<endl;

    // Load the cards into GUI. Set the parameter to 0 to indicate it is the user's cards being loaded.
    showCards(0);
    // Disable the player and dummy card objects
    //disableCards(2, true);
    // Om die rank te kry cout<<"******"<<v.toObject().value("Rank")[0].toString().toStdString()<<endl;
    // Om die suit te kry cout<<"******"<<v.toObject().value("Suit").toString().toStdString()<<endl;

    // Disable GUI elements until a BID_REQUEST is received from server
    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);
    ui->pushButton_ViewCards->setEnabled(true);

    /* In die normale flow of events sal die server na bg 'n BID_REQUEST stuur, maar omdat
       die server nou nie hier is nie word dit gesimulate in die sendBid function bo.
       Dis meer realisties om dit daar te doen want anders is daar net 1 request wat gestuur word
       en dis dit - nou kan ons klomp stuur. */
    // Temp debug code to test BID_REQUEST with bidRequestSignal/Slot
//    QString mes = clientgs->GenerateMessage("BID_REQUEST");
//    clientgs->onTextMessageReceived(mes);
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


void GameScreen::on_tableBids_cellClicked(int row, int column)
{
    currentBidRank = QString::number(row+1);
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

    // call function to send bid; BID_SEND
    sendBid(currentBidSuit, currentBidRank);
    ui->tableBids->clearSelection();
}

void GameScreen::on_pushButton_Double_clicked()
{
    currentBidSuit = "DOUBLE";
    currentBidRank = "";

    // call function to send bid; BID_SEND
    sendBid(currentBidSuit, currentBidRank);
    ui->tableBids->clearSelection();
}

void GameScreen::on_pushButton_Redouble_clicked()
{
    currentBidSuit = "REDOUBLE";
    currentBidRank = "";

    // call function to send bid; BID_SEND
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
    QString Suit = bid["Bid"].toObject()["Suit"].toString();
    QString Rank = bid["Bid"].toObject()["Rank"].toString();

    int col = 0;

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

    if (bid["Player"] == "W") {
        row++;
    }
}


void GameScreen::addToTable(QString bid, int col)
{
    QTableWidgetItem* selectedItem = new QTableWidgetItem;
    selectedItem->setText(bid);
    selectedItem->setTextAlignment(4);
    ui->tableSequence->setItem(row,col,selectedItem);
}

// Helper function that makes all the cards on the table visible
void GameScreen::visibleAll(bool vis)
{
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
    cout<<"685 bidendslot"<<endl;
    QString NDeclarer = "";
    QString SDeclarer = "";
    QString EDeclarer = "";
    QString WDeclarer = "";
    QString NDummy = "";
    QString SDummy = "";
    QString EDummy = "";
    QString WDummy = "";

    // Disable GUI elements on bidding screen
    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);
    ui->pushButton_BackAuction->setVisible(false);
    ui->pushButton_ViewCards->setEnabled(false);

    // Extract information from JSON Object
    Contract = contract["Bid"].toObject()["Suit"].toString() + contract["Bid"].toObject()["Rank"].toString() ;
    Declarer = contract["Declarer"].toString();
    Dummy = contract["Dummy"].toString();
    Trump = contract["Trump"].toString();
    Double = contract["Bid"].toObject()["IsDouble"].toBool();
    Redouble = contract["Bid"].toObject()["IsRedouble"].toBool();

    cout<<"709 Declarer: "<<Declarer.toStdString()<<endl;

    ui->lblContract->setVisible(true);
    ui->lblDummy->setVisible(true);
    ui->lblDeclarer->setVisible(true);
    ui->lblDouble->setVisible(true);
    ui->lblContractPlay->setVisible(true);
    ui->pushButton_Play->setVisible(true);
    // Update GUI elements
    ui->lblContract->setText("Contract: " + Contract);
    ui->lblDeclarer->setText("Declarer: " + Declarer);
    ui->lblDummy->setText("Dummy: " + Dummy);
    ui->lblContractPlay->setText("Contract: " + Contract);

    if (Double == false && Redouble == true) {
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

    if (Declarer == "N") {
        NDeclarer = " (Declarer)";
        }
    if (Declarer == "E") {
        EDeclarer = " (Declarer)";
        }
    if (Declarer == "S") {
        SDeclarer = " (Declarer)";
        }
    if (Declarer == "W") {
        WDeclarer = " (Declarer)";
        }

    if (Dummy == "N") {
        NDummy = " (Dummy)";
        }
    if (Dummy == "E") {
        EDummy = " (Dummy)";
        }
    if (Dummy == "S") {
        SDummy = " (Dummy)";
        }
    if (Dummy == "W") {
        WDummy = " (Dummy)";
        }

    // Do the user's info labels first
    ui->lblPlayer->setText(UserPosition);
    ui->lblNamePlayer->setText(Username);

    if (Dummy == UserPosition[0]) {
        ui->lblPlayer->setText(UserPosition + " (Dummy)");

        // if player == dummy then make top cards invisible
        // Make the dummy labels invisible
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

    if (Declarer == UserPosition[0]) {
        ui->lblPlayer->setText(UserPosition + " (Declarer)");
    }

    // Do the user's teammate
    if (UserPosition[0] == "N") {
        teamPos = "South" + SDummy + SDeclarer;
        teamUsername = SouthAlias;
        // Get the opponent's info
        opp1Pos = "East" + EDummy + EDeclarer;
        opp1Username = EastAlias;
        opp2Pos = "West" + WDummy + WDeclarer;
        opp2Username = WestAlias;
    }
    if (UserPosition[0] == "S") {
        teamPos = "North" + NDummy + NDeclarer;
        teamUsername = NorthAlias;

        opp1Pos = "East" + EDummy + EDeclarer;
        opp1Username = EastAlias;
        opp2Pos = "West" + WDummy + WDeclarer;
        opp2Username = WestAlias;
    }
    if (UserPosition[0] == "E") {
        teamPos = "West" + WDummy + WDeclarer;
        teamUsername = WestAlias;

        opp1Pos = "North" + NDummy + NDeclarer;
        opp1Username = NorthAlias;
        opp2Pos = "South" + SDummy + SDeclarer;
        opp2Username = SouthAlias;
    }
    if (UserPosition[0] == "W") {
        teamPos = "East" + EDummy + EDeclarer;
        teamUsername = EastAlias;

        opp1Pos = "North" + NDummy + NDeclarer;
        opp1Username = NorthAlias;
        opp2Pos = "South" + SDummy + SDeclarer;
        opp2Username = SouthAlias;
    }
    ui->lblTeam->setText(teamPos);
    ui->lblNameTeam->setText(teamUsername);

    // Do the other team
    ui->lblOpp1->setText(opp1Pos);
    ui->lblOpp1Name->setText(opp1Username);
    ui->lblOpp2->setText(opp2Pos);
    ui->lblOpp2Name->setText(opp2Username);
}

// Slot for MOVE_UPDATE. This slot will update the display showing the card played by a player.
// MOVE_UPDATE received
void GameScreen::moveUpdateSlot(QJsonObject move)
{
    QString Suit = move["Bid"].toObject()["Suit"].toString();
    QString Rank = move["Bid"].toObject()["Rank"].toString();
    QString cardplayed = Suit + Rank;

    // Check if the card played was from the dummy
    if (UserPosition[0] != Dummy && UserPosition[0] != Declarer)
    { // User is not the dummy nor declarer
        for (int k=0;k<13;k++)
        {
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
    }

    // If the user is the dummy and his teammate played one of his cards
    if (UserPosition[0] == Dummy)
    { // User is the dummy and one of his cards has been played by the declarer
        for (int k=0;k<13;k++)
        {
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
    }

    if (moveCounter == 0)
    { // Load into 1st move button
        ui->pb_Move_1->setVisible(true);
        loadCards(ui->pb_Move_1, "../Cards/" + Suit + Rank);
        moveCounter++;
    }
    if (moveCounter == 1)
    { // Load into 2nd move button
        ui->pb_Move_2->setVisible(true);
        loadCards(ui->pb_Move_2, "../Cards/" + Suit + Rank);
        moveCounter++;
    }
    if (moveCounter == 2)
    { // Load into 3rd move button
        ui->pb_Move_3->setVisible(true);
        loadCards(ui->pb_Move_3, "../Cards/" + Suit + Rank);
        moveCounter++;
    }
    if (moveCounter == 3)
    { // Load into 4th move button
        ui->pb_Move_4->setVisible(true);
        loadCards(ui->pb_Move_4, "../Cards/" + Suit + Rank);
        moveCounter++;
    }
}

// Slot for when TRICK_END is received.
// TRICK_END received
void GameScreen::trickEndSlot(QJsonObject trick)
{
    // Reset move counter of current trick
    moveCounter = 0;

    // Reset move buttons
    ui->pb_Move_1->setIcon(QIcon());
    ui->pb_Move_1->setVisible(false);
    ui->pb_Move_2->setIcon(QIcon());
    ui->pb_Move_2->setVisible(false);
    ui->pb_Move_3->setIcon(QIcon());
    ui->pb_Move_3->setVisible(false);
    ui->pb_Move_4->setIcon(QIcon());
    ui->pb_Move_4->setVisible(false);

    // Disable all cards
    disableCards(2);

    ui->lblRoundInfo->setVisible(true);
    ui->lblRoundInfo->setText(trick["WinningPartnership"].toString() + " won the trick");
}

// Slot for "PLAY_END". The user will return to the bidding screen and new cards dealt
// PLAY_END received
void GameScreen::playEndSlot(QJsonObject play)
{
    // Make all card buttons visible again
    visibleAll();
    // Decrease the index of the stacked widget to go back to the auction
    ui->stackedWidget->setCurrentIndex(0);
    // Update the title of the window
    QWidget::setWindowTitle("Auction");



    ui->lblRoundInfo->setVisible(false);
    ui->tableSequence->clear();
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
    // Uncomment pb_Play->setVisible(false) for final implementation
    // ui->pushButton_Play->setVisible(false);

    QMessageBox over;
    over.information(0,"Round Over",play["WinningPartnership"].toString() + " won the round");
    over.setFixedSize(500,200);
}

void GameScreen::scoreSlot(QJsonObject scores)
{
//    ScoreBoard scoreBoard(this);
//    // Use modal approach
//    scoreBoard.setModal(true);
//    scoreBoard.exec();
//    scoreBoard.updateScores(scores);

    ScoreBoard *sb = new ScoreBoard(this);
    sb->show();
    sb->updateScores(scores);
}

// Slot for DISCONNECT_PLAYER. All players will leave the match.
// DISCONNECTED_PLAYER received
void GameScreen::disconnectPlayerSlot(QJsonObject disc)
{
    QString playerdisc = disc["PlayerPos"].toString();
    QMessageBox over;
    over.critical(0,"Player Disconnect",playerdisc + " was disconnected. Leaving the game.");
    over.setFixedSize(500,200);

    this->close();
}

// Slot activates after successfully connecting to server. The "update" object
// contains the positions and aliases of all connected players.
// LOBBY_UPDATE received
void GameScreen::lobbyUpdateSlot(QJsonObject update)
{
    QJsonValue value = update.value("Cards");
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

    // Update Game Screen GUI elements
    ui->lblNamePlayer->setText(Username);
    ui->lblPlayer->setText(UserPosition);

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
    // Debug code
    clientgs->onTextMessageReceived(mes);

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
    QString mes = clientgs->GenerateMessage("PING");
    QJsonObject obj = clientgs->CreateJObject(mes);
    obj["Id"] = Userid;
    clientgs->SendMessageToServer(clientgs->CreateJString(obj));

    // Debug code
    // clientgs->onMessageReceived("PING")
}

// PONG received
void GameScreen::pongSlot(QJsonObject pong)
{
    QString reply = pong["Type"].toString();
    // Debug code
    // cout<<"Pong received from server"<<endl;
}

// Slot for when the PLAY_START message is received from the server. The QJsonObject
// received contains the dummy cards and will populate the dummy buttons.
// PLAY_START received
void GameScreen::playStartSlot(QJsonObject ob)
{
    cout<<"803"<<endl;
    ui->lblRoundInfo->setVisible(false);
    QJsonValue value = ob.value("DummyCards");
    QJsonArray array1 = value.toArray();
    int count = 0;

    foreach (const QJsonValue & v, array1){
        for (int k=0;k<v.toObject().value("Rank").toArray().size();k++) {
            cardsDummy[count] = v.toObject().value("Suit").toString() + v.toObject().value("Rank")[k].toString();
            count++;
        }
    }

    cout<<"Dummy Cards: ";
    // Temp debug code
    for (int k=0;k<13;k++) {
        cout<<cardsDummy[k].toStdString()<<", ";
    }
    cout<<endl;
    // Load the dummy cards into GUI. Set parameter to 1 to indicate it's the dummy cards being loaded
    showCards(1);
}

// Slot for when a MOVE_REQUEST signal is received from the server. This slot function will
// enable/disable the relevent card labels depending on if the player cards should be played,
// or the dummy cards. Because these components are now enabled and thus clickable, the relevent
// card played will be sent back to the server from within the component on_clicked slot.
// MOVE_REQUEST received
void GameScreen::moveRequestSlot(QJsonObject request)
{
    if (request["MoveDummy"] == false)
    { // Move must be made from player cards
        disableCards(0, true);
    }
    if (request["MoveDummy"] == true)
    { // Move must be made from dummy cards
        if (Dummy != UserPosition[0]) {
            disableCards(1, true);
        }
        else { // If the user is the dummy, and the dummy cards must be played, the user's
               // team mate must make a move, not the user.
            disableCards(0, false);
        }

    }
}


/* The slots below are for each individual card push button clicked. The corresponding card represented
 by a push button is stored in the corresponding index in the cards/dummyCards array.*/
void GameScreen::on_pb_1_clicked()
{
    sendMove(cards[0].at(0), cards[0].at(1));
    ui->pb_1->setVisible(false);
}

void GameScreen::on_pb_2_clicked()
{
    sendMove(cards[1].at(0), cards[1].at(1));
    ui->pb_2->setVisible(false);
}

void GameScreen::on_pb_3_clicked()
{
    sendMove(cards[2].at(0), cards[2].at(1));
    ui->pb_3->setVisible(false);
}

void GameScreen::on_pb_4_clicked()
{
    sendMove(cards[3].at(0), cards[3].at(1));
    ui->pb_4->setVisible(false);
}

void GameScreen::on_pb_5_clicked()
{
    sendMove(cards[4].at(0), cards[4].at(1));
    ui->pb_5->setVisible(false);
}

void GameScreen::on_pb_6_clicked()
{
    sendMove(cards[5].at(0), cards[5].at(1));
    ui->pb_6->setVisible(false);
}

void GameScreen::on_pb_7_clicked()
{
    sendMove(cards[6].at(0), cards[6].at(1));
    ui->pb_7->setVisible(false);
}

void GameScreen::on_pb_8_clicked()
{
    sendMove(cards[7].at(0), cards[7].at(1));
    ui->pb_8->setVisible(false);
}

void GameScreen::on_pb_9_clicked()
{
    sendMove(cards[8].at(0), cards[8].at(1));
    ui->pb_9->setVisible(false);
}

void GameScreen::on_pb_10_clicked()
{
    sendMove(cards[9].at(0), cards[9].at(1));
    ui->pb_10->setVisible(false);
}

void GameScreen::on_pb_11_clicked()
{
    sendMove(cards[10].at(0), cards[10].at(1));
    ui->pb_11->setVisible(false);
}

void GameScreen::on_pb_12_clicked()
{
    sendMove(cards[11].at(0), cards[11].at(1));
    ui->pb_12->setVisible(false);
}

void GameScreen::on_pb_13_clicked()
{
    sendMove(cards[12].at(0), cards[12].at(1));
    ui->pb_13->setVisible(false);
}

void GameScreen::on_pb_14_clicked()
{
    sendMove(cardsDummy[0].at(0), cardsDummy[0].at(1));
    ui->pb_14->setVisible(false);
}

void GameScreen::on_pb_15_clicked()
{
    sendMove(cardsDummy[1].at(0), cardsDummy[1].at(1));
    ui->pb_15->setVisible(false);
}

void GameScreen::on_pb_16_clicked()
{
    sendMove(cardsDummy[2].at(0), cardsDummy[2].at(1));
    ui->pb_16->setVisible(false);
}

void GameScreen::on_pb_17_clicked()
{
    sendMove(cardsDummy[3].at(0), cardsDummy[3].at(1));
    ui->pb_17->setVisible(false);
}

void GameScreen::on_pb_18_clicked()
{
    sendMove(cardsDummy[4].at(0), cardsDummy[4].at(1));
    ui->pb_18->setVisible(false);
}

void GameScreen::on_pb_19_clicked()
{
    sendMove(cardsDummy[5].at(0), cardsDummy[5].at(1));
    ui->pb_19->setVisible(false);
}

void GameScreen::on_pb_20_clicked()
{
    sendMove(cardsDummy[6].at(0), cardsDummy[6].at(1));
    ui->pb_20->setVisible(false);
}

void GameScreen::on_pb_21_clicked()
{
    sendMove(cardsDummy[7].at(0), cardsDummy[7].at(1));
    ui->pb_21->setVisible(false);
}

void GameScreen::on_pb_22_clicked()
{
    sendMove(cardsDummy[8].at(0), cardsDummy[8].at(1));
    ui->pb_22->setVisible(false);
}

void GameScreen::on_pb_23_clicked()
{
    sendMove(cardsDummy[9].at(0), cardsDummy[9].at(1));
    ui->pb_23->setVisible(false);
}

void GameScreen::on_pb_24_clicked()
{
    sendMove(cardsDummy[10].at(0), cardsDummy[10].at(1));
    ui->pb_24->setVisible(false);
}

void GameScreen::on_pb_25_clicked()
{
    sendMove(cardsDummy[11].at(0), cardsDummy[11].at(1));
    ui->pb_25->setVisible(false);
}

void GameScreen::on_pb_26_clicked()
{
    sendMove(cardsDummy[12].at(0), cardsDummy[12].at(1));
    ui->pb_26->setVisible(false);
}
