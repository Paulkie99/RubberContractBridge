/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Author: Ivan Cuyler
 * Last update: 2020/10/27 */

#include <QtTest/QtTest>
#include <QCoreApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"
class TestMainWindow: public QObject
{
    Q_OBJECT
public:
//    TestMainWindow(){MainWindow w;
//                     w.show();}
   virtual ~TestMainWindow(){}
private:
    MainWindow *mw = new MainWindow;
private slots:
    void allObjectsPresent();
    void Buttons();
    void testAlias();
    void testID();
    void testPassword();
};


// Verify that all objects have been created
void TestMainWindow::allObjectsPresent()
{
    QVERIFY2(mw->ui->HomeScreen, "HomeScreen not created");
    QVERIFY2(mw->ui->JoinGame, "JoinGame not created");
    QVERIFY2(mw->ui->ConfigureServer, "ConfigureServer not created");
    QVERIFY2(mw->ui->cbShowPassword, "cbShowPassword not created");
    QVERIFY2(mw->ui->label, "label not created");
    QVERIFY2(mw->ui->lblAI, "lblAI not created");
    QVERIFY2(mw->ui->lblBackConf, "lblBackConf not created");
    QVERIFY2(mw->ui->lblBackJoin, "lblBackJoin not created");
    QVERIFY2(mw->ui->lblCreatePassword, "lblCreatePassword not created");
    QVERIFY2(mw->ui->lblHeading, "lblHeading not created");
    QVERIFY2(mw->ui->lblHostIP, "lblHostIP not created");
    QVERIFY2(mw->ui->lblPassword, "lblPassword not created");
    QVERIFY2(mw->ui->lblPort, "lblPort not created");
    QVERIFY2(mw->ui->lblUsername, "lblUsername not created");
    QVERIFY2(mw->ui->leditCreatePassword, "leditCreatePassword not created");
    QVERIFY2(mw->ui->leditHostIP, "leditHostIP not created");
    QVERIFY2(mw->ui->leditPassword, "leditPassword not created");
    QVERIFY2(mw->ui->leditUsername, "leditUsername not created");
    QVERIFY2(mw->ui->pushButton_BackConf, "pushButton_BackConf not created");
    QVERIFY2(mw->ui->pushButton_BackJoin, "pushButton_BackJoin not created");
    QVERIFY2(mw->ui->pushButton_Create, "pushButton_Create not created");
    QVERIFY2(mw->ui->pushButton_CreateConf, "pushButton_CreateConf not created");
    QVERIFY2(mw->ui->pushButton_Join, "pushButton_Join not created");
    QVERIFY2(mw->ui->pushButton_JoinServer, "pushButton_JoinServer not created");
    QVERIFY2(mw->ui->sbAI, "sbAI not created");
    QVERIFY2(mw->ui->sbPort, "sbPort not created");
}

// Verify the functionality of the buttons
void TestMainWindow::Buttons()
{
    QTest::mouseClick(mw->ui->pushButton_Join, Qt::LeftButton);
    QVERIFY(mw->ui->stackedWidget->currentIndex() == 1);

    QTest::mouseClick(mw->ui->pushButton_BackJoin, Qt::LeftButton);
    QVERIFY(mw->ui->stackedWidget->currentIndex() == 0);

    QTest::mouseClick(mw->ui->pushButton_Create, Qt::LeftButton);
    QVERIFY(mw->ui->stackedWidget->currentIndex() == 2);

    QTest::mouseClick(mw->ui->pushButton_BackConf, Qt::LeftButton);
    QVERIFY(mw->ui->stackedWidget->currentIndex() == 0);
}

void TestMainWindow::testAlias()
{
    QJsonObject test = mw->returnJson("CONNECT_REQUEST");
    QTest::keyClicks(mw->ui->leditUsername, "QT Testing Username");
    test["Alias"] = "QT Testing Username";

    QCOMPARE(test["Alias"], mw->connectSuccessfulSlot(test)["Alias"]);
}

void TestMainWindow::testID()
{
    QJsonObject test = mw->returnJson("CONNECT_REQUEST");
    QCOMPARE(test["Id"], mw->connectSuccessfulSlot(test)["Id"]);
}

void TestMainWindow::testPassword()
{
    QJsonObject test = mw->returnJson("CONNECT_REQUEST");
    QTest::keyClicks(mw->ui->leditPassword, "QT Testing Password");
    test["Password"] = "QT Testing Password";

    QCOMPARE(test["Password"], mw->connectSuccessfulSlot(test)["Password"]);
}

QTEST_MAIN(TestMainWindow)
#include "testmainwindow.moc"
