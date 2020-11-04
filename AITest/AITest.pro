QT += testlib
QT += gui
QT += core
QT += websockets
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../AI

HEADERS += ../AI/aiplayer.h
HEADERS += ../AI/gamestate.h
HEADERS +=  ../AI/card.h

SOURCES +=  tst_testai.cpp
SOURCES +=  ../AI/aiplayer.cpp
SOURCES +=  ../AI/gamestate.cpp
SOURCES +=  ../AI/card.cpp

FORMS += \
    ../AI/mainwindow.ui

