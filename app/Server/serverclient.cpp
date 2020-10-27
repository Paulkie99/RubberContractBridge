/* Declaration
 * 1. I understand what plagiarism is and am aware of the University’s policy in this regard.
 * 2. I declare that this assignment is my own original work. Where other people’s work has been used (either from a
 * printed source, Internet or any other source), this has been properly acknowledged and referenced in accordance with
 * departmental requirements.*/

/* Code used to implement the serverclient, which is the server's representation of a client.
 * Author: Paul Claasen 18006885
 * Last update: 26/10/2020 Revision 4*/

#include "serverclient.h"

/*
 * Default constructor for ServerClient
 * */
ServerClient::ServerClient() : QObject()
{
}

/*
 * Slot connected to QWebSocket object's aboutToClose() signal. Emits socketDisconnect signal which tells the server to close the connection with a QWebSocket based on the passed id
 * */
void ServerClient::onDisconnect()
{
    emit socketDisconnect(id);
}
