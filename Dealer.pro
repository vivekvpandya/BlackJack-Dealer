#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T00:47:03
#
#-------------------------------------------------

QT       += core gui network xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dealer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    message.cpp \
    table.cpp \
    card.cpp \
    deck.cpp \
    networkoperationmanager.cpp \
    player.cpp \
    dealer.cpp \
    tablecontroller.cpp

HEADERS  += mainwindow.h \
    message.h \
    table.h \
    card.h \
    deck.h \
    networkoperationmanager.h \
    player.h \
    dealer.h \
    tablecontroller.h

FORMS    += mainwindow.ui
