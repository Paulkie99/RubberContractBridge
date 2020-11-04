/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_Server_Dialog
{
public:
    QListWidget *listWidget;
    QCheckBox *checkBox;

    void setupUi(QDialog *Server_Dialog)
    {
        if (Server_Dialog->objectName().isEmpty())
            Server_Dialog->setObjectName(QString::fromUtf8("Server_Dialog"));
        Server_Dialog->resize(800, 600);
        listWidget = new QListWidget(Server_Dialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(15, 11, 771, 541));
        checkBox = new QCheckBox(Server_Dialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(670, 560, 70, 17));
        checkBox->setChecked(true);

        retranslateUi(Server_Dialog);

        QMetaObject::connectSlotsByName(Server_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Server_Dialog)
    {
        Server_Dialog->setWindowTitle(QCoreApplication::translate("Server_Dialog", "Server Interface", nullptr));
        checkBox->setText(QCoreApplication::translate("Server_Dialog", "Secure", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server_Dialog: public Ui_Server_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
