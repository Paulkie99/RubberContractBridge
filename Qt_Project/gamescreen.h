#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class GameScreen;
}

class GameScreen : public QDialog
{
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);
    ~GameScreen();

private slots:
    void on_GameScreen_finished(int result);

    void on_pushButton_Score_clicked();

    void on_pushButton_Play_clicked();

    void loadCards(QLabel *, QString);

    void on_pushButton_Abandon_clicked();

private:
    Ui::GameScreen *ui;
};

#endif // GAMESCREEN_H
