QT += testlib
QT += gui
QT += core
QT += websockets
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Server
INCLUDEPATH += ../ClientSide

HEADERS += ../Server/serverinterface.h \
    ../Server/gamestate.h \
    ../Server/serverclient.h
HEADERS += ../Server/server.h
HEADERS +=  ../Server/card.h
HEADERS += ../ClientSide/clientconnection.h

SOURCES +=  tst_testserver.cpp \
    ../Server/gamestate.cpp \
    ../Server/inputvalidator.cpp \
    ../Server/serverclient.cpp
SOURCES +=  ../Server/serverinterface.cpp
SOURCES +=  ../Server/server.cpp
SOURCES +=  ../Server/card.cpp
SOURCES +=  ../ClientSide/clientconnection.cpp

FORMS += \
    ../Server/dialog.ui

