#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamescreen.h"
#include "clientconnection.h"
#include "aiplayer.h"

//class clientconnection;
class GameScreen;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class GameScreen;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_Join_clicked();

    void on_pushButton_JoinServer_clicked();

    void on_pushButton_Create_clicked();

    void on_cbShowPassword_clicked();

    void on_pushButton_BackJoin_clicked();

    void on_pushButton_BackConf_clicked();

    void on_pushButton_CreateConf_clicked();

    void connectSuccessfulSlot(QJsonObject);
    void authSuccessfulSlot();
    void authUnsuccessfulSlot(QJsonObject);
    void connectUnsuccessfulSlot(QJsonObject);

signals:
    /* clientconnection * is a pointer to the client object created in mainwindow.
       This allows us to have only one client object per session, and thus a new
       object doesn't have to be created for each interface.*/
    void serverInfoSignal(QString, QString, QString, clientconnection *, QString, int);

private:
    Ui::MainWindow *ui;
    // Create instance of GameScreen
    GameScreen *gameScreen;
};
#endif // MAINWINDOW_H
