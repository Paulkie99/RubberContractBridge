#include "scoreboard.h"
#include "ui_scoreboard.h"
#include "gamescreen.h"
ScoreBoard::ScoreBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScoreBoard)
{
    ui->setupUi(this);

    // Disable resizing of window
    ui->tableWidgetScore->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidgetScore->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // Set window title
    QWidget::setWindowTitle("Scoreboard");
}

ScoreBoard::~ScoreBoard()
{
    delete ui;
}

void ScoreBoard::on_ScoreBoard_finished(int result)
{
    parentWidget()->show();
}
