#include "gamescreen.h"
#include "ui_gamescreen.h"
#include "scoreboard.h"
#include "QPixmap"
#include <iostream>
using namespace std;
// Function to load the player cards as well as the dummy's cards
// Once integrated it will receive the actual cards to load from server
void GameScreen::loadCards(QLabel *lbl, QString path){
                           //
//("C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/2C.jpg"); // <- path to image file
    QPixmap pm(path);
    lbl->setPixmap(path);
    lbl->setScaledContents(true);

//    lbl->setText("asd");

}
GameScreen::GameScreen(QWidget *parent) :
    QDialog(parent),
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
    //ui->pushButton_Play->setVisible(false);
//    QPixmap pm("C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/2C.jpg");
//    QLabel *lbl = ui->lblP_1;
//    loadCards(lbl, pm);

    QString paths[26];
    QString suit[4] = {"D","C","H","S"};
    srand(time(NULL));
    int range = 12 - 0 + 1;
    int rnum = rand() % range + 1;
    int rnum2 = rand() % 4 + 1;
    for (int k = 0;k<26 ;k++ ) {
        rnum2 = rand() % 4 + 1;
        if (rnum2 == 4){
            rnum2 = 0;
        }
        rnum = rand() % range + 1;
        if (rnum == 13){
            paths[k] = "K" + suit[rnum2];
            paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/"
                    + paths[k] + ".jpg";
            continue;
        }

        if (rnum==11) {
            paths[k] = "J" + suit[rnum2];
            paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/"
                    + paths[k] + ".jpg";
            continue;
        }
        if (rnum==12) {
            paths[k] = "Q" + suit[rnum2];
            paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/"
                    + paths[k] + ".jpg";
            continue;
        }
        if (rnum==1) {
            paths[k] = "A" + suit[rnum2];
            paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/"
                    + paths[k] + ".jpg";
            continue;
        }

        paths[k] = "C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/" +
                QString::number(rnum) + suit[rnum2] + ".jpg";
    }
    //QPixmap pm("C:/Users/ivanc/Documents/Ivan se werk/2020/EPE 321/Project/group_e/Cards/2H.jpg");
    QLabel *lbl = ui->lblP_1;
    loadCards(lbl, paths[0]);
    lbl = ui->lblP_2;
    loadCards(lbl, paths[1]);
    lbl = ui->lblP_3;
    loadCards(lbl, paths[2]);
    lbl = ui->lblP_4;
    loadCards(lbl, paths[3]);
    lbl = ui->lblP_5;
    loadCards(lbl, paths[4]);
    lbl = ui->lblP_6;
    loadCards(lbl, paths[5]);
    lbl = ui->lblP_7;
    loadCards(lbl, paths[6]);
    lbl = ui->lblP_8;
    loadCards(lbl, paths[7]);
    lbl = ui->lblP_9;
    loadCards(lbl, paths[8]);
    lbl = ui->lblP_10;
    loadCards(lbl, paths[9]);
    lbl = ui->lblP_11;
    loadCards(lbl, paths[10]);
    lbl = ui->lblP_12;
    loadCards(lbl, paths[11]);
    lbl = ui->lblP_13;
    loadCards(lbl, paths[12]);

    // Dummy Cards
    lbl = ui->lblP_14;
    loadCards(lbl, paths[13]);
    lbl = ui->lblP_15;
    loadCards(lbl, paths[14]);
    lbl = ui->lblP_16;
    loadCards(lbl, paths[15]);
    lbl = ui->lblP_17;
    loadCards(lbl, paths[16]);
    lbl = ui->lblP_18;
    loadCards(lbl, paths[17]);
    lbl = ui->lblP_19;
    loadCards(lbl, paths[18]);
    lbl = ui->lblP_20;
    loadCards(lbl, paths[19]);
    lbl = ui->lblP_21;
    loadCards(lbl, paths[20]);
    lbl = ui->lblP_22;
    loadCards(lbl, paths[21]);
    lbl = ui->lblP_23;
    loadCards(lbl, paths[22]);
    lbl = ui->lblP_24;
    loadCards(lbl, paths[23]);
    lbl = ui->lblP_25;
    loadCards(lbl, paths[24]);
    lbl = ui->lblP_26;
    loadCards(lbl, paths[25]);

//    for (int k = 0;k<14 ;k++ ) {
//       // std::cout<<paths[k];
//        //cout<<paths[k];
//        cout<<paths[k].toStdString()<<endl;
//    }

    //pm(paths[1]);
//    pm(paths[1]);
//    lbl = ui->lblP_2;
//    loadCards(lbl, pm);

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

// Close the Game Screen page
void GameScreen::on_pushButton_Abandon_clicked()
{
    this->close();
}
