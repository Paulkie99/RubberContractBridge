#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamescreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_Join_clicked();

    void on_pushButton_Check_clicked();

private:
    Ui::MainWindow *ui;
    // Create instance of GameScreen
    GameScreen *gameScreen;
};
#endif // MAINWINDOW_H
