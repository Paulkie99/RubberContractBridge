    #include <QtCore/QCoreApplication>
    #include "sslechoserver.h"

    int main(int argc, char *argv[])
    {
        QCoreApplication a(argc, argv);
        SslEchoServer server(443);

        Q_UNUSED(server);

        return a.exec();
    }

