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

//This function is used to update the scores on the scoreboard. The function receives
//a Jsonobject that contains the score of the two teams at the end of a game
//The scores are extracted and displayed on the GUI. AT the moment the scores are only displayed
//in a text box but will be implemented to fill the entire scoreboard.
void ScoreBoard::updateScores(QJsonObject NSscores,QJsonObject EWscores)
{
 //QJsonObject NSscores = scoresToDisplay["NSscores"].toObject();
 //QJsonObject EWscores = scoresToDisplay["EWscores"].toObject();
 qDebug()<<NSscores["overtricks"].toString();
 //code to update gui
 ui->txtWeAbove1->append(QString::number(NSscores["overtricks"].toInt()));
 ui->txtWeAbove1->append(QString::number(NSscores["undertricks"].toInt()));
 ui->txtWeAbove1->append(QString::number(NSscores["honors"].toInt()));
 ui->txtWeAbove1->append(QString::number(NSscores["vulnerable"].toInt()));
 ui->txtWeAbove1->append(QString::number(NSscores["double"].toInt()));
 ui->txtWeAbove1->append(QString::number(NSscores["redouble"].toInt()));
 ui->txtWeAbove1->append(QString::number(NSscores["slam"].toInt()));
 ui->txtWeAbove1->append(QString::number(NSscores["unfinished"].toInt()));
 ui->txtWeAbove1->append(QString::number(NSscores["trickScore"].toInt()));

 ui->txtTheyAbove1->append(QString::number(EWscores["overtricks"].toInt()));
 ui->txtTheyAbove1->append(QString::number(EWscores["undertricks"].toInt()));
 ui->txtTheyAbove1->append(QString::number(EWscores["honors"].toInt()));
 ui->txtTheyAbove1->append(QString::number(EWscores["vulnerable"].toInt()));
 ui->txtTheyAbove1->append(QString::number(EWscores["double"].toInt()));
 ui->txtTheyAbove1->append(QString::number(EWscores["redouble"].toInt()));
 ui->txtTheyAbove1->append(QString::number(EWscores["slam"].toInt()));
 ui->txtTheyAbove1->append(QString::number(EWscores["unfinished"].toInt()));
 ui->txtTheyAbove1->append(QString::number(EWscores["trickScore"].toInt()));
}
