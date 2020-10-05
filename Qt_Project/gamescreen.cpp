#include "gamescreen.h"
#include "ui_gamescreen.h"
#include "scoreboard.h"

GameScreen::GameScreen(QWidget *parent) :
    QDialog(parent),
    //ui(new Ui::GameScreen)
    ui(new Ui::GameScreen)
{
    ui->setupUi(this);
    // Prevent the window from being resized
    QWidget::setFixedSize(size());

    // Set QDialog flags to that of a normal window
    this->setWindowFlags(Qt::Window);
    // Prevent the QTableWidget object cells from being resized
    ui->tableBids->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableBids->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // Set the title of the dialog
    QWidget::setWindowTitle("Auction");
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_Play->setVisible(false);
   // ui->tableBids->editItem()

//    QFont tableFont;
//    tableFont.setPointSize(24);
//    tableFont.setFamily("Segoe UI");
//    int r = ui->tableBids->rowCount();
//    int c = ui->tableBids->columnCount();
//    QColor col;
//    col.setRgb(100, 100, 100);
    //for(int k = 0; k < r; k++) {
    //    for(int l = 0; l < c; l++) {
            //QTableWidgetItem* selectedItem = ui->tableBids->item(0, 1);
            //selectedItem->setFont(tableFont);
            //selectedItem->setBackground(col);
        //}
    //}

    // Code to grey out a cell (0, 1)
//    QColor col;
//    col.setRgb(100, 100, 100);
//    QTableWidgetItem* selectedItem = ui->tableBids->item(0, 1);
//    selectedItem->setBackground(col);
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::on_GameScreen_finished(int result)
{
    // Show the parent again, in this case main window
    parentWidget()->show();
}

void GameScreen::on_pushButton_Score_clicked()
{
    // Create new instance of scoreBoard, set parent as this
    // (Game Screen dialog)
    ScoreBoard scoreBoard(this);
    // Use modal approach
    scoreBoard.setModal(true);
    scoreBoard.exec();
}

void GameScreen::on_pushButton_Play_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    // Update the title of the dialog
    QWidget::setWindowTitle("Normal Play");

}
