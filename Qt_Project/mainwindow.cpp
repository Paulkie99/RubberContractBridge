#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <iostream>
using namespace std;

// Establish a clientconnection object for communicating over the network
clientconnection client(QUrl(QStringLiteral("ws://localhost:159")), true);



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

    // Connect the various signals and slots
    connect(&client, &clientconnection::serverFullSignal, this, &MainWindow::serverFullSlot);
    connect(&client, &clientconnection::connectSuccessfullSignal, this, &MainWindow::connectSuccessfulSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Temp debug, delete with time
void MainWindow::ServerFull()
{
    cout<<"Hello"<<endl;
    QMessageBox err;
    err.critical(0,"Error","Server is full");
    err.setFixedSize(500,200);
    //ui->leditHostIP->setFocus();

}

void MainWindow::customslot()
{
    cout<<"4545"<<endl;

}

void MainWindow::serverFullSlot()
{
    QMessageBox err;
    err.critical(0,"Error","Server is full");
    err.setFixedSize(500,200);
    ui->leditHostIP->setFocus();
}

void MainWindow::otherSlot()
{
    QMessageBox err;
    err.critical(0,"Error","Unable to join server. Check the server credentials");
    err.setFixedSize(500,200);
    ui->leditHostIP->setFocus();
}

void MainWindow::connectSuccessfulSlot()
{
    //  CLIENT-SIDE LOGIC APPROVES SERVER CREDENTIALS & ALLOWS ACCESS TO THE SERVER
    // Modelless approach
    // Hide main window
    hide();
    // Set stacked widget index to main window for when the user returns
    ui->stackedWidget->setCurrentIndex(0);


    // Create a new instance of GameScreen
    // Set parent of gameScreen as this class (main window)
    gameScreen = new GameScreen(this);
    gameScreen->show();

    // For some reason the only way to pass information along via signals & slots is to use
    // the SIGNAL and SLOT method
    //connect(this, &MainWindow::serverInfoSignal(&QString , QString, QString), &gameScreen, &GameScreen::serverInfoSlot(QString, QString, QString));
    connect(this, SIGNAL(serverInfoSignal(QString, QString, QString, clientconnection *)), gameScreen, SLOT(serverInfoSlot(QString, QString, QString, clientconnection *)));
    emit serverInfoSignal(ui->leditHostIP->text(),ui->sbPort->text(),ui->leditPassword->text(), &client);


    //emit bid start signal ?
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
    QString Username = ui->leditUsername->text();


    QString mes = client.GenerateMessage("CONNECT_REQUEST");
    QJsonObject request = client.CreateJObject(mes);
    request["Password"] = Password;
    request["Alias"] = Username;

    //Send the updated message to the server
    client.SendMessageToServer(client.CreateJString(request));

    // Temp debug code to test successful login
    mes = client.GenerateMessage("CONNECT_SUCCESSFUL");
    client.onTextMessageReceived(mes);
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

//Function to handle a received lobby update signal
void MainWindow::lobbyUpdateSlot()
{

}

void MainWindow::authSuccessfulSlot()
{

}

void MainWindow::authUnsuccessfulSlot()
{

}

void MainWindow::connectUnsuccessfulSlot()
{

}

