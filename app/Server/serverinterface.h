/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement a server interface
 * Author: Paul Claasen 18006885
 * Last update: 06/10/2020 Revision 3*/

#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include <QDialog>
#include <server.h>
#include <QSslCertificate>
#include <QSslKey>

QT_BEGIN_NAMESPACE
namespace Ui { class Server_Dialog; }
QT_END_NAMESPACE

//class Server;

class ServerInterface : public QDialog
{
    Q_OBJECT

public:
    ServerInterface(QWidget *parent = nullptr, quint16 port = 159, bool secure = false);
    ~ServerInterface();
    friend class TestServer;

public slots:
    void Info(const QString& message);

private slots:
    void messageSent(const QString& message);
    void messageReceived(const QString &message);
    void tickUpdate(int);

private:
    Ui::Server_Dialog *ui;
    Server* bridgeServer;
    quint16 port = 159;
};

#endif // SERVERINTERFACE_H
