TEMPLATE = app
TARGET = name_of_the_app

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console

SOURCES += \
    aiplayer.cpp \
    card.cpp \
    gamestate.cpp \
    main.cpp

HEADERS += \
    aiplayer.h \
    card.h \
    gamestate.h
