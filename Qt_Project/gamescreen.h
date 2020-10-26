#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QDialog>
#include <QLabel>
#include <QObject>
#include "mainwindow.h"
#include "clientconnection.h"
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

    void serverInfoSlot(QString, QString, QString, clientconnection *, QString, int);

    void bidStartSlot(QJsonObject);

    void on_pushButton_ViewCards_clicked();

    void on_pushButton_BackAuction_clicked();

    void on_tableBids_cellClicked(int row, int column);

    void on_pushButton_Pass_clicked();

    void on_pushButton_Double_clicked();

    void on_pushButton_Redouble_clicked();

    void bidRequestSlot();

    void bidUpdateSlot(QJsonObject bid);

    void addToTable(QString, int);

    void visibleAll(bool vis = true);

    void bidEndSlot(QJsonObject);

    void moveRequestSlot(QJsonObject);
    void moveUpdateSlot(QJsonObject);
    void trickEndSlot(QJsonObject);
    void playEndSlot(QJsonObject);
    void scoreSlot(QJsonObject);
    void disconnectPlayerSlot(QJsonObject);
    void lobbyUpdateSlot(QJsonObject);
    void gameEndSlot(QJsonObject);
    void ping();
    void pongSlot(QJsonObject);
    void playStartSlot(QJsonObject);
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

signals:
    //void bidStartSignal();
    void pingSignal(QJsonObject);

private:
    Ui::GameScreen *ui;
};

#endif // GAMESCREEN_H
