#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set the prgram title
    QWidget::setWindowTitle("Rubber Contract Bridge");
    // Prevent the window from being resized
    QWidget::setFixedSize(size());
    // Set the Stacked Widget to show the first page upon creation
    ui->stackedWidget->setCurrentIndex(0);
    // Set the window title
    ui->menuBridge->setTitle("Home Screen");
    // Set the mask for the password line edit
    ui->leditPassword->setEchoMode(QLineEdit::Password);
    // Set the focus to the heading
    ui->lblHeading->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// If the user wishes to join an existing game, the stacked widget's
// index will be updated to allow the user to enter the server
// credentials.
void MainWindow::on_pushButton_Join_clicked()
{
    // Go to Join game page
    ui->stackedWidget->setCurrentIndex(1);
    // Update the title of the window
    ui->menuBridge->setTitle("Join Game");
    // Set the focus to leditHostIP
    ui->leditHostIP->setFocus();

}

// Preliminary client-side logic to receive input from the user.
// Once integration starts, these values will be communicated to
// the game server and appropriate steps followed from there.
// The pushButton_JoinServer is used when the user elects to
// join an existing game.
void MainWindow::on_pushButton_JoinServer_clicked()
{
    // Get the values from the "Join Game" screen
    QString IP = ui->leditHostIP->text();
    QString Port = ui->sbPort->text();
    QString Password = ui->leditPassword->text();

    // Once integration starts, these values will be sent to the
    // game server.
    // CLIENT-SIDE LOGIC FOLLOWS HERE

//    if (server credentials invalid) {
//            QMessageBox err;
//            err.critical(0,"Error","Invalid server credentials!");
//            err.setFixedSize(500,200);
//            ui->leditHostIP->setFocus();
//    }
//  else { server credentials valid
//      ... continue below

    //  CLIENT-SIDE LOGIC APPROVES SERVER CREDENTIALS & ALLOWS ACCESS
    // TO THE SERVER
    // Modelless approach
    // Hide main window
    hide();
    // Set stacked widget index to main window for when the user returns
    ui->stackedWidget->setCurrentIndex(0);

    // Create a new instance of GameScreen
    // Set parent of gameScreen as this class (main window)
    gameScreen = new GameScreen(this);
    gameScreen->show();
}

// The user opts to create a new server
void MainWindow::on_pushButton_Create_clicked()
{
    // Go to Configure server page
    ui->stackedWidget->setCurrentIndex(2);
    ui->menuBridge->setTitle("Configure Server");
    ui->sbAI->setFocus();
}

// Checkbox to show/hide the server password
void MainWindow::on_cbShowPassword_clicked()
{
    // Hide password when unchecked
    if (ui->cbShowPassword->isChecked() == 0)
       ui->leditPassword->setEchoMode(QLineEdit::Password);
    // Show the text in the password when checked
    if (ui->cbShowPassword->isChecked())
        ui->leditPassword->setEchoMode(QLineEdit::Normal);
}

// Return to the home screen
void MainWindow::on_pushButton_BackJoin_clicked()
{
    // Go to Home Screen page
    ui->stackedWidget->setCurrentIndex(0);
    ui->menuBridge->setTitle("Home Screen");
    ui->lblHeading->setFocus();
}


// Return to the home screen
void MainWindow::on_pushButton_BackConf_clicked()
{
    // Go to Home Screen page
    ui->stackedWidget->setCurrentIndex(0);
    ui->menuBridge->setTitle("Home Screen");
    ui->lblHeading->setFocus();
}

// Similar to on_pushButton_JoinServer_clicked, the user opts to
// create a new server. No client-to-server communication needs to
// take place because the client is also the host server.
// The Game Server will be initialised from here.
void MainWindow::on_pushButton_CreateConf_clicked()
{
    // Intermediate client-side logic to create the server
    QString numAI = ui->sbAI->text();
    QString Password = ui->leditCreatePassword->text();

    // Once the client-side logic is complete, a new instance of the
    // game screen class will be created.

    // Modelless approach
    // Hide main window
    hide();
    ui->stackedWidget->setCurrentIndex(0);
    // Create new instance of GameScreen
    // Set parent of gameScreen as this class (main window)
    gameScreen = new GameScreen(this);
    gameScreen->show();
}
