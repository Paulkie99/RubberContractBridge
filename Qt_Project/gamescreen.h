/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Author: Ivan Cuyler
 * Last update: 2020/10/27 */

#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QDialog>
#include <QLabel>
#include <QObject>
#include "mainwindow.h"
#include "clientconnection.h"
#include<QThread>
class MainWindow;


namespace Ui {
class GameScreen;
}

class GameScreen : public QDialog
{
    Q_OBJECT
    friend class MainWindow;

public:
    explicit GameScreen(QWidget *parent = nullptr);
    ~GameScreen();

private slots:
    void on_GameScreen_finished(int result);

    void on_pushButton_Score_clicked();

    void on_pushButton_Play_clicked();

    void connectSlots();

    void loadCards(QPushButton *, QString);

    void on_pushButton_Abandon_clicked();

    void on_pushButton_Bid_clicked();

    void showCards(int);

    void disableCards(int, bool);

    void sendBid(QString, QString);

    void sendMove(QString, QString);

    void on_pushButton_ViewCards_clicked();

    void on_pushButton_BackAuction_clicked();

    void on_tableBids_cellClicked(int row, int column);

    void on_pushButton_Pass_clicked();

    void on_pushButton_Double_clicked();

    void on_pushButton_Redouble_clicked();

    void addToTable(QString, int);

    void visibleAll(bool vis = true);

    void serverInfoSlot(QString, QString, QString, clientconnection *, QString, int);
    void lobbyUpdateSlot(QJsonObject);
    void bidStartSlot(QJsonObject);
    void bidRequestSlot();
    void bidUpdateSlot(QJsonObject bid);
    void bidEndSlot(QJsonObject);
    void playStartSlot(QJsonObject);
    void moveRequestSlot(QJsonObject);
    void moveUpdateSlot(QJsonObject);
    void trickEndSlot(QJsonObject);
    void playEndSlot(QJsonObject);
    void scoreSlot(QJsonObject);
    void disconnectPlayerSlot(QJsonObject);
    void gameEndSlot(QJsonObject);

    void ping();
    void pongSlot(QJsonObject);


    void on_pb_1_clicked();

    void on_pb_2_clicked();

    void on_pb_3_clicked();

    void on_pb_4_clicked();

    void on_pb_5_clicked();

    void on_pb_6_clicked();

    void on_pb_7_clicked();

    void on_pb_8_clicked();

    void on_pb_9_clicked();

    void on_pb_10_clicked();

    void on_pb_11_clicked();

    void on_pb_12_clicked();

    void on_pb_13_clicked();

    void on_pb_14_clicked();

    void on_pb_15_clicked();

    void on_pb_16_clicked();

    void on_pb_17_clicked();

    void on_pb_18_clicked();

    void on_pb_19_clicked();

    void on_pb_20_clicked();

    void on_pb_21_clicked();

    void on_pb_22_clicked();

    void on_pb_23_clicked();

    void on_pb_24_clicked();

    void on_pb_25_clicked();

    void on_pb_26_clicked();

    void on_GameScreen_destroyed();

signals:
    //void bidStartSignal();
    void pingSignal(QJsonObject);

private:
    Ui::GameScreen *ui;
    /* Declare a pointer clientconnection object that points to the original
       client object established in mainwindow.*/
    clientconnection* clientgs = NULL;
    // cards is the user's cards
    QString cards[13];
    // cardsDummy is the dummy's cards
    QString cardsDummy[13];
    QString currentBidSuit = "";
    QString currentBidRank = "";
    int counter = 0;
    int row = 0;
    int Userid = 0;
    QString Username = "";
    QString NorthAlias = "";
    QString SouthAlias = "";
    QString WestAlias = "";
    QString EastAlias = "";
    QString UserPosition = "";
    QString Declarer = "";
    QString Dummy = "not set";
    QString Trump = "";
    bool Double = false;
    bool Redouble = false;
    QString Contract = "";
    // moveCounter holds how many cards have been played in the current round
    int moveCounter = 0;
    QString teamPos = "";
    QString teamUsername = "";
    QString opp1Pos = "";
    QString opp1Username = "";
    QString opp2Pos = "";
    QString opp2Username = "";
    QString movemade = "";
    QJsonObject NSarray [50];
    QJsonObject EWarray [50] ;
    int ArrCount = 0;};

#endif // GAMESCREEN_H
