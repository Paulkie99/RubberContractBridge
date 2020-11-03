/********************************************************************************
** Form generated from reading UI file 'scoreboard.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCOREBOARD_H
#define UI_SCOREBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ScoreBoard
{
public:
    QTextEdit *txtNSBonus;
    QTextEdit *txtEWBonus;
    QTextEdit *txtNSG1;
    QTextEdit *txtEWG1;
    QTextEdit *txtNSG2;
    QTextEdit *txtEWG2;
    QTextEdit *txtNSG3;
    QTextEdit *txtEWG3;
    QLabel *label;
    QLabel *label_2;
    QLabel *NSTotal;
    QLabel *EWTotal;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QTextEdit *txtNSlog;
    QTextEdit *txtEWlog;

    void setupUi(QDialog *ScoreBoard)
    {
        if (ScoreBoard->objectName().isEmpty())
            ScoreBoard->setObjectName(QString::fromUtf8("ScoreBoard"));
        ScoreBoard->resize(760, 974);
        txtNSBonus = new QTextEdit(ScoreBoard);
        txtNSBonus->setObjectName(QString::fromUtf8("txtNSBonus"));
        txtNSBonus->setGeometry(QRect(10, 40, 301, 171));
        txtNSBonus->setReadOnly(true);
        txtEWBonus = new QTextEdit(ScoreBoard);
        txtEWBonus->setObjectName(QString::fromUtf8("txtEWBonus"));
        txtEWBonus->setGeometry(QRect(350, 40, 301, 171));
        txtEWBonus->setReadOnly(true);
        txtNSG1 = new QTextEdit(ScoreBoard);
        txtNSG1->setObjectName(QString::fromUtf8("txtNSG1"));
        txtNSG1->setGeometry(QRect(10, 240, 301, 91));
        QFont font;
        font.setPointSize(10);
        txtNSG1->setFont(font);
        txtNSG1->setReadOnly(true);
        txtEWG1 = new QTextEdit(ScoreBoard);
        txtEWG1->setObjectName(QString::fromUtf8("txtEWG1"));
        txtEWG1->setGeometry(QRect(350, 240, 301, 91));
        txtEWG1->setFont(font);
        txtEWG1->setReadOnly(true);
        txtNSG2 = new QTextEdit(ScoreBoard);
        txtNSG2->setObjectName(QString::fromUtf8("txtNSG2"));
        txtNSG2->setGeometry(QRect(10, 350, 301, 91));
        txtNSG2->setFont(font);
        txtNSG2->setReadOnly(true);
        txtEWG2 = new QTextEdit(ScoreBoard);
        txtEWG2->setObjectName(QString::fromUtf8("txtEWG2"));
        txtEWG2->setGeometry(QRect(350, 350, 301, 91));
        txtEWG2->setFont(font);
        txtEWG2->setReadOnly(true);
        txtNSG3 = new QTextEdit(ScoreBoard);
        txtNSG3->setObjectName(QString::fromUtf8("txtNSG3"));
        txtNSG3->setGeometry(QRect(10, 460, 301, 91));
        txtNSG3->setFont(font);
        txtNSG3->setReadOnly(true);
        txtEWG3 = new QTextEdit(ScoreBoard);
        txtEWG3->setObjectName(QString::fromUtf8("txtEWG3"));
        txtEWG3->setGeometry(QRect(350, 460, 301, 91));
        txtEWG3->setFont(font);
        txtEWG3->setReadOnly(true);
        label = new QLabel(ScoreBoard);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 0, 171, 41));
        QFont font1;
        font1.setPointSize(15);
        label->setFont(font1);
        label_2 = new QLabel(ScoreBoard);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(440, 0, 161, 41));
        label_2->setFont(font1);
        NSTotal = new QLabel(ScoreBoard);
        NSTotal->setObjectName(QString::fromUtf8("NSTotal"));
        NSTotal->setGeometry(QRect(110, 550, 221, 41));
        NSTotal->setFont(font1);
        EWTotal = new QLabel(ScoreBoard);
        EWTotal->setObjectName(QString::fromUtf8("EWTotal"));
        EWTotal->setGeometry(QRect(460, 550, 261, 41));
        EWTotal->setFont(font1);
        label_3 = new QLabel(ScoreBoard);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(670, 100, 81, 61));
        QFont font2;
        font2.setPointSize(12);
        label_3->setFont(font2);
        label_4 = new QLabel(ScoreBoard);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(670, 250, 81, 61));
        label_4->setFont(font2);
        label_5 = new QLabel(ScoreBoard);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(670, 360, 81, 61));
        label_5->setFont(font2);
        label_6 = new QLabel(ScoreBoard);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(670, 480, 81, 61));
        label_6->setFont(font2);
        txtNSlog = new QTextEdit(ScoreBoard);
        txtNSlog->setObjectName(QString::fromUtf8("txtNSlog"));
        txtNSlog->setGeometry(QRect(10, 650, 301, 321));
        txtNSlog->setReadOnly(true);
        txtEWlog = new QTextEdit(ScoreBoard);
        txtEWlog->setObjectName(QString::fromUtf8("txtEWlog"));
        txtEWlog->setGeometry(QRect(350, 650, 301, 321));
        txtEWlog->setReadOnly(true);

        retranslateUi(ScoreBoard);

        QMetaObject::connectSlotsByName(ScoreBoard);
    } // setupUi

    void retranslateUi(QDialog *ScoreBoard)
    {
        ScoreBoard->setWindowTitle(QCoreApplication::translate("ScoreBoard", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ScoreBoard", "NORTH/SOUTH", nullptr));
        label_2->setText(QCoreApplication::translate("ScoreBoard", "EAST/WEST", nullptr));
        NSTotal->setText(QCoreApplication::translate("ScoreBoard", "TextLabel", nullptr));
        EWTotal->setText(QCoreApplication::translate("ScoreBoard", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("ScoreBoard", "BONUS", nullptr));
        label_4->setText(QCoreApplication::translate("ScoreBoard", "GAME 1", nullptr));
        label_5->setText(QCoreApplication::translate("ScoreBoard", "GAME 2", nullptr));
        label_6->setText(QCoreApplication::translate("ScoreBoard", "GAME 3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScoreBoard: public Ui_ScoreBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCOREBOARD_H
