#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "gamescreen.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set the Stacked Widget to show the first page upon creation
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Join_clicked()
{
   //ui->stackedWidget->setCurrentIndex(1);
//    hide();
//   GameScreen gameScreen;
//   gameScreen.setModal(true);
//   gameScreen.exec();

    // Modelless approach
    // Hide main window
    hide();
    // Create new instance of GameScreen
    // Set parent of gameScreen as this class (main window)
    gameScreen = new GameScreen(this);
    gameScreen->show();
}

void MainWindow::on_pushButton_Check_clicked()
{
    QString toets = ui->lineEdit->text();
    ui->pushButton_Join->setText(toets) ;
    ui->stackedWidget->setCurrentIndex(0);
}
