#include "gamescreen.h"
#include "ui_gamescreen.h"
#include "scoreboard.h"
#include "QPixmap"
#include <QJsonArray>
#include <iostream>
using namespace std;

// Establish connection to the server
//clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), true);
/* Declare a pointer clientconnection object that points to the original
   client object established in mainwindow.*/
clientconnection* clientgs;
QString cards[13];
QString currentBidSuit;
QString currentBidRank;
int counter = 0;
int row = 0;
// Function to load the player cards as well as the dummy's cards
// Once integrated it will receive the actual cards to load from server
// The function receives a label object and a file path to which the
// label object will be set.
void GameScreen::loadCards(QLabel *lbl, QString path){
    // Create a pixmap from the received path string
    QPixmap pm(path);
    // Configure the label object to display the card image
    lbl->setPixmap(path);
    lbl->setScaledContents(true);
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
    // Set the title of the window
    QWidget::setWindowTitle("Auction");
    // Ensure that the correct interface is displayed when joining a game
    ui->stackedWidget->setCurrentIndex(0);
    // The pushButton_Play will only be visible once the auction is over,
    // however for testing purposes it should remain visible as it will
    // allow access to the Normal Play screen.
    //ui->pushButton_Play->setVisible(false);


    // The below code is a temporary placeholder for populating the card
    // components randomly each time the Game Screen is shown. Once
    // integration is started the actual cards to display will be received
    // from the game server.
//    QString paths[26];
//    QString suit[4] = {"D","C","H","S"};
//    srand(time(NULL));
//    int range = 12 - 0 + 1;
//    int rnum = rand() % range + 1;
//    int rnum2 = rand() % 4 + 1;
//    for (int k = 0;k<26 ;k++ ) {
//        rnum2 = rand() % 4 + 1;
//        if (rnum2 == 4){
//            rnum2 = 0;
//        }
//        rnum = rand() % range + 1;
//        if (rnum == 13){
//            paths[k] = "K" + suit[rnum2];
//            paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/"
//                    + paths[k] + ".jpg";
//            continue;
//        }

//        if (rnum==11) {
//            paths[k] = "J" + suit[rnum2];
//            paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/"
//                    + paths[k] + ".jpg";
//            continue;
//        }
//        if (rnum==12) {
//            paths[k] = "Q" + suit[rnum2];
//            paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/"
//                    + paths[k] + ".jpg";
//            continue;
//        }
//        if (rnum==1) {
//            paths[k] = "A" + suit[rnum2];
//            paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/"
//                    + paths[k] + ".jpg";
//            continue;
//        }

//        paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/" +
//                QString::number(rnum) + suit[rnum2] + ".jpg";
//    }

//    // As with above, the below code is only temporary, used to set each label to
//    // display the randomly generated playing cards. Will be removed once integration
//    // starts.
//    QLabel *lbl = ui->lblP_1;
//    loadCards(lbl, paths[0]);
//    lbl = ui->lblP_2;
//    loadCards(lbl, paths[1]);
//    lbl = ui->lblP_3;
//    loadCards(lbl, paths[2]);
//    lbl = ui->lblP_4;
//    loadCards(lbl, paths[3]);
//    lbl = ui->lblP_5;
//    loadCards(lbl, paths[4]);
//    lbl = ui->lblP_6;
//    loadCards(lbl, paths[5]);
//    lbl = ui->lblP_7;
//    loadCards(lbl, paths[6]);
//    lbl = ui->lblP_8;
//    loadCards(lbl, paths[7]);
//    lbl = ui->lblP_9;
//    loadCards(lbl, paths[8]);
//    lbl = ui->lblP_10;
//    loadCards(lbl, paths[9]);
//    lbl = ui->lblP_11;
//    loadCards(lbl, paths[10]);
//    lbl = ui->lblP_12;
//    loadCards(lbl, paths[11]);
//    lbl = ui->lblP_13;
//    loadCards(lbl, paths[12]);

//    // Dummy Cards
//    lbl = ui->lblP_14;
//    loadCards(lbl, paths[13]);
//    lbl = ui->lblP_15;
//    loadCards(lbl, paths[14]);
//    lbl = ui->lblP_16;
//    loadCards(lbl, paths[15]);
//    lbl = ui->lblP_17;
//    loadCards(lbl, paths[16]);
//    lbl = ui->lblP_18;
//    loadCards(lbl, paths[17]);
//    lbl = ui->lblP_19;
//    loadCards(lbl, paths[18]);
//    lbl = ui->lblP_20;
//    loadCards(lbl, paths[19]);
//    lbl = ui->lblP_21;
//    loadCards(lbl, paths[20]);
//    lbl = ui->lblP_22;
//    loadCards(lbl, paths[21]);
//    lbl = ui->lblP_23;
//    loadCards(lbl, paths[22]);
//    lbl = ui->lblP_24;
//    loadCards(lbl, paths[23]);
//    lbl = ui->lblP_25;
//    loadCards(lbl, paths[24]);
//    lbl = ui->lblP_26;
//    loadCards(lbl, paths[25]);

    // Code to grey out a cell (0, 1). Will be used to indicate which bids will
    // be valid and which not with integration.
    //  QColor col;
    //  col.setRgb(100, 100, 100);

//      QTableWidgetItem* selectedItem2 = new QTableWidgetItem;
//      selectedItem2->setText("zxczc");
//      ui->tableSequence->setItem(1,1,selectedItem2);
    // emit bid start signal ?
    //connect()

//    QString mes = clientgs->GenerateMessage("BID_START");
//    //QJsonObject bids = client.CreateJObject(mes);
//    clientgs->SendMessageToServer(mes);
}

GameScreen::~GameScreen()
{
    delete ui;
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
    ScoreBoard scoreBoard(this);
    // Use modal approach
    scoreBoard.setModal(true);
    scoreBoard.exec();
}

// Once the auction is over, the pushButton_Play will be made visible.
// For testing purposes this button will remain visible.
void GameScreen::on_pushButton_Play_clicked()
{
    ui->pushButton_BackAuction->setVisible(false);
    ui->pushButton_Abandon->setVisible(true);
    // Increase the index of the stacked widget to the Normal Play
    // page.
    ui->stackedWidget->setCurrentIndex(1);
    // Update the title of the window
    QWidget::setWindowTitle("Normal Play");

}

// Close the Game Screen page.
// The user will be taken back to the Main Screen.
void GameScreen::on_pushButton_Abandon_clicked()
{
    this->close();
}

void GameScreen::showCards()
{
    QString paths[13];
    for (int k=0;k<13;k++) {
        if (cards[k] == "") {
            continue;
        }
        //"../JFILES/"
        paths[k] = "../Cards/" + cards[k];
    }
    QLabel *lbl = ui->lblP_1;
    loadCards(lbl, paths[0]);
    lbl = ui->lblP_2;
    loadCards(lbl, paths[1]);
    lbl = ui->lblP_3;
    loadCards(lbl, paths[2]);
    lbl = ui->lblP_4;
    loadCards(lbl, paths[3]);
    lbl = ui->lblP_5;
    loadCards(lbl, paths[4]);
    lbl = ui->lblP_6;
    loadCards(lbl, paths[5]);
    lbl = ui->lblP_7;
    loadCards(lbl, paths[6]);
    lbl = ui->lblP_8;
    loadCards(lbl, paths[7]);
    lbl = ui->lblP_9;
    loadCards(lbl, paths[8]);
    lbl = ui->lblP_10;
    loadCards(lbl, paths[9]);
    lbl = ui->lblP_11;
    loadCards(lbl, paths[10]);
    lbl = ui->lblP_12;
    loadCards(lbl, paths[11]);
    lbl = ui->lblP_13;
    loadCards(lbl, paths[12]);

    ui->pushButton_ViewCards->setEnabled(true);
    ui->pushButton_BackAuction->setVisible(true);
    ui->pushButton_Abandon->setVisible(false);
}


// Helper function that sends the bid made by the player to the server
void GameScreen::sendBid(QString Suit, QString Rank)
{
    QString mes = clientgs->GenerateMessage("BID_SEND");
    QJsonObject bid = clientgs->CreateJObject(mes);
    QJsonObject bid2 = bid["Bid"].toObject();
//    QJsonObject bidSuit = bid["Bid"].toObject();
//    QJsonObject bidRank = bid["Rank"].toObject();
//    bidSuit["Suit"] = Suit;
//    bidRank["Rank"] = Rank;
    bid2["Suit"] = Suit;
    if (Rank == "") {
        bid2["Rank"] = NULL;
    } else {
           bid2["Rank"] = Rank;
        }

    bid["Bid"] = bid2;
    //cout<<"***"<<bid["Bid"].toObject()["Suit"].toString().toStdString()<<endl;
    //cout<<bid["Suit"].toString().toStdString()<<endl;
    //bid["Bid"].toObject().value("Rank") = "rank";

    // Disable GUI elements until another BID_REQUEST is received from server
    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);
    //Send the updated message to the server
    clientgs->SendMessageToServer(clientgs->CreateJString(bid));

    if (counter < 4) {
        // Temp debug code to test BID_REQUEST with bidRequestSignal/Slot
        cout<<QString::number(counter).toStdString()<<endl;
        mes = clientgs->GenerateMessage("BID_REQUEST");
        clientgs->onTextMessageReceived(mes);
       counter++;
    }


}


// Slot to receive the server info and display in a label
void GameScreen::serverInfoSlot(QString ip, QString port, QString pass, clientconnection *client1)
{
    ui->lblInfo->setText("IP: " + ip + " Port Number: " + port + " Password: " + pass);
    clientgs = client1;

    // Connect all relevant signals and slots
    connect(clientgs, SIGNAL(bidStartSignal(QJsonObject)),this, SLOT(bidStartSlot(QJsonObject)));
    connect(clientgs, SIGNAL(bidRequestSignal()), this, SLOT(bidRequestSlot()));
    connect(clientgs, SIGNAL(bidUpdateSignal(QJsonObject)), this, SLOT(bidUpdateSlot(QJsonObject)));
     connect(clientgs, SIGNAL(scoreSignal(QJsonObject)), this, SLOT(scoreSlot(QJsonObject)));

    QString mes = clientgs->GenerateMessage("BID_UPDATE");
    // Temp debug code. NEE VERKEERD, HAAL NET UIT SODRA KLAAR --> In reality this must be clientgs->sendToServer(
    clientgs->onTextMessageReceived(mes);

    // Debug code to test that the bids are placed in the correct cells
    QJsonObject temp = clientgs->CreateJObject(mes);
    temp["Player"] = "W";
    mes = clientgs->CreateJString(temp);
    clientgs->onTextMessageReceived(mes);

    temp["Player"] = "N";
    mes = clientgs->CreateJString(temp);
    clientgs->onTextMessageReceived(mes);

    temp["Player"] = "E";
    mes = clientgs->CreateJString(temp);
    clientgs->onTextMessageReceived(mes);

    temp["Player"] = "S";
    mes = clientgs->CreateJString(temp);
    clientgs->onTextMessageReceived(mes);

}

/* Slot for BID_START signal */
void GameScreen::bidStartSlot(QJsonObject cardsdealt)
{
    QJsonValue value = cardsdealt.value("Cards");
    QJsonArray array1 = value.toArray();
    int count = 0;

    foreach (const QJsonValue & v, array1){
        //cout<<"******"<<v.toObject().value("Rank")[0].toString().toStdString()<<endl;
        //cout<<v.toObject().value("Rank").toArray().size()<<endl;
        for (int k=0;k<v.toObject().value("Rank").toArray().size();k++) {
            //cout<<v.toObject().value("Suit").toString().toStdString()<<v.toObject().value("Rank")[k].toString().toStdString()<<", ";
            cards[count] = v.toObject().value("Suit").toString() + v.toObject().value("Rank")[k].toString();
            count++;
        }
    }

    // Temp debug code
    for (int k=0;k<13;k++) {
        cout<<cards[k].toStdString()<<", ";
    }
    cout<<endl;

    // Load the cards into GUI
    showCards();
    // Om die rank te kry cout<<"******"<<v.toObject().value("Rank")[0].toString().toStdString()<<endl;
    // Om die suit te kry cout<<"******"<<v.toObject().value("Suit").toString().toStdString()<<endl;

    // Disable GUI elements until a BID_REQUEST is received from server
    ui->tableBids->setEnabled(false);
    ui->pushButton_Bid->setEnabled(false);
    ui->pushButton_Double->setEnabled(false);
    ui->pushButton_Pass->setEnabled(false);
    ui->pushButton_Redouble->setEnabled(false);

    /* In die normale flow of events sal die server na bg 'n BID_REQUEST stuur, maar omdat
       die server nou nie hier is nie word dit gesimulate in die sendBid function bo.
       Dis meer realisties om dit daar te doen want anders is daar net 1 request wat gestuur word
       en dis dit - nou kan ons klomp stuur. */
    // Temp debug code to test BID_REQUEST with bidRequestSignal/Slot
    QString mes = clientgs->GenerateMessage("BID_REQUEST");
    clientgs->onTextMessageReceived(mes);
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

// Slot for when the server requests a bid from the user/client
/* This enables the GUI, allowing a bid to be made. A bid will be made via these GUI elements.
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
void GameScreen::bidUpdateSlot(QJsonObject bid)
{
    //cout<<"2222"<<endl;
    QString Suit = bid["Bid"].toObject()["Suit"].toString();
    QString Rank = bid["Bid"].toObject()["Rank"].toString();

    int col = 0;
    //cout<<bid["Player"].toString().toStdString()<<endl;

    if (bid["Player"] == "N") {
        col =0;
    }
     if (bid["Player"] == "E") {
        //cout<<"2222"<<endl;
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

void GameScreen::toets(int i)
{
    QString mes = clientgs->GenerateMessage("BID_UPDATE");
    // Temp debug code. NEE VERKEERD, HAAL NET UIT SODRA KLAAR --> In reality this must be clientgs->sendToServer(
    clientgs->onTextMessageReceived(mes);
}

void GameScreen::addToTable(QString bid, int col)
{
    //cout<<"501"<<endl;
    QTableWidgetItem* selectedItem = new QTableWidgetItem;
    selectedItem->setText(bid);
    selectedItem->setTextAlignment(4);
    ui->tableSequence->setItem(row,col,selectedItem);
}

void GameScreen::bidEndSlot()
{

}

void GameScreen::playStartSlot()
{

}

void GameScreen::moveRequestSlot()
{

}

void GameScreen::moveUpdateSlot()
{

}

void GameScreen::trickEndSlot()
{

}

void GameScreen::playEndSlot()
{

}

void GameScreen::scoreSlot(QJsonObject scores)
{
    ScoreBoard scoreBoard(this);
    // Use modal approach
    scoreBoard.setModal(true);
    scoreBoard.exec();
    scoreBoard.updateScores(scores);
}

void GameScreen::disconnectPlayerSlot()
{
 clientgs->clientSocket.close();
}
