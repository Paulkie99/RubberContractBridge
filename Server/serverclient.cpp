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
