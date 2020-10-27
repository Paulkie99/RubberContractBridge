#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QDialog>

namespace Ui {
class ScoreBoard;
}
//This class is used to create a scoreboard that shows the score of the rubber game.
//This scoreboard is updated with score messages received from the server and is updated
//by using the updateScores function.
class ScoreBoard : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreBoard(QWidget *parent = nullptr);
    ~ScoreBoard();
    void updateScores(QJsonObject,QJsonObject);

private slots:
    void on_ScoreBoard_finished(int result);

private:
    Ui::ScoreBoard *ui;
};

#endif // SCOREBOARD_H
