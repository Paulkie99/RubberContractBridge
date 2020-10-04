#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <server.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

//class Server;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr, quint16 port = 159);
    ~Dialog();

private slots:
    void messageReceived(const QString &message);

private:
    Ui::Dialog *ui;
    Server* bridgeServer;

};
#endif // DIALOG_H
