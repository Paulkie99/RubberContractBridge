#include "scoreboard.h"
#include "ui_scoreboard.h"
#include "gamescreen.h"
#include <iostream>
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

void ScoreBoard::updateScores(QJsonObject scoresToDisplay)
{
     QJsonObject NSscores = scoresToDisplay["NSscores"].toObject();
     QJsonObject EWscores = scoresToDisplay["EWscores"].toObject();

     //code to update gui
     int NSScores2 = scoresToDisplay["NSscores"].toObject()["overtricks"].toInt();
     ui->txtWeAbove1->setText(QString::number(NSScores2));
     ui->txtWeAbove1->append("hello");
}
