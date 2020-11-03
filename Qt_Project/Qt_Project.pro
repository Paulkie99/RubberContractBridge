QT       += core gui
QT += core websockets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aiplayer.cpp \
    card.cpp \
    clientconnection.cpp \
    gamescreen.cpp \
    main.cpp \
    mainwindow.cpp \
    scoreboard.cpp

HEADERS += \
    aiplayer.h \
    card.h \
    clientconnection.h \
    gamescreen.h \
    mainwindow.h \
    scoreboard.h

FORMS += \
    gamescreen.ui \
    mainwindow.ui \
    scoreboard.ui

RESOURCES = application.qrc
RESOURCES += jfiles.qrc
RESOURCES += certs.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
