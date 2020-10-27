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

// Establish a clientconnection object for communicating over the network
clientconnection *client;
int id = 0;
bool connected = false;
QString testpassword = "";

// Constructor
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

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Unit test helper function
QString MainWindow::getPassword()
{
    return testpassword;
}

// Unit test helper function
QJsonObject MainWindow::returnJson(QString type)
{
    // Establish a clientconnection object for communicating over the network
    clientconnection *client1 = new clientconnection(QUrl(QStringLiteral("ws://localhost:159")), false);

    QString mes = client1->GenerateMessage(type);

    // Return a QJsonObject of what was requested
    return client1->CreateJObject(mes);
}

// The client is connected to the server and may begin sending messages.
// CONNECT_SUCCESSFUL received
QJsonObject MainWindow::connectSuccessfulSlot(QJsonObject connectSuc)
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

    return request;
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

/* Preliminary client-side logic to receive input from the user.
 Once integration starts, these values will be communicated to the game server
 and appropriate steps followed from there. The pushButton_JoinServer is used
 when the user elects to join an existing game. */
void MainWindow::on_pushButton_JoinServer_clicked()
{
    // Establish a clientconnection object for communicating over the network
    clientconnection *client1 = new clientconnection(QUrl(QStringLiteral("ws://localhost:159")), true);
    client = client1;
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

/* Similar to on_pushButton_JoinServer_clicked, the user opts to create a new server.
   The Game Server will be initialised from here once integration starts. */
void MainWindow::on_pushButton_CreateConf_clicked()
{
    // Intermediate client-side logic to create the server
    QString numAI = ui->sbAI->text();
    QString Password = ui->leditCreatePassword->text();

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

