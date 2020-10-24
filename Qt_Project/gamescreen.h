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

    void loadCards(QLabel *, QString);

    void on_pushButton_Abandon_clicked();

    void on_pushButton_Bid_clicked();

    void showCards();

    void sendBid(QString, QString);

    void serverInfoSlot(QString, QString, QString, clientconnection *);

    void bidStartSlot(QJsonObject);

    void on_pushButton_ViewCards_clicked();

    void on_pushButton_BackAuction_clicked();

    void on_tableBids_cellClicked(int row, int column);

    void on_pushButton_Pass_clicked();

    void on_pushButton_Double_clicked();

    void on_pushButton_Redouble_clicked();

    void bidRequestSlot();

    void bidUpdateSlot(QJsonObject bid);

    void toets(int);

    void addToTable(QString, int);

    void bidEndSlot();
    void playStartSlot();
    void moveRequestSlot();
    void moveUpdateSlot();
    void trickEndSlot();
    void playEndSlot();
    void scoreSlot();
    void disconnectPlayerSlot();

signals:
    void bidStartSignal();

private:
    Ui::GameScreen *ui;
};

#endif // GAMESCREEN_H
