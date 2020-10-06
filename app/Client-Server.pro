TEMPLATE = subdirs

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SUBDIRS = Server ClientSide ServerTest
