#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QDialog>
#include<QJsonObject>

namespace Ui {
class ScoreBoard;
}

class ScoreBoard : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreBoard(QWidget *parent = nullptr);
    ~ScoreBoard();
    void updateScores(QJsonObject, QJsonObject);


private slots:

    void on_ScoreBoard_finished(int result);

private:
    Ui::ScoreBoard *ui;
    int EWtotal=0;
    int NStotal = 0;
    int NS100=0;
    int EW100=0;
    int GNum=0;
};

#endif // SCOREBOARD_H
