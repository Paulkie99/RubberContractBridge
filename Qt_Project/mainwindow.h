/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Author: Ivan Cuyler
 * Last update: 2020/10/27 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamescreen.h"
#include "clientconnection.h"

//class clientconnection;
class GameScreen;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class GameScreen;
    friend class TestMainWindow;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    QString getPassword();

    QJsonObject returnJson(QString);

    void on_pushButton_Join_clicked();

    void on_pushButton_JoinServer_clicked();

    void on_pushButton_Create_clicked();

    void on_cbShowPassword_clicked();

    void on_pushButton_BackJoin_clicked();

    void on_pushButton_BackConf_clicked();

    void on_pushButton_CreateConf_clicked();

    QJsonObject connectSuccessfulSlot(QJsonObject);
    void authSuccessfulSlot();
    void authUnsuccessfulSlot(QJsonObject);
    void connectUnsuccessfulSlot(QJsonObject);

signals:
    /* clientconnection * is a pointer to the client object created in mainwindow.
       This allows us to have only one client object per session, and thus a new
       object doesn't have to be created for each interface.*/
    void serverInfoSignal(QString, QString, QString, clientconnection *, QString, int);
    void connectRequestSignal(QJsonObject);

private:
    Ui::MainWindow *ui;
    // Create instance of GameScreen
    GameScreen *gameScreen;
};
#endif // MAINWINDOW_H
