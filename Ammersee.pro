#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T11:45:46
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ammersee
TEMPLATE = app


SOURCES += sources/main.cpp \
           sources/mainwindow.cpp \
           sources/dbank.cpp \
           sources/event_add.cpp \
           sources/teilnehmer.cpp \
           sources/teilnehmer_add.cpp \
           sources/duringevent.cpp

HEADERS  += sources/mainwindow.h \
            sources/dbank.h \
            sources/event_add.h \
            sources/teilnehmer.h \
            sources/teilnehmer_add.h \
            sources/duringevent.h

FORMS    += sources/mainwindow.ui \
            sources/event_add.ui \
            sources/teilnehmer.ui \
            sources/teilnehmer_add.ui \
            sources/duringevent.ui
