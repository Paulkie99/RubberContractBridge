/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Author: Ivan Cuyler
 * Last update: 2020/10/27 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <iostream>
using namespace std;

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

    ui->sbPort->setVisible(false);
    ui->lblPort->setVisible(false);
    ui->pushButton_Create->setVisible(false);

    for(int i = 0; i < 4; ++i)
        AI_Instances[i] = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
    if(client)
        delete client;
    if(gameScreen)
        delete gameScreen;
}

// The client is connected to the server and may begin sending messages.
// CONNECT_SUCCESSFUL received
void MainWindow::connectSuccessfulSlot(QJsonObject connectSuc)
{
    connected = true;
    id = connectSuc["Id"].toInt();

    // Get the GUI values from the "Join Game" screen
    QString IP = ui->leditHostIP->text();
    QString Port = ui->sbPort->text();
    QString Password = ui->leditPassword->text();
    QString Username = ui->leditUsername->text();


    // Generate, construct and return the JSON with the updated GUI values
    QString mes = client->GenerateMessage("CONNECT_REQUEST");
    QJsonObject request = client->CreateJObject(mes);
    request["Password"] = Password;
    request["Alias"] = Username;
    request["Id"] = id;

    //Send the updated message to the server
    client->SendMessageToServer(client->CreateJString(request));
}

/* If the user wishes to join an existing game, the stacked widget's
 index will be updated to allow the user to enter the server credentials. */
void MainWindow::on_pushButton_Join_clicked()
{
    // Go to Join game page
    ui->stackedWidget->setCurrentIndex(1);
    // Update the title of the window
    ui->menuBridge->setTitle("Join Game");
    // Set the focus to leditHostIP
    ui->leditHostIP->setFocus();

}

void MainWindow::on_pushButton_JoinServer_clicked()
{
    if (ui->cbAI->isChecked() == true && ui->cbAIvPlayer->isChecked() == false)
    {
        numAI = 4;
        for(int i = 0; i < numAI; ++i)
        {
            if(AI_Instances[i])
                delete AI_Instances[i];
            AI_Instances[i] = new AIPlayer();
        }
//        AIPlayer *bot1 = new AIPlayer();
//        AIPlayer *bot2 = new AIPlayer();
//        AIPlayer *bot3 = new AIPlayer();
//        AIPlayer *bot4 = new AIPlayer();
    }
    else if(ui->cbAIvPlayer->isChecked() == true && ui->cbAI->isChecked() == false)
    {
        QString s = ui->leditHostIP->text() == "" ? "ws://localhost:159" : ui->leditHostIP->text();
        clientconnection *client1 = new clientconnection(QUrl(s), false);
        client = client1;
        // Connect the various signals and slots
        connect(client, SIGNAL(connectSuccessfullSignal(QJsonObject)), this, SLOT(connectSuccessfulSlot(QJsonObject)));
        connect(client, &clientconnection::authSuccessfulSignal, this, &MainWindow::authSuccessfulSlot);
        connect(client, SIGNAL(authUnsuccessfulSignal(QJsonObject)), this, SLOT(authUnsuccessfulSlot(QJsonObject)));
        connect(client, SIGNAL(connectUnsuccessfulSignal(QJsonObject)), this, SLOT(connectUnsuccessfulSlot(QJsonObject)));
        numAI = 3;
        for(int i = 0; i < numAI; ++i)
        {
            if(AI_Instances[i])
                delete AI_Instances[i];
            AI_Instances[i] = new AIPlayer();
        }
//        AIPlayer *bot1 = new AIPlayer();
//        AIPlayer *bot2 = new AIPlayer();
//        AIPlayer *bot3 = new AIPlayer();
    }

    // Establish a clientconnection object for communicating over the network
    if (ui->cbAI->isChecked() == false && ui->leditHostIP->text() == "" && ui->cbAIvPlayer->isChecked() == false)
    {
        clientconnection *client1 = new clientconnection(QUrl(QStringLiteral("wss://102.132.146.35:159")), false);
        client = client1;
        // Connect the various signals and slots
        connect(client, SIGNAL(connectSuccessfullSignal(QJsonObject)), this, SLOT(connectSuccessfulSlot(QJsonObject)));
        connect(client, &clientconnection::authSuccessfulSignal, this, &MainWindow::authSuccessfulSlot);
        connect(client, SIGNAL(authUnsuccessfulSignal(QJsonObject)), this, SLOT(authUnsuccessfulSlot(QJsonObject)));
        connect(client, SIGNAL(connectUnsuccessfulSignal(QJsonObject)), this, SLOT(connectUnsuccessfulSlot(QJsonObject)));
    }
    else if (ui->cbAI->isChecked() == false && ui->leditHostIP->text() != "" && ui->cbAIvPlayer->isChecked() == false)
    {
        QString s = ui->leditHostIP->text();
        clientconnection *client1 = new clientconnection(QUrl(s), false);
        client = client1;

        // Connect the various signals and slots
        connect(client, SIGNAL(connectSuccessfullSignal(QJsonObject)), this, SLOT(connectSuccessfulSlot(QJsonObject)));
        connect(client, &clientconnection::authSuccessfulSignal, this, &MainWindow::authSuccessfulSlot);
        connect(client, SIGNAL(authUnsuccessfulSignal(QJsonObject)), this, SLOT(authUnsuccessfulSlot(QJsonObject)));
        connect(client, SIGNAL(connectUnsuccessfulSignal(QJsonObject)), this, SLOT(connectUnsuccessfulSlot(QJsonObject)));
    }
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
    if(client)
        delete client;
    if(gameScreen)
       delete gameScreen;

    client = NULL;
    gameScreen = NULL;
    connected = false;
    numAI = 0;
    id = 0;
    for(int i = 0; i < 4; ++i)
        AI_Instances[i] = NULL;
    ui->stackedWidget->setCurrentIndex(0);
    ui->menuBridge->setTitle("Home Screen");
    ui->lblHeading->setFocus();
}


// Return to the home screen
void MainWindow::on_pushButton_BackConf_clicked()
{
    // Go to Home Screen page
    if(client)
        delete client;
    if(gameScreen)
       delete gameScreen;

    client = NULL;
    gameScreen = NULL;
    connected = false;
    numAI = 0;
    id = 0;
    for(int i = 0; i < 4; ++i)
        AI_Instances[i] = NULL;
    ui->stackedWidget->setCurrentIndex(0);
    ui->menuBridge->setTitle("Home Screen");
    ui->lblHeading->setFocus();
}

/* Similar to on_pushButton_JoinServer_clicked, the user opts to create a new server.
   The Game Server will be initialised from here once integration starts. */
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


// AUTH_UNSUCCESSFUL received
void MainWindow::authUnsuccessfulSlot(QJsonObject unsuc)
{
    QMessageBox err;
    err.critical(0,"Could not authorize",unsuc["Description"].toString());
    err.setFixedSize(500,200);
}

// CONNECT_REQUEST was approved and access to the server granted.
// AUTH_SUCCESSFUL received
void MainWindow::authSuccessfulSlot()
{
    // Create the gamescreen object
    // Modelless approach
    // Hide main window
    hide();
    // Set stacked widget index to main window for when the user returns
    ui->stackedWidget->setCurrentIndex(0);


    // Create a new instance of GameScreen
    // Set parent of gameScreen as this class (main window)
    if(gameScreen)
        delete gameScreen;
    gameScreen = new GameScreen(this);
    gameScreen->show();

    connect(this, SIGNAL(serverInfoSignal(QString, QString, QString, clientconnection *, QString, int)), gameScreen, SLOT(serverInfoSlot(QString, QString, QString, clientconnection *, QString, int)));
    emit serverInfoSignal(ui->leditHostIP->text(),ui->sbPort->text(),ui->leditPassword->text(), client, ui->leditUsername->text(), id);
}

void MainWindow::connectUnsuccessfulSlot(QJsonObject conunsuc)
{
    QMessageBox err;
    err.critical(0,"Could not connect",conunsuc["Description"].toString());
    err.setFixedSize(500,200);
}
