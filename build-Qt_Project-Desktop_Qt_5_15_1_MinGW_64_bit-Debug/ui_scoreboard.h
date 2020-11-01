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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ScoreBoard
{
public:
    QTableWidget *tableWidgetScore;
    QTextEdit *txtWeAbove1;
    QTextEdit *txtWeAbove2;
    QTextEdit *txtWeAbove3;
    QTextEdit *txtWeBelow1;
    QTextEdit *txtWeBelow2;
    QTextEdit *txtWeBelow3;
    QTextEdit *txtTheyAbove1;
    QTextEdit *txtTheyAbove2;
    QTextEdit *txtTheyAbove3;
    QTextEdit *txtTheyBelow1;
    QTextEdit *txtTheyBelow2;
    QTextEdit *txtTheyBelow3;
    QLabel *lblVulnerable;

    void setupUi(QDialog *ScoreBoard)
    {
        if (ScoreBoard->objectName().isEmpty())
            ScoreBoard->setObjectName(QString::fromUtf8("ScoreBoard"));
        ScoreBoard->resize(792, 714);
        tableWidgetScore = new QTableWidget(ScoreBoard);
        if (tableWidgetScore->columnCount() < 4)
            tableWidgetScore->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetScore->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetScore->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetScore->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetScore->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidgetScore->rowCount() < 4)
            tableWidgetScore->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetScore->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetScore->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetScore->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetScore->setVerticalHeaderItem(3, __qtablewidgetitem7);
        tableWidgetScore->setObjectName(QString::fromUtf8("tableWidgetScore"));
        tableWidgetScore->setGeometry(QRect(10, 30, 771, 261));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidgetScore->sizePolicy().hasHeightForWidth());
        tableWidgetScore->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(18);
        tableWidgetScore->setFont(font);
        tableWidgetScore->setFrameShape(QFrame::Box);
        tableWidgetScore->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetScore->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetScore->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetScore->setTabKeyNavigation(false);
        tableWidgetScore->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidgetScore->setShowGrid(true);
        tableWidgetScore->horizontalHeader()->setDefaultSectionSize(147);
        tableWidgetScore->verticalHeader()->setDefaultSectionSize(50);
        txtWeAbove1 = new QTextEdit(ScoreBoard);
        txtWeAbove1->setObjectName(QString::fromUtf8("txtWeAbove1"));
        txtWeAbove1->setGeometry(QRect(10, 310, 121, 181));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        txtWeAbove1->setFont(font1);
        txtWeAbove1->setReadOnly(false);
        txtWeAbove2 = new QTextEdit(ScoreBoard);
        txtWeAbove2->setObjectName(QString::fromUtf8("txtWeAbove2"));
        txtWeAbove2->setGeometry(QRect(270, 310, 121, 181));
        QFont font2;
        font2.setPointSize(14);
        txtWeAbove2->setFont(font2);
        txtWeAbove2->setReadOnly(true);
        txtWeAbove3 = new QTextEdit(ScoreBoard);
        txtWeAbove3->setObjectName(QString::fromUtf8("txtWeAbove3"));
        txtWeAbove3->setGeometry(QRect(530, 310, 121, 181));
        txtWeAbove3->setFont(font2);
        txtWeAbove3->setReadOnly(true);
        txtWeBelow1 = new QTextEdit(ScoreBoard);
        txtWeBelow1->setObjectName(QString::fromUtf8("txtWeBelow1"));
        txtWeBelow1->setGeometry(QRect(10, 500, 121, 181));
        txtWeBelow1->setReadOnly(true);
        txtWeBelow2 = new QTextEdit(ScoreBoard);
        txtWeBelow2->setObjectName(QString::fromUtf8("txtWeBelow2"));
        txtWeBelow2->setGeometry(QRect(270, 500, 121, 181));
        txtWeBelow2->setReadOnly(true);
        txtWeBelow3 = new QTextEdit(ScoreBoard);
        txtWeBelow3->setObjectName(QString::fromUtf8("txtWeBelow3"));
        txtWeBelow3->setGeometry(QRect(530, 500, 121, 181));
        txtWeBelow3->setReadOnly(true);
        txtTheyAbove1 = new QTextEdit(ScoreBoard);
        txtTheyAbove1->setObjectName(QString::fromUtf8("txtTheyAbove1"));
        txtTheyAbove1->setGeometry(QRect(140, 310, 121, 181));
        txtTheyAbove1->setFont(font2);
        txtTheyAbove1->setReadOnly(true);
        txtTheyAbove2 = new QTextEdit(ScoreBoard);
        txtTheyAbove2->setObjectName(QString::fromUtf8("txtTheyAbove2"));
        txtTheyAbove2->setGeometry(QRect(400, 310, 121, 181));
        txtTheyAbove2->setFont(font2);
        txtTheyAbove2->setReadOnly(true);
        txtTheyAbove3 = new QTextEdit(ScoreBoard);
        txtTheyAbove3->setObjectName(QString::fromUtf8("txtTheyAbove3"));
        txtTheyAbove3->setGeometry(QRect(660, 310, 121, 181));
        txtTheyAbove3->setFont(font2);
        txtTheyAbove3->setReadOnly(true);
        txtTheyBelow1 = new QTextEdit(ScoreBoard);
        txtTheyBelow1->setObjectName(QString::fromUtf8("txtTheyBelow1"));
        txtTheyBelow1->setGeometry(QRect(140, 500, 121, 181));
        txtTheyBelow1->setReadOnly(true);
        txtTheyBelow2 = new QTextEdit(ScoreBoard);
        txtTheyBelow2->setObjectName(QString::fromUtf8("txtTheyBelow2"));
        txtTheyBelow2->setGeometry(QRect(400, 500, 121, 181));
        txtTheyBelow2->setReadOnly(true);
        txtTheyBelow3 = new QTextEdit(ScoreBoard);
        txtTheyBelow3->setObjectName(QString::fromUtf8("txtTheyBelow3"));
        txtTheyBelow3->setGeometry(QRect(660, 500, 121, 181));
        txtTheyBelow3->setReadOnly(true);
        lblVulnerable = new QLabel(ScoreBoard);
        lblVulnerable->setObjectName(QString::fromUtf8("lblVulnerable"));
        lblVulnerable->setGeometry(QRect(10, 680, 251, 31));
        QPalette palette;
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lblVulnerable->setPalette(palette);
        lblVulnerable->setFont(font2);
        lblVulnerable->setAlignment(Qt::AlignCenter);

        retranslateUi(ScoreBoard);

        QMetaObject::connectSlotsByName(ScoreBoard);
    } // setupUi

    void retranslateUi(QDialog *ScoreBoard)
    {
        ScoreBoard->setWindowTitle(QCoreApplication::translate("ScoreBoard", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetScore->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ScoreBoard", "North", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetScore->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ScoreBoard", "South", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetScore->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ScoreBoard", "East", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetScore->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ScoreBoard", "West", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetScore->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ScoreBoard", "1st Rubber", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetScore->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ScoreBoard", "2nd Rubber", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetScore->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ScoreBoard", "3rd Rubber", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetScore->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ScoreBoard", "Total", nullptr));
        txtWeAbove1->setMarkdown(QCoreApplication::translate("ScoreBoard", "We\n"
"\n"
"", nullptr));
        txtWeAbove1->setHtml(QCoreApplication::translate("ScoreBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:9px; margin-bottom:9px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">We</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:9px; margin-bottom:9px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        txtWeAbove2->setMarkdown(QCoreApplication::translate("ScoreBoard", "We\n"
"\n"
"", nullptr));
        txtWeAbove2->setHtml(QCoreApplication::translate("ScoreBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:9px; margin-bottom:9px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">We</p></body></html>", nullptr));
        txtWeAbove3->setMarkdown(QCoreApplication::translate("ScoreBoard", "We\n"
"\n"
"", nullptr));
        txtWeAbove3->setHtml(QCoreApplication::translate("ScoreBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:9px; margin-bottom:9px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">We</p></body></html>", nullptr));
        txtTheyAbove1->setMarkdown(QCoreApplication::translate("ScoreBoard", "They\n"
"\n"
"", nullptr));
        txtTheyAbove1->setHtml(QCoreApplication::translate("ScoreBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:5px; margin-bottom:5px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">They</p></body></html>", nullptr));
        txtTheyAbove2->setMarkdown(QCoreApplication::translate("ScoreBoard", "They\n"
"\n"
"", nullptr));
        txtTheyAbove2->setHtml(QCoreApplication::translate("ScoreBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:9px; margin-bottom:9px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">They</p></body></html>", nullptr));
        txtTheyAbove3->setMarkdown(QCoreApplication::translate("ScoreBoard", "They\n"
"\n"
"", nullptr));
        txtTheyAbove3->setHtml(QCoreApplication::translate("ScoreBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:5px; margin-bottom:5px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">They</p></body></html>", nullptr));
        lblVulnerable->setText(QCoreApplication::translate("ScoreBoard", "Vulnerable: North/South", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScoreBoard: public Ui_ScoreBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCOREBOARD_H
