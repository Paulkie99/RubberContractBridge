#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QDialog>

namespace Ui {
class ScoreBoard;
}

class ScoreBoard : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreBoard(QWidget *parent = nullptr);
    ~ScoreBoard();
    void updateScores(QJsonObject [50],QJsonObject[50],int);

private slots:
    void on_ScoreBoard_finished(int result);

private:
    Ui::ScoreBoard *ui;
};

#endif // SCOREBOARD_H
