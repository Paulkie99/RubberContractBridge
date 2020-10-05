#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "gamescreen.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Rubber Contract Bridge");
    // Prevent the window from being resized
    QWidget::setFixedSize(size());
    // Set the Stacked Widget to show the first page upon creation
    ui->stackedWidget->setCurrentIndex(0);
    ui->menuBridge->setTitle("Home Screen");
    // Set the mask for the password line edit
    ui->leditPassword->setEchoMode(QLineEdit::Password);
    ui->lblHeading->setFocus();
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


    // Go to Join game page
    ui->stackedWidget->setCurrentIndex(1);
    ui->menuBridge->setTitle("Join Game");
    ui->leditHostIP->setFocus();

}

void MainWindow::on_pushButton_Check_clicked()
{
    QString toets = ui->lineEdit->text();
    ui->pushButton_Join->setText(toets) ;
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_JoinServer_clicked()
{
    // Get the values from the "Join Game" screen
    QString IP = ui->leditHostIP->text();
    QString Port = ui->sbPort->text();
    QString Password = ui->leditPassword->text();

    // Modelless approach
    // Hide main window
    hide();
    // Create new instance of GameScreen
    // Set parent of gameScreen as this class (main window)
    gameScreen = new GameScreen(this);
    gameScreen->show();
}


void MainWindow::on_pushButton_Create_clicked()
{
    // Go to Configure server page
    ui->stackedWidget->setCurrentIndex(2);
    ui->menuBridge->setTitle("Configure Server");
    ui->sbAI->setFocus();
}

void MainWindow::on_cbShowPassword_clicked()
{
    // Hide password when unchecked
    if (ui->cbShowPassword->isChecked() == 0)
       ui->leditPassword->setEchoMode(QLineEdit::Password);
    // Show the text in the password when checked
    if (ui->cbShowPassword->isChecked())
        ui->leditPassword->setEchoMode(QLineEdit::Normal);
}

void MainWindow::on_pushButton_BackJoin_clicked()
{
    // Go to Home Screen page
    ui->stackedWidget->setCurrentIndex(0);
    ui->menuBridge->setTitle("Home Screen");
    ui->lblHeading->setFocus();
}

void MainWindow::on_pushButton_BackConf_clicked()
{
    // Go to Home Screen page
    ui->stackedWidget->setCurrentIndex(0);
    ui->menuBridge->setTitle("Home Screen");
    ui->lblHeading->setFocus();
}

void MainWindow::on_pushButton_CreateConf_clicked()
{

    QString numAI = ui->sbAI->text();
    QString Password = ui->leditCreatePassword->text();

    // Modelless approach
    // Hide main window
    hide();
    // Create new instance of GameScreen
    // Set parent of gameScreen as this class (main window)
    gameScreen = new GameScreen(this);
    gameScreen->show();
}
